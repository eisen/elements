/*=============================================================================
   Copyright (c) 2016-2019 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <photon/window.hpp>
#import <Cocoa/Cocoa.h>

namespace photon = cycfi::photon;

@interface PhotonWindow : NSWindow
{
   photon::window* _pwin;
}
@end

@implementation PhotonWindow

- (void) set_photon_window : (photon::window*) pwin
{
   self->_pwin = pwin;
}

- (void) close
{
   [super close];
   auto title = [self title];
   if ([title length] != 0)
      [self saveFrameUsingName : title];
   if (_pwin->on_close)
      _pwin->on_close();
}

@end

namespace cycfi { namespace photon
{
   namespace
   {
      inline int window_style(int option)
      {
         return
            ((option & window::with_title)? NSWindowStyleMaskTitled : 0)
          | ((option & window::closable)? NSWindowStyleMaskClosable : 0)
          | ((option & window::miniaturizable)? NSWindowStyleMaskMiniaturizable : 0)
          | ((option & window::resizable)? NSWindowStyleMaskResizable : 0)
          ;
      }
   }

   window::window(std::string const& name, int style_, rect const& bounds)
   {
      auto style = window_style(style_);

      PhotonWindow* window_ =
         [[PhotonWindow alloc]
            initWithContentRect : NSMakeRect(0, 0, 0, 0)
            styleMask : window_style(style_)
            backing : NSBackingStoreBuffered
            defer : NO
         ];
      _window = (__bridge void*) window_;

      window_.appearance = [NSAppearance appearanceNamed : NSAppearanceNameVibrantDark];
      [window_ setTitle : [NSString stringWithUTF8String : name.c_str()]];
      [window_ makeKeyAndOrderFront : nil];
      [window_ set_photon_window : this];

      auto title = [window_ title];
      if ([title length] == 0 || ![window_ setFrameUsingName : title])
      {
         size({ bounds.width(), bounds.height() });
         position({ bounds.left, bounds.top });
      }
   }

   window::~window()
   {
   }

   point window::size() const
   {
      id const& window_ = (__bridge id) _window;
      auto const& frame = [window_ frame];
      return { float(frame.size.width), float(frame.size.height) };
   }

   void window::size(point const& p)
   {
      id window_ = (__bridge id) _window;
      auto frame = [window_ frame];
      frame.size.width = p.x;
      frame.size.height = p.y;
      [window_ setFrame : frame display : YES animate : false];
   }

   point window::position() const
   {
      id const window_ = (__bridge id) _window;
      auto const& frame = [window_ frame];
      NSRect sframe = [[NSScreen mainScreen] frame];

      return {
         float(frame.origin.x - sframe.origin.x)
       , float((sframe.size.height - frame.size.height) - (frame.origin.y - sframe.origin.y))
      };
   }

   void window::position(point const& p)
   {
      id window_ = (__bridge id) _window;
      NSRect sframe = [[NSScreen mainScreen] frame];

      auto frame = [window_ frame];
      frame.origin.x = sframe.origin.x + p.x;
      frame.origin.y = sframe.origin.y + (sframe.size.height - frame.size.height) - p.y;

      [window_ setFrame : frame display : YES animate : false];
   }
}}

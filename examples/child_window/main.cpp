/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <elements.hpp>

using namespace cycfi::elements;

// Main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

auto make_child_window()
{
   return closable_child_window(
      "Child Window",
      { 10, 10, 300, 200 },
      scroller(image{ "deep_space.jpg" })
   );
}

int main(int argc, char* argv[])
{
   app _app(argc, argv, "Child Window", "com.cycfi.child-window");
   window _win(_app.name());
   _win.on_close = [&_app]() { _app.stop(); };

   view view_(_win);

   view_.content(
      make_child_window(),
      background
   );

   _app.run();
   return 0;
}
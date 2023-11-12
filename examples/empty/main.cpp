/*=============================================================================
   Copyright (c) 2016-2023 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <elements.hpp>

using namespace cycfi::elements;
using namespace cycfi::artist;

// Main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

int main(int argc, char* argv[])
{
   app _app(argc, argv, "Empty Starter", "com.cycfi.empty-starter");
   window _win(_app.name());
   _win.on_close = [&_app]() { _app.stop(); };
   view view_(_win);

   auto open_button = button("open");

   window win2(_app.name());
   view view2(win2);
   view2.content(box(bkd_color));
   win2.hide();

   open_button.on_click = [&](bool)
   {
      win2.show();
   };
   view_.content(open_button, background);
   _app.run();
   return 0;
}



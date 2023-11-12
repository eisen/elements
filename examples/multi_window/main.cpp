/*=============================================================================
   Copyright (c) 2016-2023 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <elements.hpp>

using namespace cycfi::elements;
using namespace cycfi::artist;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
constexpr auto bblue = colors::blue.opacity(0.4);
constexpr auto ggreen = colors::green.opacity(0.4);
auto background = box(bkd_color);

int main(int argc, char* argv[])
{
   app _app(argc, argv, "Show/Hide window", "com.cycfi.multi-window");
   window _win(_app.name());
   window win2("Other Window");
   view view_(_win);
   view view2(win2);

   auto hide_button = button("Hide other window", 1.0, bblue);
   auto show_button = button("Show other Window", 1.0, ggreen);

   view_.content(
      margin({20, 0, 20, 20},
         vtile(
            top_margin(20, link(show_button)),
            top_margin(20, link(hide_button))
         )
      ),
      background
   );

   view2.content(box(bkd_color));
   win2.hide(); // FIXME: This doesn't work (at least) on GTK3, needs to be called after app::run()

   hide_button.on_click = [&](bool) { win2.hide(); };
   show_button.on_click = [&](bool) { win2.show(); };

   win2.on_close =
   _win.on_close = [&_app]() { _app.stop(); };

   _app.run();
   return 0;
}

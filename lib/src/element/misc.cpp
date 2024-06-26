/*=============================================================================
   Copyright (c) 2016-2023 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/misc.hpp>

namespace cycfi::elements
{
   void panel::draw(context const& ctx)
   {
      draw_panel(
         ctx.canvas
       , ctx.bounds
       , get_theme().panel_color.opacity(_opacity)
       , 4.0
      );
   }

   void frame::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(colors::black.opacity(0.4));
      canvas_.stroke_round_rect(bounds.move(-1, -1), theme_.frame_corner_radius);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.stroke_round_rect(bounds, theme_.frame_corner_radius);
   }

   void border::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.stroke_rect(bounds);
   }

   void border_left::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.left, bounds.top});
      canvas_.line_to({bounds.left, bounds.bottom});
      canvas_.stroke();
   }

   void border_top::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.left, bounds.top});
      canvas_.line_to({bounds.right, bounds.top});
      canvas_.stroke();
   }

   void border_right::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.right, bounds.top});
      canvas_.line_to({bounds.right, bounds.bottom});
      canvas_.stroke();
   }

   void border_bottom::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.left, bounds.bottom});
      canvas_.line_to({bounds.right, bounds.bottom});
      canvas_.stroke();
   }

   void border_top_bottom::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.left, bounds.top});
      canvas_.line_to({bounds.right, bounds.top});
      canvas_.stroke();
      canvas_.move_to({bounds.left, bounds.bottom});
      canvas_.line_to({bounds.right, bounds.bottom});
      canvas_.stroke();
   }

   void border_left_right::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.move_to({bounds.left, bounds.top});
      canvas_.line_to({bounds.left, bounds.bottom});
      canvas_.stroke();
      canvas_.move_to({bounds.right, bounds.top});
      canvas_.line_to({bounds.right, bounds.bottom});
      canvas_.stroke();
   }

   void vgrid_lines::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      float pos = bounds.top;
      float incr = bounds.height() / _major_divisions;

      canvas_.stroke_style(theme_.major_grid_color);
      canvas_.line_width(theme_.major_grid_width);
      while (pos <= bounds.bottom+1)
      {
         canvas_.move_to({bounds.left, pos});
         canvas_.line_to({bounds.right, pos});
         canvas_.stroke();
         pos += incr;
      }

      pos = bounds.top;
      incr = bounds.height() / _minor_divisions;

      canvas_.stroke_style(theme_.minor_grid_color);
      canvas_.line_width(theme_.minor_grid_width);
      while (pos <= bounds.bottom+1)
      {
         canvas_.move_to({bounds.left, pos});
         canvas_.line_to({bounds.right, pos});
         canvas_.stroke();
         pos += incr;
      }
   }

   void hgrid_lines::draw(context const& ctx)
   {
      auto const& theme_ = get_theme();
      auto& canvas_ = ctx.canvas;
      auto const& bounds = ctx.bounds;

      float pos = bounds.left;
      float incr = bounds.width() / _major_divisions;

      canvas_.stroke_style(theme_.major_grid_color);
      canvas_.line_width(theme_.major_grid_width);
      while (pos <= bounds.right + 1)
      {
         canvas_.move_to({pos, bounds.top});
         canvas_.line_to({pos, bounds.bottom});
         canvas_.stroke();
         pos += incr;
      }

      pos = bounds.left;
      incr = bounds.width() / _minor_divisions;

      canvas_.stroke_style(theme_.minor_grid_color);
      canvas_.line_width(theme_.minor_grid_width);
      while (pos <= bounds.right + 1)
      {
         canvas_.move_to({pos, bounds.top});
         canvas_.line_to({pos, bounds.bottom});
         canvas_.stroke();
         pos += incr;
      }
   }

   icon::icon(std::uint32_t code_, float size_)
    : _code(code_)
    , _size(size_)
   {}

   view_limits icon::limits(basic_context const& ctx) const
   {
      auto& thm = get_theme();
      float font_size = thm.icon_font._size * _size;
      point s = measure_icon(ctx.canvas, _code, font_size);
      return {{s.x, s.y}, {s.x, s.y}};
   }

   void icon::draw(context const& ctx)
   {
      auto& thm = get_theme();
      float font_size = thm.icon_font._size * _size;
      draw_icon(ctx.canvas, ctx.bounds, _code, font_size);
   }
}


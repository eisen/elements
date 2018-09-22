/*=============================================================================
   Copyright (c) 2016-2018 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(PHOTON_GUI_LIB_CIRCLE_APRIL_17_2016)
#define PHOTON_GUI_LIB_CIRCLE_APRIL_17_2016

#include <photon/support/rect.hpp>

namespace photon
{
   ////////////////////////////////////////////////////////////////////////////
   // Circles
   ////////////////////////////////////////////////////////////////////////////
   struct circle
   {
      constexpr   circle();
      constexpr   circle(float cx, float cy, float radius);
      constexpr   circle(point c, float radius);
                  circle(circle const&) = default;
      circle&     operator=(circle const&) = default;

      rect        bounds() const { return { cx-radius, cy-radius, cx+radius, cy+radius }; }
      bool        operator==(circle const& other) const;
      bool        operator!=(circle const& other) const;

      point       center() const;
      circle      inset(float x);
      circle      move(float dx, float dy) const;
      circle      move_to(float x, float y) const;

      float       cx;
      float       cy;
      float       radius;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   inline constexpr circle::circle()
    : cx(0.0), cy(0.0), radius(0.0)
   {}

   inline constexpr circle::circle(float cx, float cy, float radius)
    : cx(cx), cy(cy), radius(radius)
   {}

   inline constexpr circle::circle(point c, float radius)
    : cx(c.x), cy(c.y), radius(radius)
   {}

   inline bool circle::operator==(circle const& other) const
   {
      return (other.cx == cx) && (other.cy == cy) && (other.radius == radius);
   }

   inline bool circle::operator!=(circle const& other) const
   {
      return !(*this == other);
   }

   inline point circle::center() const
   {
      return { cx, cy };
   }

   inline circle circle::inset(float x)
   {
      return { cx, cy, radius-x };
   }

   inline circle circle::move(float dx, float dy) const
   {
      return { cx+dx, cy+dy, radius };
   }

   inline circle circle::move_to(float x, float y) const
   {
      return { x, y, radius };
   }
}
#endif
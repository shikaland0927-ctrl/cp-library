#pragma once
#include "geom/point.hpp"
// snippet: line
const ld eps = 1e-9;

template <typename T = ld> struct Line {
  Point<T> fm, to;
  tuple<T, T, T> coef;

  Line(Point<T> fm = Point<T>(), Point<T> to = Point<T>()) : fm(fm), to(to) {
    T a = fm.y - to.y;
    T b = to.x - fm.x;
    T c = fm ^ to;
    if constexpr (is_integral_v<T>) {
      T g = gcd(a, gcd(b, c));
      if (g > 0) a /= g, b /= g, c /= g;
      if (a < 0 || (a == 0 && b < 0)) a = -a, b = -b, c = -c;
    } else {
      T norm = sqrtl(a * a + b * b);
      if (norm > eps) a /= norm, b /= norm, c /= norm;
      if (a < -eps || (abs(a) <= eps && b < -eps)) a = -a, b = -b, c = -c;
    }
    coef = {a, b, c};
  } 

  Point<T> dir() const { return to - fm; }

  Point<ld> normalize() const {
    assert(fm != to);
    return Point<ld>(dir().x, dir().y) / dir().norm();
  }

  ld len() const { return dir().norm(); }

  ll ccw(const Point<T>& p) const {
    Point<T> d1 = dir();
    Point<T> d2 = p - fm;
    T cr = d1 ^ d2;
    ld e = is_floating_point_v<T> ? eps : 0;
    if (cr > e) return +1;
    if (cr < -e) return -1;
    if (d1 * d2 < -e) return +2;
    if (d1 * (to - p) < -e) return -2;
    return 0;
  }

  bool touch(const Line& l) const { return ccw(l.fm) * ccw(l.to) <= 0 && l.ccw(fm) * l.ccw(to) <= 0; }
};
/*
    -- Constructor --
    Line<T = ld> l(Point<T> fm, Point<T> to)
    Generates a line directed from point 'fm' to point 'to'.
    Generates a member variable 'coef' storing coefficients (a, b, c) for ax + by + c = 0.

    -- Basic Operations --
    Point<T> l.dir()
    Returns the direction vector (to - fm).

    Point<ld> l.normalize()
    Returns a direction vector of length 1 (assert(fm != to)).

    ld l.len()
    Returns the length of the line segment fm-to.

    -- Counter-Clockwise (CCW) --
    ll l.ccw(const Point<T>& p)
    Determines the relative position of point p with respect to the line segment fm-to.
    +1 : p is to the left of the direction fm-to (counter-clockwise)
    -1 : p is to the right of the direction fm-to (clockwise)
    +2 : p is on the line fm-to and behind fm
    -2 : p is on the line fm-to and ahead of to
    0  : p lies on the line segment fm-to (including endpoints)

    -- Line Segment Intersection --
    bool l.touch(const Line<T>& other)
    Determines whether two line segments intersect (returns true even for endpoint touches).
*/

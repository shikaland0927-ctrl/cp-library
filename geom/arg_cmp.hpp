#pragma once
#include "geom/point.hpp"
// snippet: arg_cmp
template <typename T> bool arg_cmp(const Point<T>& a, const Point<T>& b) {
  auto ort = [](const auto& p) {
    if (p.x == 0 && p.y == 0) return 0;
    if (p.y > 0 || (p.y == 0 && p.x > 0)) return 1;
    return 2;
  };
  auto oa = ort(a), ob = ort(b);
  if (oa != ob) return oa < ob;
  T c = a ^ b;
  if (c != 0) return c > 0;
  return a.norm2() < b.norm2();
}
/*
    Uses the Point struct
    sort(all(P), arg_cmp<T>); (Origin -> Argument/Angle -> Distance)
*/

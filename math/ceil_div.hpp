#pragma once
// snippet: ceil
template <typename T> T ceil(T x, T y) {
  assert(y > 0);
  return x / y + (x % y > 0);
}

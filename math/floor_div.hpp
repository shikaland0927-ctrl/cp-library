#pragma once
// snippet: floor
template <typename T> T floor(T x, T y) {
  assert(y > 0);
  return x / y - (x % y < 0);
}

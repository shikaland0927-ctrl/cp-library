#pragma once
// snippet: floor_kth_root
ull floor_kth_root(ull n, ull k) {
  if (n <= 1 || k == 1) return n;
  if (k >= 64) return 1;
  static constexpr auto lim = []() {
    array<ull, 64> res{};
    rep (e, 2, 64) {
      ull ac = 1, wa = 1ULL << 32;
      while (wa - ac > 1) {
        ull wj = (ac + wa) / 2, x = ~0ULL;
        rep (i, e) x /= wj;
        (x >= 1 ? ac : wa) = wj;
      }
      res[e] = wa;
    }
    return res;
  }();
  ull ac = 1, wa = min(n, lim[k]);
  while (wa - ac > 1) {
    ull wj = (ac + wa) / 2, p = 1;
    rep (i, k) p *= wj;
    (p <= n ? ac : wa) = wj;
  }
  return ac;
}

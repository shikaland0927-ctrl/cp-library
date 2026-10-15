#pragma once
// snippet: subset_fmt
template<typename T = ll> void subset_fmt(vector<T>& v) {
  ll m = (ll)v.size();
  assert(m > 0 && (m & (m - 1)) == 0);
  for (ll bit = 1; bit < m; bit <<= 1)
    rep (s, m) if (s & bit) v[s] -= v[s ^ bit];
}

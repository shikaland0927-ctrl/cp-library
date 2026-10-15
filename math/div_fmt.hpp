#pragma once
// snippet: div_fmt
template<typename T = ll> void div_fmt(vector<T>& v) {
  ll n = v.size() - 1;
  vector<bool> isp(n + 1, true);
  rep (p, 2, n + 1) {
    if (!isp[p]) continue;
    rrep (x, n / p + 1, 1) {
      isp[p * x] = false;
      v[p * x] -= v[x];
    }
  }
}

#pragma once
// snippet: div_fzt
template<typename T = ll> void div_fzt(vector<T>& v) {
  ll n = v.size() - 1;
  vector<bool> isp(n + 1, true);
  rep (p, 2, n + 1) {
    if (!isp[p]) continue;
    rep (x, 1, n / p + 1) {
      isp[p * x] = false;
      v[p * x] += v[x];
    }
  }
}

#pragma once
// snippet: pf
vector<pair<ll, ll>> prime_factors(ll n) {
  vector<pair<ll, ll>> res;
  for (ll p = 2; p * p <= n; p++) {
    if (n % p != 0) continue;
    ll ex = 0;
    while (n % p == 0) {
      ex++;
      n /= p;
    }
    res.eb(p, ex);
  }
  if (n != 1) res.eb(n, 1);
  return res;
}

#pragma once
// snippet: pf
vector<pair<ll, ll>> prime_factors(ll n) {
  vector<pair<ll, ll>> res;
  for (ll a = 2; a * a <= n; a++) {
    if (n % a != 0) continue;
    ll ex = 0;
    while (n % a == 0) {
      ex++;
      n /= a;
    }
    res.eb(a, ex);
  }
  if (n != 1) res.eb(n, 1);
  return res;
}

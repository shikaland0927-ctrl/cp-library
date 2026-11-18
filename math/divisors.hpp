#pragma once
// snippet: divisors
vector<ll> divisors(ll n) {
  vector<ll> res;
  for (ll d = 1; d * d <= n; d++) {
    if (n % d == 0) {
      res.eb(d);
      if (d * d != n) res.eb(n / d);
    }
  }
  sort(all(res));
  return res;
}

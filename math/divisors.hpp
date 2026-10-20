#pragma once
// snippet: divisors
vector<ll> divisors(ll n) {
  vector<ll> res;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.eb(i);
      if (i * i != n) res.eb(n / i);
    }
  }
  sort(all(res));
  return res;
}

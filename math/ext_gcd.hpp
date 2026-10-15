#pragma once
// snippet: ext_gcd
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  ll g = ext_gcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}
// find one of (x, y) s.t. ax + by = gcd(a, b)
// O(log min(|a|, |b|))
// max(|x|, |y|) <= max(|a|, |b|)

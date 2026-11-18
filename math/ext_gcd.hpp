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
/*
    ll ext_gcd(ll a, ll b, ll& x, ll& y)
    Time Complexity: O(log min(|a|, |b|))
    Finds one (x, y) such that ax + by = gcd(a, b), and returns gcd(a, b).
    max(|x|, |y|) <= max(|a|, |b|)
*/

#pragma once
// snippet: pow_ll
ll pow_ll(ll a, ll n) {
  ll res = 1;
  while (n) {
    if (n & 1) res *= a;
    a *= a;
    n >>= 1;
  }
  return res;
}

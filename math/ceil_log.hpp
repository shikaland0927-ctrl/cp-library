#pragma once
// snippet: ceil_log
ll ceil_log(ll b, ll n) {
  ll res = 0;
  for (ll x = 1; x < n; res++) {
    if (x > (n - 1) / b) return res + 1;
    x *= b;
  }
  return res;
}

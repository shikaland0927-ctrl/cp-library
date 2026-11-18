#pragma once
// snippet: ceil_log
ll ceil_log(ll b, ll n) {
  ll res = 0;
  for (ll pw = 1; pw < n; res++) {
    if (pw > (n - 1) / b) return res + 1;
    pw *= b;
  }
  return res;
}

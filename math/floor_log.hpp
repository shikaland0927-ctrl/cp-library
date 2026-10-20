#pragma once
// snippet: floor_log
ll floor_log(ll b, ll n) {
  ll res = 0;
  for (ll x = 1; x <= n / b; x *= b) res++;
  return res;
}

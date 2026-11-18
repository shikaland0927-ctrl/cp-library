#pragma once
// snippet: floor_log
ll floor_log(ll b, ll n) {
  ll res = 0;
  for (ll pw = 1; pw <= n / b; pw *= b) res++;
  return res;
}

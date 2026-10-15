#pragma once
// snippet: sqrt_ll
ll sqrt_ll(ll x) {
  ll res = sqrt(x);
  while (res * res > x) res--;
  while ((res + 1) * (res + 1) <= x) res++;
  return res;
}

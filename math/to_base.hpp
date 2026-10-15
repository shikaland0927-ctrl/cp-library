#pragma once
// snippet: to_base
string to_base(ll n, ll base) {
  if (n == 0) return "0";
  string res = "";
  while (n > 0) {
    res += (char)((n % base) + '0');
    n /= base;
  }
  reverse(all(res));
  return res;
}

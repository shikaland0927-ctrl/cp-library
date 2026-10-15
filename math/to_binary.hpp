#pragma once
// snippet: to_binary
string to_binary(ll n) {
  if (!n) return "0";
  string res = "";
  while (n) {
    res += ((n & 1) ? '1' : '0');
    n >>= 1;
  }
  reverse(all(res));
  return res;
}

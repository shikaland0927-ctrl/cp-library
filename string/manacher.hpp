#pragma once
// snippet: manacher
void manacher_check(ll n, const string& s) {  // @nopaste (for checking this file alone; only the body is pasted)
vector<ll> R(n);
ll c = 0, r = 0;
while (c < n) {
  while (c - r >= 0 && c + r < n && s[c - r] == s[c + r]) r++;
  R[c] = r;
  ll k = 1;
  while (c - k >= 0 && k + R[c - k] < r) R[c + k] = R[c - k], k++;
  c += k, r -= k;
}
}  // @nopaste

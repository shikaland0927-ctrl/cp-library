#pragma once
// snippet: cc
void coord_compress(vector<ll>& v) {
  vector<ll> u = v;
  sort(all(u));
  u.erase(unique(all(u)), u.end());
  for (ll& x : v) x = lb(all(u), x) - u.begin();
}

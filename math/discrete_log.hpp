#pragma once
// snippet: discrete_log
ll discrete_log(ll a, ll b, ll m) {
  if (m == 1) return 0;
  a = (a % m + m) % m, b = (b % m + m) % m;
  auto mul = [&](ll x, ll y) { return (ll)((__int128)x * y % m); };
  ll k = 1, add = 0, g;
  while ((g = gcd(a, m)) > 1) {
    if (b == k) return add;
    if (b % g) return -1;
    b /= g, m /= g, add++;
    k = (ll)((__int128)k * (a / g) % m);
  }
  ll n = sqrtl(m) + 1, an = 1;
  rep(n) an = mul(an, a);
  unordered_map<ll, ll> vals;
  vals.reserve(2 * n + 2);
  for (ll q = 0, cur = b; q <= n; q++) {
    vals[cur] = q;
    cur = mul(cur, a);
  }
  for (ll p = 1, cur = k; p <= n; p++) {
    cur = mul(cur, an);
    if (auto it = vals.find(cur); it != vals.end()) return n * p - it->se + add;
  }
  return -1;
}
// min x >= 0 s.t. a^x = b (mod m), -1 if none (0^0 = 1)
// m need not be prime, m <= ~1e12
// O(sqrt(m))

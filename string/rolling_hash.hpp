#pragma once
// snippet: rh
struct RollingHash {
  static const ll mod = (1LL << 61) - 1;
  vector<ll> hash, power;
  ll base;

  RollingHash(const string& s, ll base = 0) : base(base) {
    int n = s.size();
    if (this->base == 0) {
      random_device rd;
      mt19937_64 rng(rd());
      this->base = rng() % (mod - 2) + 2;
    }
    hash.assign(n + 1, 0);
    power.assign(n + 1, 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = mul(hash[i], this->base) + s[i];
      if (hash[i + 1] >= mod) hash[i + 1] -= mod;
      power[i + 1] = mul(power[i], this->base);
    }
  }

  static ll mul(ll a, ll b) {
    __int128_t c = (__int128_t)a * b;
    return add(c >> 61, c & mod);
  }

  static ll add(ll a, ll b) {
    if ((a += b) >= mod) a -= mod;
    return a;
  }

  ll get(int l, int r) { return add(hash[r], mod - mul(hash[l], power[r - l])); }
};
/*
    -- Constructor --
    (1) RollingHash rh(const string& s)
    Time complexity: O(|s|)
    Automatically generates a base using random numbers and builds the hash for string s.

    (2) RollingHash rh(const string& s, ll base)
    Time complexity: O(|s|)
    Constructs using a specified base.
    (* Note: When comparing hash values between multiple strings, a common base must be specified, e.g., rh2(t, rh1.base))

    -- Get Hash Value --
    ll rh.get(int l, int r)
    Time complexity: O(1)
    Returns the hash value of the substring s[l:r] corresponding to the 0-indexed half-open interval [l, r).
*/

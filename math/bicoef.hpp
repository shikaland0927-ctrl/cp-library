#pragma once
// snippet: bc
using mint = modint998244353; // @nopaste (for checking this file alone; define mint yourself)
struct BiCoef {
  vector<mint> fac, finv;
  BiCoef(int n) : fac(n + 1), finv(n + 1) {
    fac[0] = 1;
    rep (i, n) fac[i + 1] = fac[i] * (i + 1);
    finv[n] = fac[n].inv();
    rrep (i, n) finv[i] = finv[i + 1] * (i + 1);
  }

  mint C(ll n, ll k) {
    if (n < k || n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
  }

  mint P(ll n, ll k) {
    if (n < k || n < 0 || k < 0) return 0;
    return fac[n] * finv[n - k];
  }

  mint H(ll n, ll k) {
    if (n == 0 && k == 0) return 1;
    if (n <= 0 || k < 0) return 0;
    return C(n + k - 1, k);
  }
};
/*
    -- Constructor --
    BiCoef bc(int n)
    Time complexity: O(n log mod) (To be used when n is small enough to build a table, suitable for queries)

    -- Factorials and their inverses --
    vector<mint> fac
    vector<mint> finv

    -- Combinatorics (Number of ways) --
    mint C(ll n, ll k)
    mint P(ll n, ll k)
    mint H(ll n, ll k)
*/

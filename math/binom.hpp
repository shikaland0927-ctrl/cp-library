#pragma once
// snippet: binom
using mint = modint998244353; // @nopaste（単体確認用。mint は自分で定義しておく）
template<class T = mint>
T binom(ll n, ll k) {
  if (k < 0 || n < k) return 0;
  if (k > n - k) k = n - k;
  T res = 1;
  rep (i, k) res = res * (n - i) / (i + 1);
  return res;
}
/*
    T binom<T>(ll n, ll k)
    Time complexity: O(min(k, n - k)) (To be used when n is huge and a table cannot be built, but k is small)
*/

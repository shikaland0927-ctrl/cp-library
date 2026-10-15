#pragma once
// snippet: fact
using mint = modint998244353;  // @nopaste（単体確認用。mint は自分で定義しておく）
void fact_check(ll n) {  // @nopaste（単体確認用。貼るときは中身だけになる）
vector<mint> fac(n + 1), finv(n + 1);
fac[0] = 1;
rep (i, n) fac[i + 1] = fac[i] * (i + 1);
finv[n] = fac[n].inv();
rrep (i, n) finv[i] = finv[i + 1] * (i + 1);
}  // @nopaste

#pragma once
// snippet: euler_tour
void euler_tour_check(ll n, const vector<vector<ll>>& g, const vector<ll>& A) {  // @nopaste（単体確認用。貼るときは中身だけになる）
vector<ll> in(n), out(n), tour;
auto dfs = [&](this auto& dfs, ll v = 0, ll p = -1) -> void {
  in[v] = tour.size();
  tour.eb(A[v]);
  for (const ll& nv : g[v]) if (nv != p) dfs(nv, v);
  out[v] = tour.size();
};
dfs();
}  // @nopaste

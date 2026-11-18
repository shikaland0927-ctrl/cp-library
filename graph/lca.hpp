#pragma once
// snippet: lca
template <typename S, S (*op)(S, S), S (*e)()> struct LCA {
  ll n, log_size;
  vector<vector<pair<ll, S>>> g;
  vector<vector<ll>> parent;
  vector<vector<S>> dat;
  vector<ll> depth;

  LCA(ll n) : n(n), g(n), depth(n) {
    log_size = 1;
    while ((1LL << log_size) < n) log_size++;
    parent.assign(log_size, vector<ll>(n, -1));
    dat.assign(log_size, vector<S>(n, e()));
  }

  void add_edge(ll u, ll v, S cost = 1) {
    g[u].eb(v, cost);
    g[v].eb(u, cost);
  }

  void build(ll root = 0) {
    dat[0][root] = e();
    dfs(root, -1, 0);
    rep (i, log_size - 1) rep (v, n) {
      if (parent[i][v] < 0) {
        parent[i + 1][v] = -1;
        dat[i + 1][v] = dat[i][v];
      } else {
        parent[i + 1][v] = parent[i][parent[i][v]];
        dat[i + 1][v] = op(dat[i][v], dat[i][parent[i][v]]);
      }
    }
  }

  void dfs(ll u, ll p, ll d) {
    parent[0][u] = p;
    depth[u] = d;
    for (auto& [v, cost] : g[u]) {
      if (v == p) continue;
      dat[0][v] = cost;
      dfs(v, u, d + 1);
    }
  }

  ll lca(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    ll diff = depth[u] - depth[v];
    rep (i, log_size) if ((diff >> i) & 1) u = parent[i][u];
    if (u == v) return u;
    rrep (i, log_size) if (parent[i][u] != parent[i][v]) {
      u = parent[i][u];
      v = parent[i][v];
    }
    return parent[0][u];
  }

  S prod_up(ll v, ll k) {
    S res = e();
    rep (i, log_size) {
      if ((k >> i) & 1) {
        if (v < 0) break;
        res = op(res, dat[i][v]);
        v = parent[i][v];
      }
    }
    return res;
  }

  S prod(ll u, ll v) {
    ll l = lca(u, v);
    return op(prod_up(u, depth[u] - depth[l]), prod_up(v, depth[v] - depth[l]));
  }
};
/*
    -- Constructor --
    LCA<S, op, e> tree(ll n)
    Time Complexity: O(N log N)

    -- Adding Edges --
    void tree.add_edge(ll u, ll v, S cost = 1)

    -- Build --
    void tree.build(ll root = 0)
    Time Complexity: O(N log N)
    Constructs the doubling table and monoid products.

    -- Get LCA --
    ll tree.lca(ll u, ll v)
    Time Complexity: O(log N)

    -- Get Monoid Product --
    S tree.prod_up(ll v, ll k)
    Time Complexity: O(log N)
    Returns the monoid product of the path tracing up to the parent k times from vertex v.

    S tree.prod(ll u, ll v)
    Time Complexity: O(log N)
    Returns the monoid product of the path between vertices u and v (restricted to commutative monoids).
*/

using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

#pragma once
// snippet: tree_diameter
template <typename T = ll> struct TreeDiameter {
  vector<vector<pair<ll, T>>> g;
  ll n, ep1, ep2;
  T dia;
  vector<ll> parent;

  TreeDiameter(ll n) : g(n), n(n), parent(n) {}

  void add_edge(ll u, ll v, T cost = 1) {
    g[u].eb(v, cost);
    g[v].eb(u, cost);
  }

  void build() {
    auto [_, u] = bfs(0);
    auto [d, v] = bfs(u);
    dia = d;
    ep1 = u;
    ep2 = v;
  }

  pair<T, ll> bfs(ll s) {
    parent.assign(n, -1);
    vector<T> dist(n, 0);
    queue<ll> q;
    q.em(s);
    pair<T, ll> res = {0, s};
    while (q.size()) {
      ll u = q.front(); q.pop();
      if (dist[u] > res.fi) res = {dist[u], u};
      for (auto [v, cost] : g[u]) if (v != parent[u]) {
        dist[v] = dist[u] + cost;
        parent[v] = u;
        q.em(v);
      }
    }
    return res;
  }

  vector<ll> get_path() {
    vector<ll> path;
    for (ll v = ep2; v != -1; v = parent[v]) path.eb(v);
    reverse(all(path));
    return path;
  }

  vector<ll> get_center() {
    vector<ll> path = get_path();
    ll m = path.size();
    if (m & 1) return {path[m / 2]};
    return {path[m / 2 - 1], path[m / 2]};
  }

  vector<T> get_distance(ll s) {
    vector<T> dist(n, -1);
    queue<ll> q;
    q.em(s);
    dist[s] = 0;
    while (q.size()) {
      ll u = q.front(); q.pop();
      for (auto [v, cost] : g[u]) if (dist[v] == -1) {
        dist[v] = dist[u] + cost;
        q.em(v);
      }
    }
    return dist;
  }

  vector<pair<T, ll>> get_farthest() {
    vector<T> dist1 = get_distance(ep1);
    vector<T> dist2 = get_distance(ep2);
    vector<pair<T, ll>> res(n);
    rep (v, n) {
      if (dist1[v] > dist2[v]) res[v] = {dist1[v], ep1};
      else res[v] = {dist2[v], ep2};
    }
    return res;
  }
};
/*
    -- Constructor --
    TreeDiameter<T = ll> tree(ll n)

    -- Add Edge --
    void tree.add_edge(ll u, ll v, T cost = 1)
    
    -- Tree Endpoints, Diameter --
    void tree.build()
    Time Complexity: O(n)
    Computes the following member variables
     - Tree endpoints: ep1, ep2
     - Tree diameter: dia

    -- Get Diameter Path (Requires build) --
    vector<ll> tree.get_path()
    Time Complexity: Worst-case O(n)

    -- Tree Center (Requires build) --
    vector<ll> tree.get_center()
    Time Complexity: Worst-case O(n)
    Returns 1 element if the number of vertices in the diameter path is odd, and 2 elements if even.

    -- Distance from Specified Vertex (Requires build) --
    vector<T> tree.get_distance(ll s)
    Time Complexity: O(n)
    Returns an array of distances from vertex s to each vertex.

    -- Farthest Vertex for Each Vertex (Requires build) --
    vector<pair<T, ll>> tree.get_farthest()
    Time Complexity: O(n)
    For each vertex i, returns {distance to the farthest vertex, farthest vertex}.
*/

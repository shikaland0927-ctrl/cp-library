#pragma once
// snippet: tree_diameter
template <typename T = ll> struct TreeDiameter {
  vector<vector<pair<ll, T>>> g;
  ll n, ep1, ep2;
  T dia;
  vector<ll> parent;

  TreeDiameter(ll n) : g(n), n(n), parent(n) {}

  void add_edge(ll a, ll b, T cost = 1) {
    g[a].eb(b, cost);
    g[b].eb(a, cost);
  }

  void build() {
    auto [_, u] = bfs(0);
    auto [d, v] = bfs(u);
    dia = d;
    ep1 = u;
    ep2 = v;
  }

  pair<T, ll> bfs(ll u) {
    parent.assign(n, -1);
    vector<T> dist(n, 0);
    queue<ll> q;
    q.push(u);
    pair<T, ll> res = {0, u};
    while (q.size()) {
      ll v = q.front(); q.pop();
      if (dist[v] > res.fi) res = {dist[v], v};
      for (auto [nv, cost] : g[v]) if (nv != parent[v]) {
        dist[nv] = dist[v] + cost;
        parent[nv] = v;
        q.push(nv);
      }
    }
    return res;
  }

  vector<ll> get_path() {
    vector<ll> path;
    ll v = ep2;
    while (v != -1) {
      path.eb(v);
      v = parent[v];
    }
    reverse(all(path));
    return path;
  }

  vector<ll> get_center() {
    vector<ll> path = get_path();
    ll m = path.size();
    if (m & 1) return {path[m / 2]};
    return {path[m / 2 - 1], path[m / 2]};
  }

  vector<T> get_distance(ll start) {
    vector<T> dist(n, -1);
    queue<ll> q;
    q.em(start);
    dist[start] = 0;
    while (q.size()) {
      ll v = q.front(); q.pop();
      for (auto [nv, cost] : g[v]) if (dist[nv] == -1) {
        dist[nv] = dist[v] + cost;
        q.em(nv);
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
    Time complexity: O(n)
    Computes the following member variables
     - Tree endpoints: ep1, ep2
     - Tree diameter: dia

    -- Get Diameter Path (Requires build) --
    vector<ll> tree.get_path()
    Time complexity: Worst-case O(n)

    -- Tree Center (Requires build) --
    vector<ll> tree.get_center()
    Time complexity: Worst-case O(n)
    Returns 1 element if the number of vertices in the diameter path is odd, and 2 elements if even.

    -- Distance from Specified Vertex (Requires build) --
    vector<T> tree.get_distance(ll v);
    Time complexity: O(n)
    Returns an array of distances from vertex v to each vertex.

    -- Farthest Vertex for Each Vertex (Requires build) --
    vector<pair<T, ll>> tree.get_farthest();
    Time complexity: O(n)
    For each vertex i, returns {distance to the farthest vertex, farthest vertex}.
*/

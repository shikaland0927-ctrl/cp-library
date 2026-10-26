#pragma once
// snippet: graph
struct Graph {
  ll n;
  vector<vector<pair<ll, ll>>> to;
  vector<ll> dist, pre;

  Graph(ll n) : n(n), to(n), dist(n, inf), pre(n, -1) {}

  void add_edge(ll u, ll v, ll w = 1) { to[u].eb(v, w); }

  vector<ll> bfs(ll s = 0) {
    dist[s] = 0;
    queue<ll> q;
    q.em(s);
    while (q.size()) {
      ll u = q.front(); q.pop();
      for (const auto& [v, cost] : to[u]) {
        assert(cost == 1);
        if (chmin(dist[v], dist[u] + cost)) {
          pre[v] = u;
          q.em(v);
        }
      }
    }
    return dist;
  }

  vector<ll> bfs01(ll s = 0) {
    dist[s] = 0;
    deque<ll> dq;
    dq.eb(s);
    while (dq.size()) {
      ll u = dq.front(); dq.pf();
      for (const auto& [v, cost] : to[u]) {
        assert(cost == 0 || cost == 1);
        if (chmin(dist[v], dist[u] + cost)) {
          pre[v] = u;
          if (cost == 0) dq.ef(v);
          else dq.eb(v);
        }
      }
    }
    return dist;
  }

  vector<ll> dijkstra(ll s = 0) {
    dist[s] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.em(0, s);
    while (pq.size()) {
      auto [d, u] = pq.top(); pq.pop();
      if (dist[u] < d) continue;
      for (const auto& [v, cost] : to[u]) {
        assert(cost >= 0);
        if (chmin(dist[v], d + cost)) {
          pre[v] = u;
          pq.em(dist[v], v);
        }
      }
    }
    return dist;
  }

  vector<ll> bellman_ford(ll s = 0) {
    dist[s] = 0;
    rep (n - 1) {
      bool update = false;
      rep(u, n) {
        if (dist[u] == inf) continue;
        for (const auto& [v, cost] : to[u]) if (chmin(dist[v], dist[u] + cost)) {
          pre[v] = u;
          update = true;
        }
      }
      if (!update) break;
    }
    rep(n) rep(v, n) {
      if (dist[v] == inf) continue;
      for (const auto& [nv, cost] : to[v])
        if (dist[v] == -inf || dist[nv] > dist[v] + cost) dist[nv] = -inf;
    }
    return dist;
  }

  vector<ll> topological_sort() const {
    vector<ll> indegree(n);
    rep(v, n) for (const auto& edge : to[v]) indegree[edge.fi]++;

    queue<ll> q;
    // lexicographically smallest
    // priority_queue<ll, vector<ll>, greater<>> q;
    rep(v, n) if (indegree[v] == 0) q.em(v);

    vector<ll> order;
    while (q.size()) {
      ll u = q.front(); q.pop();
      order.eb(u);
      for (const auto& edge : to[u]) {
        ll v = edge.fi;
        if (--indegree[v] == 0) q.em(v);
      }
    }
    if (ssize(order) != n) return {};
    return order;
  }

  vector<ll> get_path(ll t) {
    if (dist[t] == inf) return {};
    vector<ll> path;
    for (ll v = t; v != -1; v = pre[v]) path.eb(v);
    reverse(all(path));
    return path;
  }
};
// add_edge is directed

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
      ll v = q.front(); q.pop();
      for (const auto& [nv, cost] : to[v]) {
        assert(cost == 1);
        if (chmin(dist[nv], dist[v] + cost)) {
          pre[nv] = v;
          q.em(nv);
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
      ll v = dq.front(); dq.pop_front();
      for (const auto& [nv, cost] : to[v]) {
        assert(cost == 0 || cost == 1);
        if (chmin(dist[nv], dist[v] + cost)) {
          pre[nv] = v;
          if (cost == 0) dq.ef(nv);
          else dq.eb(nv);
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
      auto [d, v] = pq.top(); pq.pop();
      if (dist[v] < d) continue;
      for (const auto& [nv, cost] : to[v]) {
        assert(cost >= 0);
        if (chmin(dist[nv], d + cost)) {
          pre[nv] = v;
          pq.em(dist[nv], nv);
        }
      }
    }
    return dist;
  }

  vector<ll> bellman_ford(ll s = 0) {
    dist[s] = 0;
    rep (n - 1) {
      bool update = false;
      rep(v, n) {
        if (dist[v] == inf) continue;
        for (const auto& [nv, cost] : to[v]) if (chmin(dist[nv], dist[v] + cost)) {
          pre[nv] = v;
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
    rep(v, n) for (const auto& edge : to[v]) ++indegree[edge.fi];

    queue<ll> q;
    // lexicographically smallest
    // priority_queue<ll, vector<ll>, greater<>> q;
    rep(v, n) if (indegree[v] == 0) q.em(v);

    vector<ll> order;
    while (q.size()) {
      ll v = q.front(); q.pop();
      order.eb(v);
      for (const auto& edge : to[v]) {
        ll nv = edge.fi;
        if (--indegree[nv] == 0) q.em(nv);
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

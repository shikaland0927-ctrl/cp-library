#pragma once
// snippet: dijkstra
vector<ll> dijkstra(const vector<vector<pair<ll, ll>>>& g, ll s = 0) {
  vector<ll> dist(g.size(), inf);
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
  dist[s] = 0;
  pq.em(0, s);
  while (pq.size()) {
    auto [d, v] = pq.top(); pq.pop();
    if (dist[v] < d) continue;
    for (auto [u, cost] : g[v])
      if (chmin(dist[u], dist[v] + cost)) pq.em(dist[u], u);
  }
  return dist;
}

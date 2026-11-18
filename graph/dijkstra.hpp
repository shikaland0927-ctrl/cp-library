#pragma once
// snippet: dijkstra
vector<ll> dijkstra(const vector<vector<pair<ll, ll>>>& g, ll s = 0) {
  vector<ll> dist(g.size(), inf);
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
  dist[s] = 0;
  pq.em(0, s);
  while (pq.size()) {
    auto [d, u] = pq.top(); pq.pop();
    if (dist[u] < d) continue;
    for (auto [v, cost] : g[u])
      if (chmin(dist[v], d + cost)) pq.em(dist[v], v);
  }
  return dist;
}

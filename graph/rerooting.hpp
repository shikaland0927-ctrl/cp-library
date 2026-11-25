#pragma once
// snippet: rerooting
template <typename E,
          typename V,
          E (*merge)(E, E),
          E (*e)(),
          E (*put_edge)(V, ll),
          V (*put_vertex)(E, ll)>
struct Rerooting {
  struct Edge {
    ll to, id, rev_id;
  };

  ll n, root;
  vector<vector<Edge>> g;
  vector<Edge> es;
  vector<ll> start, outs_pos;
  vector<E> outs, reverse_edge;
  vector<V> subdp, answers;

  Rerooting(ll n) : n(n), g(n) {}

  void add_edge(ll u, ll v, ll id = -1, ll rev_id = -1) {
    g[u].eb(v, id, rev_id);
    g[v].eb(u, rev_id, id);
  }

  void build(ll root = 0) {
    this->root = root;
    start.assign(n + 1, 0);
    rep (v, n) start[v + 1] = g[v].size();
    rep (v, n) start[v + 1] += start[v];
    es.resize(2 * n - 2);
    vector<ll> pos = start;
    rep (v, n) {
      for (auto& edge : g[v]) {
        es[pos[v]++] = edge;
      }
    }
    subdp.resize(n);
    subdp[0] = put_vertex(e(), 0);
    outs.resize(n);
    outs_pos.assign(n + 1, 0);
    rep (v, n) outs_pos[v + 1] = start[v + 1] - start[v] - 1;
    outs_pos[root + 1]++;
    rep (v, n) outs_pos[v + 1] += outs_pos[v];
    dfs(root, -1);
  }

  void dfs(ll v, ll p) {
    E val = e();
    rep (i, start[v], start[v + 1]) {
      if (es[i].to == p) {
        swap(es[start[v + 1] - 1], es[i]);
      }
      if (es[i].to == p) continue;
      dfs(es[i].to, v);
      E nval = put_edge(subdp[es[i].to], es[i].id);
      outs[outs_pos[v]++] = nval;
      val = merge(val, nval);
    }
    subdp[v] = put_vertex(val, v);
  }

  vector<V> reroot() {
    reverse_edge.assign(n, e());
    answers.resize(n);
    reroot_rec(root);
    return answers;
  }

  void reroot_rec(ll v) {
    ll l = outs_start(v);
    ll r = outs_start(v + 1);
    ll sz = r - l;
    vector<E> suf(sz + 1);
    suf[sz] = e();
    rrep (i, sz) {
      suf[i] = merge(outs[l + i], suf[i + 1]);
    }
    answers[v] = put_vertex(merge(suf[0], reverse_edge[v]), v);
    E pref = e();
    rep (i, sz) {
      V rdp = put_vertex(merge(merge(pref, suf[i + 1]), reverse_edge[v]), v);
      reverse_edge[es[start[v] + i].to] = put_edge(rdp, es[start[v] + i].rev_id);
      pref = merge(pref, outs[l + i]);
      reroot_rec(es[start[v] + i].to);
    }
  }

private:
  ll outs_start(ll v) {
    ll res = start[v] - v;
    if (root < v) res++;
    return res;
  }
};
/*
    -- Template parameters --
    E                          : Type of the data associated with the subtree + edge
    V                          : Type of the data associated with the subtree
    E merge(E a, E b)          : Merges two edge data values, a and b
    E e()                      : Returns the identity element of merge
    E put_edge(V v, ll e_id)   : Converts vertex data v into edge data for edge e_id
    V put_vertex(E x, ll v_id) : Converts aggregated edge data x into vertex data for vertex v_id

    -- Constructor --
    Rerooting<E, V, merge, e, put_edge, put_vertex> tree(ll n)

    -- Add an edge --
    void tree.add_edge(ll u, ll v, ll id = -1, ll rev_id = -1)
    id: directed edge ID for u -> v; rev_id: directed edge ID for v -> u

    -- Build --
    void tree.build(ll root = 0)
    Time Complexity: O(N)

    -- Run rerooting DP (requires build) --
    vector<V> tree.reroot()
    Time Complexity: O(N)
    Returns the rerooting DP result for every vertex used as the root
*/

using E = ll;
using V = ll;
E merge(E a, E b) { return a + b; }
E e() { return 0; }
E put_edge(V v, ll e_id) { return v; }
V put_vertex(E x, ll v_id) { return x; }

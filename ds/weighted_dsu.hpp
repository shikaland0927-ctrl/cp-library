#pragma once
// snippet: wdsu
template <typename T = ll> struct wdsu {
  vector<ll> parent_or_size;
  vector<T> diff_weight;

  wdsu(ll n) : parent_or_size(n, -1), diff_weight(n, 0) {}

  ll leader(ll v) {
    if (parent_or_size[v] < 0) return v;
    ll r = leader(parent_or_size[v]);
    diff_weight[v] += diff_weight[parent_or_size[v]];
    return parent_or_size[v] = r;
  }

  T weight(ll v) {
    leader(v);
    return diff_weight[v];
  }

  bool same(ll u, ll v) { return leader(u) == leader(v); }

  bool merge(ll u, ll v, T w) {
    w += weight(u);
    w -= weight(v);
    u = leader(u);
    v = leader(v);
    if (u == v) return false;
    if (-parent_or_size[u] < -parent_or_size[v]) {
      swap(u, v);
      w = -w;
    }
    parent_or_size[u] += parent_or_size[v];
    parent_or_size[v] = u;
    diff_weight[v] = w;
    return true;
  }

  T diff(ll u, ll v) { return weight(v) - weight(u); }

  ll size(ll v) { return -parent_or_size[leader(v)]; }
};
/*
    -- Constructor --
    wdsu<T = ll> uf(ll n)

    -- Leader (Root) --
    ll uf.leader(ll v)

    -- Group Check --
    bool uf.same(ll u, ll v)
    Time complexity: Amortized O(α(n))

    -- Weighted Merge --
    bool uf.merge(ll u, ll v, T w)
    Time complexity: Amortized O(α(n))
    Merges the groups of u and v such that weight(u) + w = weight(v).
    Returns false if they already belong to the same group, and true if newly merged.

    -- Get Weight Difference --
    T uf.diff(ll u, ll v)
    Time complexity: Amortized O(α(n))
    Returns the weight from u to v (weight(v) - weight(u)) (assert(same(u, v))).

    -- Size of Connected Component --
    ll uf.size(ll v)
    Time complexity: Amortized O(α(n))
    Returns the number of elements in the group to which v belongs.
*/

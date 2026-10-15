#pragma once
// snippet: merge_sort_tree
struct MergeSortTree {
  ll n;
  vector<vector<ll>> tree;

  MergeSortTree(const vector<ll>& v) : n(v.size()), tree(2 * n) {
    rep(i, n) tree[n + i] = {v[i]};
    rrep(i, n, 1) {
      tree[i].resize(tree[2 * i].size() + tree[2 * i + 1].size());
      merge(all(tree[2 * i]), all(tree[2 * i + 1]), tree[i].begin());
    }
  }

  ll cnt_lower(ll l, ll r, ll x) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res += lb(all(tree[l]), x) - tree[l].begin();
        l++;
      }
      if (r & 1) {
        r--;
        res += lb(all(tree[r]), x) - tree[r].begin();
      }
    }
    return res;
  }
};
/*
    -- Constructor --
    MergeSortTree mst(vector<ll> v)
    Time Complexity: O(N log(N))

    -- Frequencies --
    ll mst.cnt_lower(ll l, ll r, ll x)
    Time Complexity: O(log^2(N))
    Returns the number of elements strictly less than `x` in the range [l, r).
*/

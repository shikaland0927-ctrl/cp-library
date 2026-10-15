#pragma once
// snippet: interval_map
template<typename T = ll, typename V = ll> struct IntervalMap {
  struct Node {
    T l;
    mutable T r;
    mutable V val;
    Node(T l, T r, V val) : l(l), r(r), val(val) {}
    bool operator<(const Node& node) const { return l < node.l; }
  };

  const V null;
  set<Node> st;

  IntervalMap(V null = -1) : null(null) {}
  IntervalMap(const vector<V>& v, V null = -1) : null(null) {
    for (ll l = 0, r = 0; l < (ll)v.size(); l = r) {
      while (r < (ll)v.size() && v[r] == v[l]) r++;
      if (v[l] != null) st.emplace_hint(st.end(), l, r, v[l]);
    }
  }

  auto get(T x) const {
    auto it = st.ub(Node(x, x, null));
    if (it == st.begin()) return st.end();
    it--;
    return x < it->r ? it : st.end();
  }

  V get_val(T x) const {
    auto it = get(x);
    return it == st.end() ? null : it->val;
  }

  T mex(T x = 0) const {
    auto it = get(x);
    if (it == st.end()) return x;
    T r = it->r;
    while (++it != st.end() && it->l == r) r = it->r;
    return r;
  }

  auto split(T x) {
    auto it = st.lb(Node(x, x, null));
    if (it == st.begin()) return it;
    auto p = prev(it);
    if (p->r <= x) return it;
    T r = exchange(p->r, x);
    return st.emplace_hint(it, x, r, p->val);
  }

  void erase(T l, T r) {
    if (l >= r) return;
    auto it = split(r);
    st.erase(split(l), it);
  }

  void update(T l, T r, V v) {
    if (l >= r) return;
    auto it = split(r);
    it = st.erase(split(l), it);
    if (v == null) return;
    if (it != st.end() && it->l == r && it->val == v) {
      r = it->r;
      it = st.erase(it);
    }
    if (it != st.begin() && prev(it)->r == l && prev(it)->val == v) prev(it)->r = r;
    else st.emplace_hint(it, l, r, v);
  }
};
/*
    -- Template Parameters --
    T : Type of coordinates
    V : Type of values (requires ==)

    -- Constructor --
    (1) IntervalMap<T = ll, V = ll> imp(V null = -1)
    Generates an empty map. Uncovered points have the value null.

    (2) IntervalMap<T = ll, V = ll> imp(const vector<V>& v, V null = -1)
    Generates a map whose value at i is v[i] (points with v[i] == null are uncovered).
    Time Complexity: O(|v|)

    null must not be used as the value of a covered point.
    N is the number of stored intervals.

    -- Update Interval --
    void imp.update(T l, T r, V v)
    Time Complexity: Amortized O(log N)
    Sets all values in [l, r) to v, merging adjacent intervals with the same value.
    update(l, r, null) is the same as erase(l, r).

    -- Erase Interval --
    void imp.erase(T l, T r)
    Time Complexity: Amortized O(log N)
    Makes all points in [l, r) uncovered.

    -- Get Value --
    V imp.get_val(T x)
    Time Complexity: O(log N)
    Returns the value at x, or null if x is uncovered.

    -- Minimum Excluded Value --
    T imp.mex(T x = 0)
    Time Complexity: O(log N + K) (K: number of consecutive intervals from x)
    Returns the smallest value >= x that is uncovered.

    -- Get Interval --
    auto imp.get(T x)
    Time Complexity: O(log N)
    Returns the iterator to the interval containing x (it->l, it->r, it->val), or imp.st.end() if none.

    -- Split --
    auto imp.split(T x)
    Time Complexity: O(log N)
    Splits the interval containing x at x, and returns the iterator to the first interval with l >= x.
    The intervals in [l, r) can be visited by:
    auto itr = imp.split(r);
    for (auto it = imp.split(l); it != itr; it++)
*/

#pragma once
// snippet: interval_set
template<typename T = ll> struct IntervalSet {
  struct Node {
    T l;
    mutable T r;
    Node(T l, T r) : l(l), r(r) {}
    bool operator<(const Node& node) const { return l < node.l; }
  };

  set<Node> st;

  auto get(T x) const {
    auto it = st.ub(Node(x, x));
    if (it == st.begin()) return st.end();
    it--;
    return x < it->r ? it : st.end();
  }

  bool contains(T x) const { return get(x) != st.end(); }
  bool contains(T l, T r) const {
    if (l >= r) return true;
    auto it = get(l);
    return it != st.end() && r <= it->r;
  }

  bool same(T x, T y) const {
    auto it = get(x);
    return it != st.end() && it == get(y);
  }

  T mex(T x = 0) const {
    auto it = get(x);
    return it == st.end() ? x : it->r;
  }

  void erase(T l, T r) {
    if (l >= r) return;
    auto it = split(r);
    st.erase(split(l), it);
  }

  void insert(T l, T r) {
    if (l >= r) return;
    auto it = split(r);
    it = st.erase(split(l), it);
    if (it != st.end() && it->l == r) {
      r = it->r;
      it = st.erase(it);
    }
    if (it != st.begin() && prev(it)->r == l) prev(it)->r = r;
    else st.emplace_hint(it, l, r);
  }

private:
  auto split(T x) {
    auto it = st.lb(Node(x, x));
    if (it == st.begin()) return it;
    auto p = prev(it);
    if (p->r <= x) return it;
    T r = exchange(p->r, x);
    return st.emplace_hint(it, x, r);
  }
};
/*
    -- Constructor --
    IntervalSet<T = ll> ist
    Manages a set of points as disjoint intervals [l, r). Adjacent intervals are always merged.
    N is the number of stored intervals.

    -- Insert Interval --
    void ist.insert(T l, T r)
    Time Complexity: Amortized O(log N)
    Adds all x in [l, r).

    -- Erase Interval --
    void ist.erase(T l, T r)
    Time Complexity: Amortized O(log N)
    Removes all x in [l, r).

    -- Membership --
    bool ist.contains(T x)
    bool ist.contains(T l, T r)
    Time Complexity: O(log N)
    Checks whether x or all of [l, r) is contained.

    -- Same Interval --
    bool ist.same(T x, T y)
    Time Complexity: O(log N)
    Checks whether x and y belong to the same stored interval.

    -- Minimum Excluded Value --
    T ist.mex(T x = 0)
    Time Complexity: O(log N)
    Returns the smallest value >= x not contained in the set.

    -- Get Interval --
    auto ist.get(T x)
    Time Complexity: O(log N)
    Returns the iterator to the interval containing x (it->l, it->r), or ist.st.end() if none.
*/

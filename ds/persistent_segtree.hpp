#pragma once
// snippet: persistent_segtree
template <class S, S (*op)(S, S), S (*e)()> struct PersistentSegtree {
  private:
    struct Node {
      ll lc, rc;
      S val;
    };

    ll n;
    vector<Node> nodes;
    vector<ll> roots;

    ll build(ll l, ll r) {
      ll u = nodes.size();
      nodes.eb(-1, -1, e());
      if (r - l <= 1) return u;
      ll m = l + (r - l) / 2;
      ll lc = build(l, m);
      ll rc = build(m, r);
      nodes[u].lc = lc;
      nodes[u].rc = rc;
      return u;
    }
    
    ll build(const vector<S>& v, ll l, ll r) {
      ll u = nodes.size();
      nodes.eb(-1, -1, e());
      if (r - l <= 1) {
        if (r > l) nodes[u].val = v[l]; 
        return u;
      }
      ll m = l + (r - l) / 2;
      ll lc = build(v, l, m);
      ll rc = build(v, m, r);
      nodes[u].lc = lc;
      nodes[u].rc = rc;
      nodes[u].val = op(nodes[lc].val, nodes[rc].val);
      return u;
    }

    ll _set(ll u, ll l, ll r, ll p, S x) {
      ll v = nodes.size();
      nodes.eb(nodes[u]);
      if (r - l == 1) {
        nodes[v].val = x;
        return v;
      }
      ll m = l + (r - l) / 2;
      if (p < m) nodes[v].lc = _set(nodes[u].lc, l, m, p, x);
      else nodes[v].rc = _set(nodes[u].rc, m, r, p, x);
      nodes[v].val = op(nodes[nodes[v].lc].val, nodes[nodes[v].rc].val);
      return v;
    }

    S _get(ll u, ll l, ll r, ll p) const {
      if (r - l == 1) return nodes[u].val;
      ll m = l + (r - l) / 2;
      if (p < m) return _get(nodes[u].lc, l, m, p);
      return _get(nodes[u].rc, m, r, p);
    }

    S _prod(ll u, ll l, ll r, ll ql, ll qr) const {
      if (qr <= l || r <= ql) return e();
      if (ql <= l && r <= qr) return nodes[u].val;
      ll m = l + (r - l) / 2;
      return op(_prod(nodes[u].lc, l, m, ql, qr), _prod(nodes[u].rc, m, r, ql, qr));
    }

  public:
    PersistentSegtree() : n(0) {}
    explicit PersistentSegtree (ll n) : n(n) { roots.eb(build(0, n)); }
    explicit PersistentSegtree (const vector<S>& v) : n(v.size()) { roots.eb(build(v, 0, n)); }

    ll set(ll version, ll p, S x) {
      assert(0 <= p && p < n);
      assert(0 <= version && version < ssize(roots));
      ll new_root = _set(roots[version], 0, n, p, x);
      roots.eb(new_root);
      return roots.size() - 1;
    }

    S get(ll version, ll p) const {
      assert(0 <= p && p < n);
      assert(0 <= version && version < ssize(roots));
      return _get(roots[version], 0, n, p);
    }

    S prod(ll version, ll l, ll r) const {
      assert(0 <= l && l <= r && r <= n);
      assert(0 <= version && version < ssize(roots));
      return _prod(roots[version], 0, n, l, r);
    }

    S all_prod(ll version) const {
      assert(0 <= version && version < ssize(roots));
      return nodes[roots[version]].val;
    }

    ll version_count() const { return roots.size(); }
};
/*
    -- Constructor --
    PersistentSegtree<S, op, e> seg()
    PersistentSegtree<S, op, e> seg(ll n)
    PersistentSegtree<S, op, e> seg(const vector<S>& v)
    Time Complexity: O(n)
    Constructs the initial state (Version 0).

    -- Element Update --
    ll seg.set(ll version, ll p, S x)
    Time Complexity: O(log n)
    Creates a new version from the specified version's state by updating the p-th element to x,
    and returns the new version number.

    -- Element Access --
    S seg.get(ll version, ll p)
    Time Complexity: O(log n)
    Returns the value of the p-th element in the specified version's state.

    -- Range Product --
    S seg.prod(ll version, ll l, ll r)
    Time Complexity: O(log n)
    Returns the product of the monoid elements in the half-open interval [l, r) for the specified version's state.

    -- All Product --
    S seg.all_prod(ll version)
    Time Complexity: O(1)
    Returns the product of all monoid elements for the specified version's state.

    -- Get Version Count --
    ll seg.version_count()
    Time Complexity: O(1)
    Returns the total number of versions currently stored.
*/

using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

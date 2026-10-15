#pragma once
// snippet: mo
struct Mo {
  ll n, block_size;
  vector<ll> L, R, ord;

  Mo(ll n) : n(n) {}

  void add_query(ll l, ll r) {
    L.eb(l);
    R.eb(r);
  }

  void build() {
    ll q = L.size();
    block_size = max(1LL, ll(n / sqrt(max(1LL, q))));
    ord.resize(q);
    iota(all(ord), 0);
    sort(all(ord), [&](ll i, ll j) {
      ll b_i = L[i] / block_size;
      ll b_j = L[j] / block_size;
      if (b_i != b_j) return b_i < b_j;
      return (b_i & 1) ? R[i] > R[j] : R[i] < R[j];
    });
  }

  template <typename Add, typename Del, typename Rem>
  void run(Add add, Del del, Rem rem) {
    ll l = 0, r = 0;
    for (ll i : ord) {
      while (l > L[i]) add(--l);
      while (l < L[i]) del(l++);
      while (r > R[i]) del(--r);
      while (r < R[i]) add(r++);
      rem(i);
    }
  }
};
/*
    -- Constructor --
    Mo mo(ll n)
    n : Size of the array being processed

    -- Add Query --
    void mo.add_query(ll l, ll r)
    Adds a query for the interval [l, r)

    -- Build --
    void mo.build()
    Sorts and determines the processing order of queries
    Time complexity: O(Q log Q) (where Q is the number of queries)

    -- Run --
    void mo.run(Add add, Del del, Rem rem)
    Executes the algorithm by passing lambda expressions or functions
    add(ll id...)   : Process to add element 'id' to the current state
    del(ll id...)   : Process to remove element 'id' from the current state
    rem(ll q_id...) : Process to record the answer for the query added at index 'q_id'
    Time complexity: O(N √Q)
*/

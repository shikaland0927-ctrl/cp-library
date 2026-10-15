#pragma once
// snippet: doubling
template <class S, S (*op)(S, S), S (*e)()> struct Doubling {
  ll n, log_size, max_k;
  vector<vector<ll>> doubling;
  vector<vector<S>> val;

  Doubling(const vector<ll>& to, const vector<S>& cost, ll max_k)
      : n(to.size()), max_k(max_k) {
    assert(n > 0);
    assert(ssize(cost) == n);
    assert(max_k >= 0);
    rep (j, n) assert(0 <= to[j] && to[j] < n);
    log_size = 1;
    for (ll x = max_k; x > 1; x >>= 1) log_size++;
    doubling.assign(log_size, vector<ll>(n));
    val.assign(log_size, vector<S>(n, e()));
    doubling[0] = to;
    val[0] = cost;
    rep (i, log_size - 1) rep (j, n) {
      ll m = doubling[i][j];
      doubling[i + 1][j] = doubling[i][m];
      val[i + 1][j] = op(val[i][j], val[i][m]);
    }
  }

  pair<ll, S> jump(ll j, ll k) const {
    assert(0 <= j && j < n);
    assert(0 <= k && k <= max_k);
    S res = e();
    rep (i, log_size) if ((k >> i) & 1) {
      res = op(res, val[i][j]);
      j = doubling[i][j];
    }
    return {j, res};
  }
};
/*
    -- Template Parameters --
    S                  : Type of the value accumulated along transitions
    S op(S a, S b)     : Combines a value from an earlier block with the following block
    S e()              : Returns the identity element of op
    op must be associative; commutativity is not required.

    -- Constructor --
    Doubling<S, op, e> db(const vector<ll>& to,
                          const vector<S>& cost,
                          ll max_k)
    to[j]   : State reached after one transition from state j
    cost[j] : Value obtained by the one transition j -> to[j]
    max_k   : Maximum number of transitions passed to jump
    Requirements: to.size() == cost.size() > 0, 0 <= to[j] < n, max_k >= 0
    Time complexity: O(N log(max_k + 1))
    Space complexity: O(N log(max_k + 1))

    -- Jump --
    pair<ll, S> db.jump(ll j, ll k)
    j : Starting state
    k : Number of transitions (0 <= k <= max_k)
    Returns the state after k transitions and the value accumulated during those transitions.
    For k = 0, returns the starting state and e().
    Time complexity: O(log(max_k + 1))

    -- Internal Tables --
    doubling[i][j] : State reached after 2^i transitions from state j
    val[i][j]      : Value accumulated during 2^i transitions from state j
*/

using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

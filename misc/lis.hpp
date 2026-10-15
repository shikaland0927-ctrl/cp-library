#pragma once
// snippet: lis
template <typename T = ll> struct LIS {
  ll n;
  vector<T> v;
  mutable vector<T> dp;
  mutable vector<ll> id, pre;
  bool strictly;
  mutable bool built = false;

  LIS(ll n, bool strictly = true) : n(n), v(n), strictly(strictly) {}
  LIS(const vector<T>& v, bool strictly = true) : n(v.size()), v(v), strictly(strictly) {}

  T& operator[](ll i) {
    built = false;
    return v[i];
  }
  
  const T& operator[](ll i) const { return v[i]; }

  void build() const {
    if (built) return;
    dp.clear(); id.clear();
    pre.assign(n, -1);
    rep (i, n) {
      auto it = (strictly ? lb(all(dp), v[i]) : ub(all(dp), v[i]));
      ll pos = it - dp.begin();
      if (it == dp.end()) {
        dp.eb(v[i]);
        id.eb(i);
      } else {
        dp[pos] = v[i];
        id[pos] = i;
      }
      if (pos > 0) pre[i] = id[pos - 1];
    }
    built = true;
  }

  ll size() const {
    build();
    return dp.size();
  }

  vector<T> get_val() const {
    build();
    if (dp.empty()) return {};
    vector<T> res;
    ll now = id.back();
    while (now != -1) {
      res.eb(v[now]);
      now = pre[now];
    }
    reverse(all(res));
    return res;
  }

  vector<ll> get_id() const {
    build();
    if (dp.empty()) return {};
    vector<ll> res;
    ll now = id.back();
    while (now != -1) {
      res.eb(now);
      now = pre[now];
    }
    reverse(all(res));
    return res;
  }
};
/*
    -- Constructor --
    LIS<T = ll> lis(ll n, bool strictly = true)
    LIS<T = ll> lis(const vector<T>& v, bool strictly = true)
    
    v: Target array
    n: Size of the target array (elements can be modified via lis[i] = x)
    strictly: true -> Strictly increasing, false -> Non-decreasing

    -- Getter Methods --
    ll lis.size()
    Size of the LIS

    vector<T> lis.get_val()
    Time complexity: O(lis.size())
    Returns an array of the values that make up the LIS

    vector<ll> lis.get_id()
    Time complexity: O(lis.size())
    Returns an array of the indices in the original array v of the elements that make up the LIS
*/

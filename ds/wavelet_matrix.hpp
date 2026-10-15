#pragma once
// snippet: wavelet_matrix
struct WaveletMatrix {
  struct BitRank {
    vector<int> pref;
    BitRank() {}
    BitRank(const vector<ll>& v) {
      pref.resize(v.size() + 1);
      rep (i, v.size()) pref[i + 1] = pref[i] + v[i];
    }
    ll rank0(ll pos) { return pos - pref[pos]; }
    ll rank1(ll pos) { return pref[pos]; }
  };

  ll n, height;
  vector<BitRank> dat;

  WaveletMatrix(vector<ll> v) : n(v.size()) {
    ll mx = (v.size() ? *max_element(all(v)) : 0);
    height = (mx == 0 ? 1 : 64 - __builtin_clzll(mx));
    dat.resize(height);
    rrep (h, height) {
      vector<ll> dir(n), left, right;
      rep (i, n) {
        dir[i] = v[i] >> h & 1;
        (dir[i] == 0 ? left : right).eb(v[i]);
      }
      dat[h] = BitRank(dir);
      v = left;
      v.insert(v.end(), all(right));
    }
  }

  // subtree of (h + 1, l, r)
  tuple<ll, ll, ll, ll> get_subtree_range(ll h, ll l, ll r) {
    ll l0 = dat[h].rank0(l), r0 = dat[h].rank0(r); 
    ll mid = dat[h].rank0(n);
    ll l1 = dat[h].rank1(l) + mid, r1 = dat[h].rank1(r) + mid;
    return {l0, r0, l1, r1};
  }

  ll kth_smallest_rec(ll h, ll l, ll r, ll k) {
    if (h == -1) return 0;
    auto [l0, r0, l1, r1] = get_subtree_range(h, l, r);
    ll left_size = r0 - l0;
    if (k < left_size) return kth_smallest_rec(h - 1, l0, r0, k);
    return (1LL << h) | kth_smallest_rec(h - 1, l1, r1, k - left_size);
  }

  ll cnt_lower_rec(ll h, ll l, ll r, ll x) {
    if (l == r || h == -1) return 0;
    auto [l0, r0, l1, r1] = get_subtree_range(h, l, r);
    if ((x >> h) & 1) return r0 - l0 + cnt_lower_rec(h - 1, l1, r1, x);
    return cnt_lower_rec(h - 1, l0, r0, x);
  }

  ll kth_smallest(ll l, ll r, ll k) { return kth_smallest_rec(height - 1, l, r, k); }
  ll kth_largest(ll l, ll r, ll k) { return kth_smallest_rec(height - 1, l, r, r - l - 1 - k); }
  ll cnt_lower(ll l, ll r, ll x) {
    if (x <= 0) return 0;
    if (height < 64 && (ull)x >= (1ULL << height)) return r - l;
    return cnt_lower_rec(height - 1, l, r, x);
  }
  ll range_freq(ll l, ll r, ll lower, ll upper) {
    if (!(l < r || lower < upper)) return 0;
    return cnt_lower(l, r, upper) - cnt_lower(l, r, lower);
  }
};
/*
    -- Constructor --
    WaveletMatrix wm(vector<ll> v)
    Time Complexity: O(N log(MAX_V))

    -- K-th Elements --
    ll wm.kth_smallest(ll l, ll r, ll k)
    Time Complexity: O(log(MAX_V))
    Returns the 0-indexed k-th smallest element in the range [l, r).

    ll wm.kth_largest(ll l, ll r, ll k)
    Time Complexity: O(log(MAX_V))
    Returns the 0-indexed k-th largest element in the range [l, r).

    -- Frequencies --
    ll wm.cnt_lower(ll l, ll r, ll x)
    Time Complexity: O(log(MAX_V))
    Returns the number of elements strictly less than `x` in the range [l, r).

    ll wm.range_freq(ll l, ll r, ll lower, ll upper)
    Time Complexity: O(log(MAX_V))
    Returns the number of elements `e` such that lower <= e < upper in the range [l, r).
*/

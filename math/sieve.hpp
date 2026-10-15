#pragma once
// snippet: sieve
struct Sieve {
  ll n;
  vector<ll> spf;
  vector<ll> primes;
  Sieve(ll n = 1) : n(n), spf(n + 1, 0) {
    spf[0] = spf[1] = -1;
    rep (i, 2, n + 1) {
      if (spf[i]) continue;
      spf[i] = i;
      primes.eb(i);
      rep (j, i * i, n + 1, i) if(!spf[j]) spf[j] = i;
    }
  }

  bool is_prime(ll x) const {
    if (x <= 1 || x > n) return false;
    return spf[x] == x;
  }

  vector<pair<ll, ll>> prime_factors(ll x) const {
    vector<pair<ll, ll>> res;
    if (x <= 1) return res;
    else if (x <= n) {
      while (x != 1) {
        ll p = spf[x];
        ll exp = 0;
        while (spf[x] == p) {
          x /= p;
          exp++;
        }
        res.eb(p, exp);
      }
      return res;
    } else {
      for (ll p : primes) {
        if (p * p > x) break;
        ll exp = 0;
        while (x % p == 0) {
          x /= p;
          exp++;
        }
        if (exp != 0) res.eb(p, exp);
      }
      if (x != 1) res.eb(x, 1);
      return res;
    }
  }

  ll count_divisors(ll x) const {
    if (x <= 0) return 0;
    if (x == 1) return 1;
    ll res = 1;
    for (auto& p : prime_factors(x)) res *= p.se + 1;
    return res;
  }

  ll sum_divisors(ll x) const {
    if (x <= 0) return 0;
    if (x == 1) return 1;
    ll res = 1;
    for (auto& p : prime_factors(x)) {
      ll sum = 0;
      ll cur = 1;
      rep (i, p.se + 1) {
        sum += cur;
        cur *= p.fi;
      }
      res *= sum;
    }
    return res;
  }

  vector<ll> divisors(ll x) const {
    if (x <= 0) return {};
    if (x == 1) return {1};
    auto pf = prime_factors(x);
    vector<ll> res;
    auto dfs = [&](auto dfs, ll idx, ll val) -> void {
      if (idx == (ll)pf.size()) {
        res.eb(val);
        return;
      }
      auto [p, exp] = pf[idx];
      ll mul = 1;
      rep (i, exp + 1) {
        dfs(dfs, idx + 1, val * mul);
        mul *= p;
      }
    };
    dfs(dfs, 0, 1);
    sort(all(res));
    return res;
  }

  ll totient(ll x) const {
    if (x <= 0) return 0;
    if (x == 1) return 1;
    ll res = x;
    for (auto& p : prime_factors(x)) res = res / p.fi * (p.fi - 1);
    return res;
  }
};
/*
    -- Constructor --
    Sieve sieve(ll n)
    Time Complexity: O(n log log n)
    Constructs the SPF (Smallest Prime Factor) array and the list of primes up to n.

    -- Primality Test --
    bool sieve.is_prime(ll x)
    Time Complexity: O(1)
    Determines whether x is a prime number (assert(x <= n)).

    -- Prime Factorization --
    vector<pair<ll, ll>> sieve.prime_factors(ll x)
    Time Complexity: O(log x) when x <= n / O(√x / log √x) when x > n
    Returns an array of pairs (p, exp) representing the prime factor p and its exponent exp of x.

    -- Divisor-related Operations --
    ll sieve.count_divisors(ll x)
    Time Complexity: Same as prime_factors
    Returns the number of divisors of x.

    ll sieve.sum_divisors(ll x)
    Time Complexity: Same as prime_factors
    Returns the sum of divisors of x.

    vector<ll> sieve.divisors(ll x)
    Time Complexity: Time complexity of prime_factors + O(d(x) log d(x)) (where d(x) is the number of divisors)
    Returns an array containing all divisors of x, sorted in ascending order.

    -- Euler's Totient Function --
    ll sieve.totient(ll x)
    Time Complexity: Same as prime_factors
    Returns the number of integers between 1 and x (inclusive) that are coprime to x.
*/

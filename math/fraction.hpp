#pragma once
// snippet: frac
struct Frac {
  ll num, den;

  Frac(__int128_t n = 0, __int128_t d = 1) {
    if (d == 0) {
      num = 1;
      den = 0;
    } else {
      if (d < 0) n = -n, d = -d;
      __int128_t g = gcd128(n < 0 ? -n : n, d);
      num = (ll)(n / g);
      den = (ll)(d / g);
    }
  }

  static __int128_t gcd128(__int128_t a, __int128_t b) {
    while (b) { a %= b; swap(a, b); }
    return a;
  }

  Frac operator+(const Frac& f) const {
    return Frac((__int128_t)num * f.den + (__int128_t)f.num * den, (__int128_t)den * f.den);
  }
  Frac operator-(const Frac& f) const {
    return Frac((__int128_t)num * f.den - (__int128_t)f.num * den, (__int128_t)den * f.den);
  }
  Frac operator*(const Frac& f) const {
    return Frac((__int128_t)num * f.num, (__int128_t)den * f.den);
  }
  Frac operator/(const Frac& f) const {
    return Frac((__int128_t)num * f.den, (__int128_t)den * f.num);
  }

  Frac& operator+=(const Frac& f) { return *this = *this + f; }
  Frac& operator-=(const Frac& f) { return *this = *this - f; }
  Frac& operator*=(const Frac& f) { return *this = *this * f; }
  Frac& operator/=(const Frac& f) { return *this = *this / f; }

  auto operator<=>(const Frac& f) const {
    return (__int128_t)num * f.den <=> (__int128_t)f.num * den;
  }
  bool operator==(const Frac& f) const = default;

  // friend ostream& operator<<(ostream& os, const Frac& f) {
  //   if (f.den == 0) {
  //     if (f.num > 0) return os << "INF";
  //     if (f.num < 0) return os << "-INF";
  //     return os << "NaN";
  //   }
  //   return os << f.num << "/" << f.den;
  // }
};
/*
    -- Constructor --
    Frac frac(ll n, ll d)
    Time Complexity: O(log(min(n, d))) (Reduction via GCD)
    Generates n / d.
    Without arguments: 0/1. With 1 argument: n/1.
    If d = 0, num = 1 (equivalent to INF).

    -- Arithmetic Operations --
    +, -, *, /, +=, -=, *=, /=
    Time Complexity: O(log(min(num, den))) 

    -- Comparison Operations --
    <=>, == 
    Time Complexity: O(1)
*/

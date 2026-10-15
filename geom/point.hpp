#pragma once
// snippet: point
template <typename T = ld> struct Point {
  T x, y;
  ll id;

  Point(T x = 0, T y = 0, ll id = -1) : x(x), y(y), id(id) {}

  Point  operator+() const { return *this; }
  Point  operator-() const { return Point(-x, -y); }
  Point  operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point  operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  Point  operator*(T s) const { return Point(x * s, y * s); }
  Point  operator/(T s) const { return Point(x / s, y / s); }
  T      operator*(const Point& p) const { return x * p.x + y * p.y; }
  T      operator^(const Point& p) const { return x * p.y - y * p.x; }
  Point& operator+=(const Point& p) { x += p.x; y += p.y; return *this; }
  Point& operator-=(const Point& p) { x -= p.x; y -= p.y; return *this; }
  Point& operator*=(T s) { x *= s; y *= s; return *this; }
  Point& operator/=(T s) { x /= s; y /= s; return *this; }

  T norm2() const { return x * x + y * y; }
  ld norm() const { return sqrtl(norm2()); }
  T dist2(const Point& p) const { return (*this - p).norm2(); }
  ld dist(const Point& p) const { return (*this - p).norm(); }

  Point rot90() const { return Point(-y, x, id); }
  Point<ld> rot(ld ang) const {
    return Point<ld>(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang), id);
  }

  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point& p) const { return !(*this == p); }
  bool operator< (const Point& p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator<=(const Point& p) const { return *this < p || *this == p; }
  bool operator> (const Point& p) const { return p < *this; }
  bool operator>=(const Point& p) const { return p <= *this; }

  friend istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
  }
  friend ostream& operator<<(ostream& os, const Point& p) {
    os << p.x << ' ' << p.y;
    return os;
  }
};
/*
    -- Constructor --
    Point<T = ld> p(T x = 0, T y = 0, ll id = -1)

    -- Arithmetic / Comparison Operations --
    Supports +, -, +=, -= (Addition/subtraction between Points)
    Supports *, ^, *=, ^= (Dot product / Cross product between Points)
    Supports *, /, *=, /= (Scalar multiplication / division)
    Supports ==, !=
    Supports <, <=, >, >= (Lexicographical comparison: x-coordinate first, then y-coordinate)
    * Note: ^ has low precedence, so wrap in parentheses like (a ^ b)

    -- Vector Operations / Distance --
    T p.norm2()
    Calculates the squared distance from the origin

    ld p.norm()
    Calculates the distance from the origin

    T p.dist2(const Point<T>& q)
    Calculates the squared distance to point q

    ld p.dist(const Point<T>& q)
    Calculates the distance to point q

    -- Rotation --
    Point<T> p.rot90()
    Returns the point rotated 90 degrees counter-clockwise around the origin

    Point<ld> p.rot(ld ang)
    Returns the point rotated counter-clockwise by ang (radians) around the origin
    * Note: Even if T is an integer type, it returns floating-point coordinates, hence Point<ld>

    -- Input / Output --
    cin >> p
    Reads x and y (id is not modified)

    cout << p
    Outputs in the format "x y"
*/

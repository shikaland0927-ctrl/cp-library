#pragma once
// snippet: semiring_matrix
template <class T,
          auto op_add,
          auto op_mul,
          auto e_add, 
          auto e_mul>
struct SemiringMatrix {
  ll h, w;
  vector<T> A;

  SemiringMatrix() : h(0), w(0) {}
  SemiringMatrix(ll n) : h(n), w(n), A(n * n, e_add()) {}
  SemiringMatrix(ll n, ll m) : h(n), w(m), A(n * m, e_add()) {}
  SemiringMatrix(initializer_list<vector<T>> init) {
    h = init.size();
    w = (h > 0) ? init.begin()->size() : 0;
    A.reserve(h * w);
    for (const auto& row : init) A.insert(A.end(), row.begin(), row.end());
  }

  inline T* operator[](ll k) { return A.data() + k * w; }
  inline const T* operator[](ll k) const { return A.data() + k * w; }

  static SemiringMatrix I(ll n) {
    SemiringMatrix mat(n);
    rep (i, n) mat[i][i] = e_mul();
    return mat;
  }

  SemiringMatrix &operator+=(const SemiringMatrix &B) {
    assert(h == B.h && w == B.w);
    ll sz = A.size();
    rep (i, sz) A[i] = op_add(A[i], B.A[i]);
    return *this;
  }

  SemiringMatrix &operator*=(const SemiringMatrix &B) {
    ll n = h, m = B.w, p = w;
    assert(p == B.h);
    vector<T> C(n * m, e_add());
    rep (i, n) rep (k, p) {
      const T val = (*this)[i][k];
      if (val == e_add()) continue;
      rep (j, m) C[i * m + j] = op_add(C[i * m + j], op_mul(val, B[k][j]));
    }
    w = m;
    A.swap(C);
    return *this;
  }

  SemiringMatrix operator+(const SemiringMatrix &B) const { return (SemiringMatrix(*this) += B); }
  SemiringMatrix operator*(const SemiringMatrix &B) const { return (SemiringMatrix(*this) *= B); }

  SemiringMatrix pow(ll k) const {
    assert(h == w);
    SemiringMatrix res = SemiringMatrix::I(h);
    SemiringMatrix tmp = *this;
    while (k > 0) {
      if (k & 1) res *= tmp;
      tmp *= tmp;
      k >>= 1;
    }
    return res;
  }
};
/*
    -- Template Arguments --
    T                  : Type of matrix elements
    T op_add(T a, T b) : Addition operation for matrix elements
    T op_mul(T a, T b) : Multiplication operation for matrix elements
    T e_add()          : Identity element for addition
    T e_mul()          : Identity element for multiplication

    -- Constructor --
    using Matrix = SemiringMatrix<T, op_add, op_mul, e_add, e_mul>;

    (1) Matrix mat
    Generates an empty matrix

    (2) Matrix mat(ll n)
    Generates an n x n zero matrix

    (3) Matrix mat(ll n, ll m)
    Generates an n x m zero matrix

    (4) Matrix mat = {{T a, T b}, {T c, T d}}
    Generates a matrix from an initializer list

    -- Identity Matrix --
    Matrix Matrix::I(ll n)

    -- Element Access --
    T mat[ll i][ll j]

    -- Operations --
    Supports +, +=, *, *=

    -- Matrix Exponentiation --
    Matrix mat.pow(ll k)
    Time complexity: O(n^3 log k)
    Calculates the k-th power of the matrix (assert(square matrix))
*/

using T = ll;
T op_add(T a, T b) { return min(a, b); }
T op_mul(T a, T b) { return a + b; }
T e_add() { return inf; }
T e_mul() { return 0; }
using Matrix = SemiringMatrix<T, op_add, op_mul, e_add, e_mul>;

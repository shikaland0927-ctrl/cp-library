#pragma once
// snippet: matrix
template <class T> struct Matrix {
  ll h, w;
  vector<T> A;

  Matrix() : h(0), w(0) {}
  Matrix(ll n) : h(n), w(n), A(n * n, 0) {}
  Matrix(ll n, ll m) : h(n), w(m), A(n * m, 0) {}
  Matrix(initializer_list<vector<T>> init) {
    h = init.size();
    w = (h > 0) ? init.begin()->size() : 0;
    A.reserve(h * w);
    for (const auto& row : init) {
      A.insert(A.end(), row.begin(), row.end());
    }
  }

  inline T* operator[](ll k) { return A.data() + k * w; }
  inline const T* operator[](ll k) const { return A.data() + k * w; }

  static Matrix I(ll n) {
    Matrix mat(n);
    for (ll i = 0; i < n; i++) mat[i][i] = 1;
    return mat;
  }

  Matrix &operator+=(const Matrix &B) {
    assert(h == B.h && w == B.w);
    ll sz = A.size();
    for (ll i = 0; i < sz; i++) A[i] += B.A[i];
    return *this;
  }

  Matrix &operator-=(const Matrix &B) {
    assert(h == B.h && w == B.w);
    ll sz = A.size();
    for (ll i = 0; i < sz; i++) A[i] -= B.A[i];
    return *this;
  }

  Matrix &operator*=(const Matrix &B) {
    ll n = h, m = B.w, p = w;
    assert(p == B.h);
    vector<T> C(n * m, 0);
    for (ll i = 0; i < n; i++) {
      for (ll k = 0; k < p; k++) {
        const T val = (*this)[i][k];
        for (ll j = 0; j < m; j++) {
          C[i * m + j] += val * B[k][j];
        }
      }
    }
    w = m;
    A.swap(C);
    return *this;
  }

  Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
  Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
  Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

  Matrix pow(ll k) const {
    assert(h == w);
    Matrix res = Matrix::I(h);
    Matrix tmp = *this;
    while (k > 0) {
      if (k & 1) res *= tmp;
      tmp *= tmp;
      k >>= 1;
    }
    return res;
  }
};
/*
    -- Constructor --
    (1) Matrix<T> mat
    Generates an empty matrix

    (2) Matrix<T> mat(ll n)
    Generates an n x n zero matrix

    (3) Matrix<T> mat(ll n, ll m)
    Generates an n x m zero matrix

    (4) Matrix<T> mat = {{T a, T b}, {T c, T d}}
    Generates a matrix from an initializer list

    -- Identity Matrix --
    Matrix<T> Matrix<T>::I(ll n)

    -- Element Access --
    T mat[ll i][ll j]

    -- Arithmetic Operations --
    Supports +, -, +=, -=, *, *=

    -- Matrix Exponentiation --
    Matrix<T> mat.pow(ll k)
    Time complexity: O(n^3 log k)
    Calculates the k-th power of the matrix (assert(square matrix))
*/

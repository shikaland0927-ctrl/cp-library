#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#define SHOW(...) show_debug(#__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)
#else
#define SHOW(...) ((void)0)
#endif
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
const ll inf = 4e18;
const ld pi = acos(-1.0L);

#define em emplace
#define ef emplace_front
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define lb lower_bound
#define ub upper_bound
#define np next_permutation
#define acc accumulate
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define fi first
#define se second
#define popcount __builtin_popcountll
#define ctz __builtin_ctzll
#define rep0(n) for (ll _ = 0; _ < (ll)(n); _++)
#define rep1(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep2(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define rep3(i, a, b, c) for (ll i = a; i < (ll)(b); i += c)
#define rrep0(n) for (ll _ = (ll)(n) - 1; _ >= 0; _--)
#define rrep1(i, n) for (ll i = (ll)(n) - 1; i >= 0; i--)
#define rrep2(i, n, a) for (ll i = (ll)(n) - 1; i >= (ll)(a); i--)
#define rrep3(i, n, a, b) for (ll i = (ll)(n) - 1; i >= (ll)(a); i -= b)
#define overload5(a, b, c, d, e, ...) e
#define rep(...) overload5(__VA_ARGS__, rep3, rep2, rep1, rep0)(__VA_ARGS__)
#define rrep(...) overload5(__VA_ARGS__, rrep3, rrep2, rrep1, rrep0)(__VA_ARGS__)
#define INPUT_DETAIL_CAT_I(a, b) a##b
#define INPUT_DETAIL_CAT(a, b) INPUT_DETAIL_CAT_I(a, b)
#define INPUT_DETAIL_PROBE(x) x, 1
#define INPUT_DETAIL_CHECK_N(x, n, ...) n
#define INPUT_DETAIL_CHECK(...) INPUT_DETAIL_CHECK_N(__VA_ARGS__, 0)
#define INPUT_DETAIL_IS_PAREN_PROBE(...) INPUT_DETAIL_PROBE(~)
#define INPUT_DETAIL_IS_PAREN(x) INPUT_DETAIL_CHECK(INPUT_DETAIL_IS_PAREN_PROBE x)
#define INPUT_DETAIL_UNPAREN(...) __VA_ARGS__
#define INPUT_DETAIL_DIMS_0(x) tuple{x}
#define INPUT_DETAIL_DIMS_1(x) tuple{INPUT_DETAIL_UNPAREN x}
#define INPUT_DETAIL_DIMS(x) INPUT_DETAIL_CAT(INPUT_DETAIL_DIMS_, INPUT_DETAIL_IS_PAREN(x))(x)
#define INPUT_DETAIL_INPUT_0(type, first, ...) type first __VA_OPT__(,) __VA_ARGS__; input(first __VA_OPT__(,) __VA_ARGS__)
#define INPUT_DETAIL_INPUT_1(type, dims, ...) nested_vector_t<type, tuple_size_v<decltype(INPUT_DETAIL_DIMS(dims))>> __VA_ARGS__; input_vec(INPUT_DETAIL_DIMS(dims), __VA_ARGS__)
#define INPUT(type, first, ...) INPUT_DETAIL_CAT(INPUT_DETAIL_INPUT_, INPUT_DETAIL_IS_PAREN(first))(type, first __VA_OPT__(,) __VA_ARGS__)
#define INPUT_COL(type, n, ...) vector<type> __VA_ARGS__; input_col(n, __VA_ARGS__)
#define DROP(...) do { PRINT(__VA_ARGS__); exit(0); } while (false)

template<class T> concept tuple_like = requires { tuple_size<remove_cvref_t<T>>::value; };
template<tuple_like T> istream& operator>>(istream& is, T& value) { apply([&](auto&... x) { (is >> ... >> x); }, value); return is; }
template<class T> istream& operator>>(istream& is, vector<T>& v) { rep(i, v.size())is >> v[i]; return is; }
template<class T, size_t N> struct nested_vector { using type = vector<typename nested_vector<T, N - 1>::type>; };
template<class T> struct nested_vector<T, 0> { using type = T; };
template<class T, size_t N> using nested_vector_t = typename nested_vector<T, N>::type;
template<typename T, typename... Args> bool chmin(T& a, const Args&... args) { bool res = false; ((a > args && (a = args, res = true)), ...); return res; }
template<typename T, typename... Args> bool chmax(T& a, const Args&... args) { bool res = false; ((a < args && (a = args, res = true)), ...); return res; }
template<class... T> void input(T&... a) { (cin >> ... >> a); }
template<class... T> void input_vec(ll n, T&... a) { ((a.resize(n), cin >> a), ...); }
template<size_t I = 0, class T, tuple_like Dims> void resize_nd(T& v, const Dims& dims) {
    v.resize(get<I>(dims));
    if constexpr (I + 1 < tuple_size_v<remove_cvref_t<Dims>>) for (auto& x : v) resize_nd<I + 1>(x, dims);
}
template<tuple_like Dims, class... T> void input_vec(const Dims& dims, T&... a) { ((resize_nd(a, dims), cin >> a), ...); }
template<class... T> void input_col(ll n, T&... a) { (a.resize(n), ...); rep(i, n) (cin >> ... >> a[i]); }
template<class T> concept string_like = convertible_to<const T&, string_view>;
template<class T> concept output_range = ranges::input_range<const T&> && (!string_like<T>);
template<class> inline constexpr bool always_false = false;
template<class T> void output_value(ostream& os, const T& value, bool debug) {
    using U = remove_cvref_t<T>;
    if constexpr (string_like<T>) {
        if (debug) os << '"';
        os << value;
        if (debug) os << '"';
    } else if constexpr (same_as<U, char>) {
        if (debug) os << '\'';
        os << value;
        if (debug) os << '\'';
    } else if constexpr (output_range<T>) {
        if (debug) os << '[';
        bool first = true;
        for (const auto& x : value) {
            if (!exchange(first, false)) os << (debug ? ", " : " ");
            output_value(os, x, debug);
        }
        if (debug) os << ']';
    } else if constexpr (tuple_like<T>) {
        if (debug) os << '(';
        bool first = true;
        apply([&](const auto&... x) {
            ((os << (exchange(first, false) ? "" : (debug ? ", " : " ")), output_value(os, x, debug)), ...);
        }, value);
        if (debug) os << ')';
    } else if constexpr (floating_point<U>) {
        const auto flags = os.flags();
        const auto precision = os.precision();
        if (debug) os << setprecision(15) << value;
        else os << fixed << setprecision(15) << value;
        os.flags(flags);
        os.precision(precision);
    } else if constexpr (requires { os << value; }) {
        os << value;
    } else if constexpr (requires { value.val(); }) {
        output_value(os, value.val(), debug);
    } else {
        static_assert(always_false<T>, "output_value: unsupported type");
    }
}
inline void PRINT() { cout << '\n'; }
template<class... T> requires (sizeof...(T) > 0) void PRINT(const T&... value) {
    bool first = true;
    ((cout << (exchange(first, false) ? "" : " "), output_value(cout, value, false)), ...);
    cout << '\n';
}
template<class... T> void show_debug(string_view names, const T&... value) {
    cerr << '[' << names << "] = [";
    bool first = true;
    ((cerr << (exchange(first, false) ? "" : ", "), output_value(cerr, value, true)), ...);
    cerr << "]\n";
}

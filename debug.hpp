// Debug helpers for local runs. template.hpp includes this only when ONLINE_JUDGE is not defined,
// so the expanded submission keeps just the #include line, which the judge skips
#pragma once
#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#define SHOW(...) debug_detail::show(#__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)

namespace debug_detail {
using namespace std;
template <typename T> concept tuple_like = requires { tuple_size<remove_cvref_t<T>>::value; };
template <typename T> concept string_like = convertible_to<const T&, string_view>;
template <typename T> concept output_range = ranges::input_range<const T&> && (!string_like<T>);
template <typename> inline constexpr bool always_false = false;
template <typename T> void output(ostream& os, const T& value) {
  using U = remove_cvref_t<T>;
  if constexpr (string_like<T>) {
    os << '"' << value << '"';
  } else if constexpr (same_as<U, char>) {
    os << '\'' << value << '\'';
  } else if constexpr (output_range<T>) {
    os << '[';
    bool first = true;
    for (const auto& x : value) {
      if (!exchange(first, false)) os << ", ";
      output(os, x);
    }
    os << ']';
  } else if constexpr (tuple_like<T>) {
    os << '(';
    bool first = true;
    apply([&](const auto&... x) { ((os << (exchange(first, false) ? "" : ", "), output(os, x)), ...); }, value);
    os << ')';
  } else if constexpr (floating_point<U>) {
    const auto precision = os.precision();
    os << setprecision(15) << value;
    os.precision(precision);
  } else if constexpr (requires { os << value; }) {
    os << value;
  } else if constexpr (requires { value.val(); }) {
    output(os, value.val());
  } else {
    static_assert(always_false<T>, "SHOW: unsupported type");
  }
}
template <typename... T> void show(string_view names, const T&... value) {
  cerr << '[' << names << "] = [";
  [[maybe_unused]] bool first = true;
  ((cerr << (exchange(first, false) ? "" : ", "), output(cerr, value)), ...);
  cerr << "]\n";
}
}  // namespace debug_detail

#pragma once
// snippet: rle
vector<pair<char, ll>> rle(const string& s) {
  vector<pair<char, ll>> res;
  for (char c : s) {
    if (!res.size() || res.back().fi != c) res.eb(c, 0);
    res.back().se++;
  }
  return res;
}

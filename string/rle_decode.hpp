#pragma once
// snippet: rle_decode
string rle_decode(const vector<pair<char, ll>>& r) {
  string res = "";
  for (auto [c, len] : r) res.append(len, c);
  return res;
}

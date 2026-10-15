#pragma once
// snippet: trie
template <ll char_size = 26, char margin = 'a'> struct TrieNode {
  vector<ll> nxt;
  ll exist, pass;
  TrieNode() : nxt(char_size, -1), exist(0), pass(0) {}
};

template <ll char_size = 26, char margin = 'a'> struct Trie {
  vector<TrieNode<char_size, margin>> nodes;
  Trie(ll reserve_size = 0) {
    if (reserve_size > 0) nodes.reserve(reserve_size + 1);
    nodes.eb(TrieNode<char_size, margin>());
  }

  void add(const string& s) {
    ll now = 0;
    nodes[0].pass++;
    for (char c : s) {
      ll k = c - margin;
      if (nodes[now].nxt[k] == -1) {
        nodes[now].nxt[k] = nodes.size();
        nodes.eb(TrieNode<char_size, margin>());
      }
      now = nodes[now].nxt[k];
      nodes[now].pass++;
    }
    nodes[now].exist++;
  }

  bool erase(const string& s) {
    if (!search(s)) return false;
    ll now = 0;
    nodes[0].pass--;
    for (char c : s) {
      ll k = c - margin;
      now = nodes[now].nxt[k];
      nodes[now].pass--;
    }
    nodes[now].exist--;
    return true;
  }

  ll search(const string& s) const {
    ll now = 0;
    for (char c : s) {
      ll k = c - margin;
      if (nodes[now].nxt[k] == -1) return 0;
      now = nodes[now].nxt[k];
    }
    return nodes[now].exist;
  }

  ll count_prefix(const string& s) const {
    ll now = 0;
    for (char c : s) {
      ll k = c - margin;
      if (nodes[now].nxt[k] == -1) return 0;
      now = nodes[now].nxt[k];
    }
    return nodes[now].pass;
  }
};
/*
    -- Constructor --
    Trie<ll char_size = 26, char margin = 'a'> trie(ll reserve_size = 0)
    char_size    : Number of character types to handle
    margin       : Base character
    reserve_size : Expected number of nodes (optional)

    -- Add String --
    void trie.add(const string& s)
    Time Complexity: O(|s|)

    -- Erase String --
    bool trie.erase(const string& s)
    Removes one occurrence; returns false if s is not stored.
    Time Complexity: O(|s|)

    -- Search (Exact Match) --
    ll trie.search(const string& s)
    Time Complexity: O(|s|)

    -- Search (Prefix Match) --
    ll trie.count_prefix(const string& s)
    Time Complexity: O(|s|)
*/

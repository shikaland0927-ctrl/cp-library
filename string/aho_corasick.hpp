#pragma once
// snippet: aho
template <ll char_size = 26, char margin = 'a'> struct AhoNode {
  vector<ll> nxt;
  ll exist, fail;
  vector<ll> exist_ids;
  AhoNode() : nxt(char_size, -1), exist(0), fail(-1) {}
};

template <ll char_size = 26, char margin = 'a'> struct AhoCorasick {
  vector<AhoNode<char_size, margin>> nodes;
  ll pattern_count;
  vector<ll> bfs_order;

  AhoCorasick(ll reserve_size = 0) : pattern_count(0) {
    if (reserve_size > 0) nodes.reserve(reserve_size + 1);
    nodes.eb(AhoNode<char_size, margin>());
  }

  ll add(const string& s) {
    ll now = 0;
    for (char c : s) {
      ll k = c - margin;
      if (nodes[now].nxt[k] == -1) {
        nodes[now].nxt[k] = nodes.size();
        nodes.eb(AhoNode<char_size, margin>());
      }
      now = nodes[now].nxt[k];
    }
    nodes[now].exist++;
    nodes[now].exist_ids.eb(pattern_count);
    return pattern_count++;
  }

  void build() {
    queue<ll> q;
    for (ll i = 0; i < char_size; i++) {
      if (nodes[0].nxt[i] != -1) {
        nodes[nodes[0].nxt[i]].fail = 0;
        q.em(nodes[0].nxt[i]);
      } else {
        nodes[0].nxt[i] = 0;
      }
    }
    bfs_order.clear();
    bfs_order.eb(0);
    while (q.size()) {
      ll v = q.front(); q.pop();
      bfs_order.eb(v);
      for (ll i = 0; i < char_size; i++) {
        ll nv = nodes[v].nxt[i];
        if (nv != -1) {
          nodes[nv].fail = nodes[nodes[v].fail].nxt[i];
          nodes[nv].exist += nodes[nodes[nv].fail].exist;
          q.em(nv);
        } else {
          nodes[v].nxt[i] = nodes[nodes[v].fail].nxt[i];
        }
      }
    }
  }

  ll operator()(ll v, char c) const { return nodes[v].nxt[c - margin]; }
  const AhoNode<char_size, margin>& operator[](ll v) const { return nodes[v]; }
  ll size() const { return nodes.size(); }
};
/*
    -- Constructor --
    AhoCorasick<ll char_size = 26, char margin = 'a'> aho(ll reserve_size = 0)
    char_size    : Number of character types to handle
    margin       : Base character (margin)
    reserve_size : Expected number of nodes (optional)

    -- Add pattern string --
    ll aho.add(const string& s)
    Time complexity: O(|s|)
    Returns the index of the added string (unique ID)

    -- Build --
    void aho.build()
    Time complexity: O(total number of nodes × char_size)

    -- State transition --
    ll aho(ll v, char c)
    Returns the next state number after reading character c from the current state number v

    -- Get node information --
    ll aho[v].exist             : Total number of occurrences of patterns ending at state v
    vector<ll> aho[v].exist_ids : List of unique IDs of patterns that terminate exactly at state v
    vector<ll> aho.bfs_order    : List of node numbers in BFS traversal order from parent to child on the failure tree

    -- Get total number of nodes --
    ll aho.size()
*/

#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;

using namespace std;

/*
  Add all strings before calling go()

  count(v) will count the number 
  of strings (in the original set) that 
  are a suffix of the string represented
  by state v (call this string(v))

  get_link(v) points to the state that
  contains the longest proper suffix
  of string(v)
  
  this is all done lazily, and memoized
  to preserved amortized-linear time
*/
template<int A>
struct AhoCorasick {
  struct Vertex {
    int next[A], go[A];
    int parent = -1, link = -1, leaves = 0, count = -1;
    char incoming;
    Vertex(int par = -1, char ch = '$') {
      parent = par;
      incoming = ch;
      fill(next, next + A, -1);
      fill(go, go + A, -1);
    }
  };

  vector<Vertex> trie;

  AhoCorasick(): trie(1) {}

  void add_string(const string &s) {
    int v = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (trie[v].next[c] == -1) {
        trie[v].next[c] = trie.size();
        trie.emplace_back(v, ch);
      }
      v = trie[v].next[c];
    }
    trie[v].leaves++;
  }

  int get_link(int v) {
    if (trie[v].link == -1) {
      if (v == 0 || trie[v].parent == 0) {
        trie[v].link = 0;
      } else {
        trie[v].link = go(get_link(trie[v].parent), trie[v].incoming);
      }
    }
    return trie[v].link;
  }

  int go(int v, char ch) {
    int c = ch - 'a';
    if (trie[v].go[c] == -1) {
      if (trie[v].next[c] != -1) {
        trie[v].go[c] = trie[v].next[c];
      } else {
        trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
      }
    }
    return trie[v].go[c];
  }

  int count(int v) {
    if (trie[v].count == -1) {
      if (v == 0) trie[v].count = 0;
      else {
        trie[v].count = trie[v].leaves + count(get_link(v));
      }
    }
    return trie[v].count;
  }
};

AhoCorasick<26> forw, backw;

int main() {

	return 0;
}
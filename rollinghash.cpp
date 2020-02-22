#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
typedef long long ll;
typedef long double ld;
using namespace std;

struct rolling_hash {
  int len = 0;

  int p = 101;
  int ppow = 1; // p ^ len
  int mod= 1e9 + 7;
  int hash = 0;

  void inc() {
    len++;
    ppow = (ppow * 1ll * p) % mod;
  }

  void insert_front(char ch) {
    hash = (hash * 1ll * p + ch) % mod;
    inc();
  }

  void insert_back(char ch) {
    hash = (hash + ch * 1ll * ppow) % mod;
    inc();
  }

  bool operator==(rolling_hash &h) {
    return hash == h.hash;
  }
};
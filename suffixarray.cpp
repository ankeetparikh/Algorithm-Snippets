#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define rep(s, l, r) for (int s = l; s < r; s++)
#define per(s, r, l) for (int s = r - 1; s >= l; s--)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

// make sure that you append '$' to your string before calling this
vi suffix_array(string s) {
  int n = s.length();
  vi p(n), c(n);
  vector<pair<pii, int>> tmp(n);

  rep(i, 0, n) c[i] = s[i];
  int k = -1;
  do {
    k++;
    rep(i, 0, n) {
      tmp[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    }
    sort(all(tmp));
    rep(i, 0, n) p[i] = tmp[i].s;
    c[p[0]] = 0;
    rep(i, 1, n) {
      c[p[i]] = c[p[i - 1]] + (tmp[i - 1].f < tmp[i].f);
    }
  } while ((1 << k) < n);
  return p;
}

// p must be the suffix array of s
// in other words: build_lcp(s, suffix_array(s))
vi build_lcp(string s, vi p) {
  int n = s.length();
  vi c(n), lcp(n);
  rep(i, 0, n) c[p[i]] = i;
  int k = 0;
  rep(i, 0, n - 1) {
    int pos = c[i];
    int j = p[pos - 1];
    while (s[i + k] == s[j + k]) k++;
    lcp[pos] = k;
    k = max(k - 1, 0);
  }
  return lcp;
}

/* 
  Make sure eq_class[i] is less than a million.
  It is not necessary that eq_class[i] < n.
  But in most cases it will be.
*/
template<int N>
struct suffixarray {
  char s[N];
  int n;
  int suf[N]; // ith suffix in sorted order
  int eq_class[N];
  int LCP[N]; // for computation of LCP
  struct container {
    int pref, suff, i;
    bool operator<(const container& b) const {
      if (pref != b.pref) return pref < b.pref;
      if (suff != b.suff) return suff < b.suff;
      return false;
    }
    bool operator!=(const container& b) const {
      return pref != b.pref || suff != b.suff;
    }
  } eq_pair[N];

  /*
    0 abaab       2 aab
    1 baab        3 ab
    2 aab     ->  0 abaab
    3 ab          4 b
    4 b           1 baab

    suf = [2, 3, 0, 4, 1]
  */

  void build() {
    for (int i = 0; i < n; i++) {
      eq_class[i] = s[i];
    }
    for (int j = 0; j == 0 || (1 << (j - 1)) < n; j++) {
      int hlen = (1 << j) / 2;
      for (int i = 0; i < n; i++) {
        eq_pair[i].pref = eq_class[i];
        eq_pair[i].suff = i + hlen < n ? eq_class[i + hlen] : -1;
        eq_pair[i].i = i;
      }
      sort(eq_pair, eq_pair + n);
      for (int i = 0, c = 0; i < n; i++) {
        if (i > 0 && eq_pair[i - 1] != eq_pair[i]) {
          ++c;
        }
        eq_class[eq_pair[i].i] = c;
      }
    }
    for (int i = 0; i < n; i++) {
      suf[eq_class[i]] = i;
    }
  }

  // make sure this gets called after build()
  // kasai's algorithm takes O(n)
  void buildLCP() {
    for (int i = 0, k = 0; i < n; i++, k = max(k - 1, 0)) {
      if (eq_class[i] == n - 1) {
        k = 0;// last suffix in sorted order
      }
      int j = suf[eq_class[i] + 1]; // next suffix in sorted order
      while (i + k < n && j + k < n && s[i + k] == s[j + k])
        k++;
      LCP[eq_class[i]] = k;
    }
  }

  int operator[](const int i) const {
    return suf[i];
  }

  suffixarray& operator=(const char* z) {
    n = strlen(z);
    for (int i = 0; i < n; i++) {
      s[i] = z[i];
    }
    build();
    return *this;
  }

  suffixarray& operator=(const string &z) {
    n = z.length();
    for (int i = 0; i < n; i++) {
      s[i] = z[i];
    }
    build();
    return *this;
  }
};

const int N = 1e6 + 10;
suffixarray<N> y;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  string s;
  cin >> s;
  y = s;
  for (int i = 0; i < s.length(); i++) {
    cout << y[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < s.length(); i++) {
    cout << y.eq_class[i] << " ";
  }
  cout << endl;
  y.buildLCP();
  for (int i = 0; i < s.length(); i++) {
    cout << y.LCP[i] << " ";
  }
  cout << endl;

  return 0;
}


/*
  i        eq_class
  0 banana 3
  1 anana  2
  2 nana   5
  3 ana    1
  4 na     4
  5 a      0
  
  suf       LCP
  5 a       1
  3 ana     3
  1 anana   0
  0 banana  0
  4 na      2
  2 nana    0
*/
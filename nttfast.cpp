#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T v, T lo, T hi) { return lo <= v && v <= hi; };

struct TimeStamp {
  string procedure;
  ld start = 0;

  TimeStamp(string s) {
    procedure = s;
    start = clock();
  }

  void finish() {
    ld end = clock();
    ld seconds = (end - start) / CLOCKS_PER_SEC;
    cout << procedure << " took " << seconds << " seconds\n";  
  }

};

/*
  make sure N is a power of 2
  Profiling:
    N = 1 << 18 = ~2e5 => 0.4 seconds
    N = 1 << 19 = ~5e5 => 0.9 seconds
    N = 1 << 20 = ~1e6 => 1.7 seconds
    N = 1 << 21 = ~2e6 => 3.9 seconds
    N = 1 << 22 = ~4e6 => 7.9 seconds
    N = 1 << 23 = ~8e6 => 16.5 seconds
*/
template<int N>
struct NTT {
  const int mod = 998244353;
  const int g = 3;

  constexpr static int L = __builtin_ctz(N);
  int a[N], b[N], rev[N];
  int prim_root[L + 1], prim_root_inv[L + 1]; // prim_root[i] = primitive root for transform of length 2^i
  int root = -1, invroot = -1, invN = -1;

  inline int add(int a, int b) {
    int x = a + b;
    if (x >= mod) x -= mod;
    return x;
  }

  inline int sub(int a, int b) {
    int x = a - b;
    if (x < 0) x += mod;
    return x;
  }

  inline int mul(int a, int b) {
    return a * 1ll * b % mod;
  }

  int power(int a, int b) {
    int res = 1;
    while (b) {
      if (b & 1) {
        res = mul(res, a);
      }
      a = mul(a, a);
      b >>= 1;
    }
    return res;
  }

  inline int inv(int x) {
    return power(x, mod - 2);
  }

  NTT() {
    // g^c is a (2^k)th root of unity
    // g^(2c) is a (2^{k-1}) root of unity
    // g^(4c) is a (2^{k-2}) root of unity
    // g^((p-1)/n) is an nth root of unity (since n is a power of 2)
    root = power(g, (mod - 1) / N);
    invroot = inv(root);
    invN = inv(N);
    prim_root[1] = root;
    prim_root_inv[1] = invroot;
    for (int i = 2; i <= L; i++) {
      prim_root[i] = mul(prim_root[i - 1], prim_root[i - 1]);
      prim_root_inv[i] = mul(prim_root_inv[i - 1], prim_root_inv[i - 1]);
    }
    reverse(prim_root + 1, prim_root + L + 1);
    reverse(prim_root_inv + 1, prim_root_inv + L + 1);

    // rev[i] stores the reverse of the first L bits of i
    rev[0] = 0;
    for (int i = 1; i < N; i++) {
      rev[i] = (rev[i / 2] / 2) | (i & 1) << (L - 1);
    }
  }

  void bit_reverse(int *a) {
    for(int i = 1; i < N; i++){
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
  }

  void ntt(int *a, bool invert) {
    bit_reverse(a);

    for (int n = 2; n <= N; n *= 2) {
      int wlen = invert ? prim_root_inv[__builtin_ctz(n)] : prim_root[__builtin_ctz(n)];
      const int half_len = n / 2;
      for (int i = 0; i < N; i += n) {
        for (int j = i, w = 1; j < i + half_len; j++) {
          ll u = a[j];
          ll v = mul(a[j + half_len], w);
          a[j] = add(u, v);
          a[j + half_len] = sub(u, v);
          w = mul(w, wlen);
        }
      }
    }
    if (invert) {
      for (int i = 0; i < N; i++) {
        a[i] = mul(a[i], invN);
      }
    }
  }

  // assume a and b are modded prior to calling this method
  void multiply(vi &_a, vi &_b) {
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    copy(_a.begin(), _a.end(), a);
    copy(_b.begin(), _b.end(), b);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < N; i++) {
      a[i] = a[i] * b[i] % mod;
    }
    ntt(a, true);
  }
};

const int N = 1 << 20;
NTT<N> ntt;

int main() {

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  {
    vi a = {1}, b = {4, 5, 6};
    ntt.multiply(a, b);
    for (int i = 0; i < 10; i++) {
      cout << ntt.a[i] << " ";
    }
    cout << endl;
  }

  vi a(N), b(N);

  for (int &x : a) 
  x = rng() % ntt.mod;

  for (int &x : b) 
    x = rng() % ntt.mod;

  TimeStamp t("Full ntt");
  ntt.multiply(a, b);
  t.finish();

  return 0;
}
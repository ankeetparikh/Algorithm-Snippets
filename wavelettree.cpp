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
#define pll pair<ll, ll>
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

struct WaveletTree2 {
	vvi tree;

	WaveletTree2() {

	}
};

struct WaveletTree {
  typedef vi::iterator iter;
  vvi C;
  int s;

  // sigma = size of alphabet, i.e. one more than the max element in S
  WaveletTree(vi A, int sigma): C(2 * sigma), s(sigma) {
    build(A.begin(), A.end(), 0, s - 1, 1);
  }

  void build(iter b, iter e, int L, int U, int u) {
    if (L == U) return;
    int M = (L + U) / 2;

    C[u].reserve(e - b + 1); C[u].pb(0);
    for (iter it = b; it != e; ++it)
      C[u].pb(C[u].back() + (*it <= M));

    iter p = stable_partition(b, e, [=](int i) {return i <= M;});
    
    build(b, p, L, M, u * 2);
    build(p, e, M + 1, U, 2 * u + 1);
  }

  // Count occurrences of number c until position i
  // ie, occurrences of c in positions [0, i]
  int rank(int c, int i) const {
    // internally make the interval open: [0, i)
    i++;
    int L = 0, U = s - 1, u = 1, M, r;
    while (L != U) {
      M = (L + U) / 2;
      r = C[u][i];
      u *= 2;
      if (c <= M) {
        i = r, U = M;
      } else {
        i -= r; L = M + 1; ++u;
      }
    }
    return i;
  }

  // Find the k-th smallest element in positions [i,j]
  // The smallest element is k=1
  int quantile(int k, int i, int j) {
    // internally consider the open interval [i, j)
    j++;
    int L = 0, U = s - 1, u = 1, M, ri, rj;
    while (L != U) {
      M = (L + U) / 2;
      ri = C[u][i]; rj = C[u][j]; u *= 2;
      if (k <= rj - ri) {
        i = ri, j = rj, U = M;
      } else {
        k -= rj - ri, i -= ri, j -= rj;
        L = M + 1; 
        ++u;
      }
    }
    return U;
  }

  // Count number of occurrences of numbers in the range [a, b]
  // present in the positions [i, j]
  // if representing a grid it counts number of points in the rect
  mutable int L, U;
  int range(int i, int j, int a, int b) const {
    if (j < i || b < a) return 0;
    L = a; U = b;
    return range(i, j + 1, 0, s - 1, 1);
  }

  int range(int i, int j, int a, int b, int u) const {
    if (b < L || U < a) return 0;
    if (L <= a && b <= U) 
      return j - i;
    int M = (a + b) / 2, ri = C[u][i], rj = C[u][j];
    return range(ri, rj, a, M, 2 * u) + range(i - ri, j - rj, M + 1, b, 2 * u + 1);
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cout << sizeof(int) << endl;
  cout << sizeof(ll) << endl;
  cout << sizeof(double) << endl;
  cout << sizeof(ld) << endl;
  
  return 0; 
}
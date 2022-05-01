#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vl vector<ll>
#define vvl vector<vl>
#define vld vector<ld>
#define vvld vector<vld>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define rep(s, l, r) for (int s = l; s < r; s++)
#define per(s, r, l) for (int s = r - 1; s >= l; s--)
#define all(x) x.begin(), x.end()
#define PI acosl(-1) 
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using maxheap = priority_queue<T, vector<T>, less<T>>;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v < hi; };
/*
  Uses the Hungarian algorithm to solve the Assignment problem.
  Finds the MINIMUM assignment of n workers to m tasks. Matching
  at most min(n, m) workers to tasks.

  For MAXIMUM, multiply all weights by -1

  Complexity: O(n^2 * m)

  http://zafar.cc/2017/7/19/hungarian-algorithm/
  Check: https://judge.yosupo.jp/submission/87924
*/

struct Assignment {
  const ll INF = 1e18;

  vpll pairings; // this will have size m!
  ll mincost;

  /* 
    _a is zero-indexed and rectangular (n may differ from m)
    works with negative edge weights too
  */
  void solve(vvl _a) { 
    int n = _a.size();
    int m = _a[0].size();

    vvl a(n + 1, vl(m + 1, 0));
    for (int i = 1; i <= n; i++) {
      copy(_a[i - 1].begin(), _a[i - 1].end(), a[i].begin() + 1);
    }

    vl u(n + 1);
    vl v(m + 1), p(m + 1), way(m + 1);

    for (int i = 1; i <= n; i++) {
      p[0] = i;
      ll j0 = 0;
      vl minv(m + 1, INF);
      vl used(m + 1, false);
      do {
        used[j0] = true;
        ll i0 = p[j0], delta = INF, j1;
        for (int j = 1; j <= m; j++) {
          if (!used[j]) {
            ll cur = a[i0][j] - u[i0] - v[j];
            if (cur < minv[j]) {
              minv[j] = cur, way[j] = j0;
            } 
            if (minv[j] < delta) {
              delta = minv[j], j1 = j;
            }
          }
        }
        for (int j = 0; j <= m; j++) {
          if (used[j]) {
            u[p[j]] += delta, v[j] -= delta;
          } else {
            minv[j] -= delta;
          }
        }
        j0 = j1;
      } while (p[j0] != 0);
      do {
        ll j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }

    pairings.clear();
    for (int i = 1; i <= m; i++) {
      pairings.pb({p[i] - 1, i - 1});
    }
    mincost = -v[0];
  }

};


int main() {

  int N;
  cin >> N;
  vvl _a(N, vl(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> _a[i][j];
    }
  }

  Assignment A;
  A.solve(_a);
  cout << A.mincost << endl;
  vl matches(N);
  for (int i = 0; i < N; i++) 
    matches[A.pairings[i].f] = A.pairings[i].s;
  for (int i = 0; i < N; i++) 
    cout << matches[i] << " \n"[i == N - 1];


  return 0;
}
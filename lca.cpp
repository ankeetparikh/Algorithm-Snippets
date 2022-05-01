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


struct LCA {
  int n, L;
  vvi g, p;
  vi dep;
  LCA(vvi _g, int root) {
    g = _g;
    n = g.size();
    L = 1; while ((1ll << L) < n) L++;
    p.assign(n, vi(L, -1));
    dep.assign(n, 0);
    dfs(root, -1);
    preprocess();
  }

  void dfs(int x, int par) {
    if (par != -1) {
      dep[x] = dep[par] + 1;
      p[x][0] = par;
    }
    for (int y : g[x]) {
      if (y != par) {
        dfs(y, x);
      }
    }
  }

  void preprocess() {
    for (int j = 1; j < L; j++) {
      for (int i = 0; i < n; i++) {
        p[i][j] = p[i][j - 1] == -1 ? -1 : p[p[i][j - 1]][j - 1];
      }
    }
  }

  int lca(int a, int b) {
    if(dep[a] < dep[b]){
      swap(a, b);
    }

    for(int i = L - 1; i >= 0; i--){
      if(dep[a] - (1 << i) >= dep[b]){
        a = p[a][i];
      }
    }

    if(a == b) return a;
    for(int i = L - 1; i >= 0; i--){
      if(p[a][i] != -1 && p[a][i] != p[b][i]){
        a = p[a][i];
        b = p[b][i];
      }
    }

    return p[a][0];
  }
};

int main(){
	int n, q;
  cin >> n >> q;
  vvi g(n);
  for (int i = 1; i <= n - 1; i++) {
    int p; cin >> p;
    g[p].pb(i);
    g[i].pb(p);
  }

  LCA z(g, 0);
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << z.lca(u, v) << endl;
  }
	return 0;
}
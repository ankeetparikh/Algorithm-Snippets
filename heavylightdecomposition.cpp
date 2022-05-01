#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;


struct HeavyLight {
  int n;
  int t;
  vvi g; // input graph
  vi p; // p[i] = parent of i
  vi sz; // sz[i] = size of subtree rooted at i
  vi up; // up[x] = root of heavy path which x is a part
  vi in, out; // enter/exit time for the vertex i. 
  vi arr; // all heavy paths, concatenated together. the first one starts at 0

  // arr[in[x], out[x]) is the subtree rooted at x
  // arr[in[up[x]], out[x]) is the heavy path containing x. 
  //    Note that this heavy path potentially extends beyond out[x]

  HeavyLight(int n_) {
    n = n_;
    g.resize(n); 
  }

  void add_edge(int a, int b) { // ensure a, b are in [0, n)
    g[a].pb(b);
    g[b].pb(a);
  }

  void dfs(int x) { // don't call this directly
    sz[x]++;
    for (int &y : g[x]) {
      if (p[x] == y) continue;
      p[y] = x;
      dfs(y);
      sz[x] += sz[y];
      if (sz[y] > sz[g[x][0]]) {
        swap(y, g[x][0]);
      }
    }
  }

  void dfs_hld(int x) { // don't call this directly
    in[x] = t++;
    arr.pb(x);
    for (int y : g[x]) {
      if (p[x] == y) continue;
      up[y] = y == g[x][0] ? up[u] : y;
      dfs_hld(y);
    }
    out[x] = t;
  }

  void decompose() { // O(n)
    p.assign(n, -1);
    sz.resize(n);
    dfs(0);

    t = 0;
    up.assign(n, 0);
    in.resize(n);
    out.resize(n);
    dfs_hld(0);
  }
};

int main() {
	return 0;
}
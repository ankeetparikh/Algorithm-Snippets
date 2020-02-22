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

class TreeIsomorphism {
  /*
    Use this to check if two trees are isomorphic.
    This does not validate the inputs. The
    inputs must be valid trees. If there are loops,
    multiple connected components, or cycles,
    then the checker will not perform well.
    
    Vertices must be numbered from [0, N)
    Complexity: O(N)
  */

  int N;
  vi depthA, depthB, parA, parB;

  vi findCenters(const vvi &T) {
    // center is the vertex in the middle of the diameter
    // there may be two centers of a Tree
    vi vis(N, 0);
    
    int u = 0;
    vis[u] = 1;
    queue<int> bfs;
    bfs.push(u);
    while (bfs.size()) {
      u = bfs.front(); bfs.pop();
      for (int v : T[u]) {
        if (!vis[v]) {
          vis[v] = 1;
          bfs.push(v);
        }
      }
    }

    int E1 = u;
    // reuse vis for distance
    fill(vis.begin(), vis.end(), 0);
    vi pre(N, -1);
    pre[u] = u;
    vis[u] = 1;
    bfs.push(u);
    while (bfs.size()) {
      u = bfs.front(); bfs.pop();
      for (int v : T[u]) {
        if (pre[v] == -1) {
          vis[v] = vis[u] + 1;
          pre[v] = u;
          bfs.push(v);
        }
      }
    }
    int E2 = u;
    // cout << E1 << " " << E2 << endl;
    if (E1 == E2) {
      return {E1};
    }
    if (vis[E2] == 2) {
      return {E1, E2};
    }
    vi centers;
    int diam = vis[E2];
    u = E2;
    while (u != E1) {
      if (diam & 1) {
        if (vis[u] == (diam + 1) / 2) {
          centers.pb(u);
        }
      } else {
        if (vis[u] == diam / 2 || vis[u] == diam / 2 + 1) {
          centers.pb(u);
        }
      }
      u = pre[u];
    }
    return centers;
  }


  int fill_depths(const vvi A, const int root, vi &depth, vi &par) {
    // returns depth of entire tree
    // depths are computed from [0, D)
    depth.assign(N, -1);
    par.assign(N, -1);
    int u = root;
    depth[u] = 0;
    queue<int> bfs;
    bfs.push(u);
    while (bfs.size()) {
      u = bfs.front(); bfs.pop();
      for (int v : A[u]) {
        if (depth[v] == -1) {
          par[v] = u;
          depth[v] = depth[u] + 1;
          bfs.push(v);
        }
      }
    }
    return depth[u] + 1;
  }

  bool rootedTreeIso(const vvi A, const int rootA, const vvi B, const int rootB) {
    // cout << "roots: " << rootA << " " << rootB << endl;
    int Adepth = fill_depths(A, rootA, depthA, parA);
    int Bdepth = fill_depths(B, rootB, depthB, parB);
    // cout << "depths: " << Adepth << " " << Bdepth << endl;
    if (Adepth != Bdepth) {
      return false;
    }
    int D = Adepth;
    vvi atDepthA(D), atDepthB(D);
    for (int i = 0; i < N; i++) {
      atDepthA[depthA[i]].pb(i);
      atDepthB[depthB[i]].pb(i);
    }
    vi labelA(N), labelB(N);

    auto getLabelsAtLevel = [&](int level, const vvi &T, const vi &par, const vvi &atDepth, const vi &label) -> vector<pair<vi, int>> {
      vector<pair<vi, int>> result;
      for (int vertex : atDepth[level]) {
        vi childlabels;
        for (int ch : T[vertex]) {
          if (ch == par[vertex]) continue;
          childlabels.pb(label[ch]);
        }
        if (childlabels.size() == 0) {
          childlabels.pb(0); // leaf node
        } else {
          sort(childlabels.begin(), childlabels.end());
        }
        result.pb({childlabels, vertex});
      }
      sort(result.begin(), result.end());
      return result;
    };
    for (int d = D - 1; d >= 0; d--) {
      auto levelA = getLabelsAtLevel(d, A, parA, atDepthA, labelA);
      auto levelB = getLabelsAtLevel(d, B, parB, atDepthB, labelB);
      int SZ = levelA.size();
      if (levelB.size() != SZ) {
        return false;
      }
      for (int i = 0; i < SZ; i++) {
        if (levelA[i].f != levelB[i].f) {
          return false;
        }
      }
      int label = 1;
      for (int i = 0; i < SZ; i++) {
        int vertA = levelA[i].s;
        int vertB = levelB[i].s;
        if (i > 0 && levelA[i - 1].f != levelA[i].f) {
          ++label;
        }
        labelA[vertA] = labelB[vertB] = label;
      }
    }
    return labelA[rootA] == labelB[rootB]; 
  }
  
public: 
  // only public method
  bool checkIfIsomorphic(const vvi &A, const vvi &B) {
    N = A.size();
    if (B.size() != N) {
      return false;
    }

    vi centersA = findCenters(A);
    vi centersB = findCenters(B);
    // for (int x : centersA) cout << x << " "; cout << endl;
    // for (int x : centersB) cout << x << " "; cout << endl;
    if (centersA.size() != centersB.size()) {
      return false;
    }
    for (int centerB : centersB) {
      if (rootedTreeIso(A, centersA.back(), B, centerB)) {
        return true;
      }
    }
    return false;
  }
};


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vvi A(n), B(n);
    for (int i = 0; i < n - 1; i++) {
      int x, y; 
      cin >> x >> y;
      --x;
      --y;
      A[x].pb(y);
      A[y].pb(x);
    }
    for (int i = 0; i < n - 1; i++) {
      int x, y; 
      cin >> x >> y;
      --x;
      --y;
      B[x].pb(y);
      B[y].pb(x);
    }
    TreeIsomorphism t;
    if (t.checkIfIsomorphic(A, B)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  
  return 0;
}
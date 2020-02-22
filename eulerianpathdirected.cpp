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
typedef long long ll;
typedef long double ld;
using namespace std;

template<int N>
struct EulerianPathDirected {
  // graph must be directed
  // O(E) time
  // Edges are indexed from [1..n] inclusive

private:
  int inDegree[N], outDegree[N];
  vector<int> g[N];
  int n = -1;
  vector<int> path;

  bool hasEulerianPath() {
    int num_start = 0, num_end = 0;
    for (int i = 1; i <= n; i++) {
      if ((outDegree[i] - inDegree[i] > 1) || (inDegree[i] - outDegree[i] > 1)) {
        return false;
      }
      if (outDegree[i] - inDegree[i] == 1) {
        num_start++;
      }
      if (inDegree[i] - outDegree[i] == 1) {
        num_end++;
      }
    }
    return (num_start == 0 && num_end == 0) || 
            (num_start == 1 && num_end == 1);
  }

  int get_starting_node() {
    int start = 0;
    for (int i = 1; i <= n; i++) {
      if (outDegree[i] - inDegree[i] == 1)
        return i;
      if (outDegree[i] > 0)
        start = i;
    }
    return start;
  }

  void dfs(int x) {
    while (outDegree[x]) {
      dfs(g[x][--outDegree[x]]);
    }
    path.pb(x);
  }

public:
  void setN(int _n) {
    n = _n;
  }
  void addEdge(int a, int b) {
    g[a].pb(b);
    ++outDegree[a];
    ++inDegree[b];
  }

  vector<int> getPath() {
    assert(n >= 0);
    if (!hasEulerianPath()) {
      cout << "No Eulerian path";
      return {};
    }
    dfs(get_starting_node());
    reverse(path.begin(), path.end());
    return path;
  }
};

EulerianPathDirected<101> g;

int main() {
  g.setN(3);

  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  for (int v : g.getPath()) {
    cout << v << endl;
  }
  return 0;
}
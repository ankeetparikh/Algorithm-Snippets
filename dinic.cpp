#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;

template<int N> struct flowgraph {
  struct edge {
    int from, to;
    ll flow, cap;
  };
  // vertices are 1 indexed [1..N]
  vector<int> g[N + 1];
  vector<edge> edges;
  int q[N + 1], d[N + 1], ptr[N + 1];
 
  int n, source, sink;
 
  void addEdge(int from, int to, int cap) {
    g[from].pb(edges.size());
    edges.pb({from, to, 0, cap});
    g[to].pb(edges.size());
    edges.pb({to, from, 0, 0});
  }
 	
 	// constructs the level graph:
 	// d[i] = distance from source to i by minimum number of nonzero capacity edges
 	// doable by simple bfs
  bool bfs() {
    fill(d + 1, d + 1 + n, -1);
    int head = 0, tail = 0;
    q[tail++] = source;
    d[source] = 0;
    while (head < tail) {
      int x = q[head++];
      for (int i : g[x]) {
        int y = edges[i].to;
        if (d[y] == -1 && edges[i].flow < edges[i].cap) {
          d[y] = d[x] + 1;
          q[tail++] = y;
        }
      }
    }
    return d[sink] != -1;
  }
 	
 	// try to route flow from u->sink, using at most flow units of flow
 	// return the actual amount pushed
 	// formally called a "blocking flow"
  ll dfs(int u, ll flow) {
    if (!flow) return 0;
    if (u == sink) return flow;
    for (; ptr[u] < g[u].size(); ++ptr[u]) {
      int i = g[u][ptr[u]];
      int v = edges[i].to;
      if (d[v] == d[u] + 1 && edges[i].flow < edges[i].cap) {
        ll pushed = dfs(v, min(flow, edges[i].cap - edges[i].flow));
        if (pushed) {
          edges[i].flow += pushed;
          edges[i ^ 1].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  } 
 
  ll dinic() {
    ll flow = 0;
    while (bfs()) {
      fill(ptr + 1, ptr + n + 1, 0);
      while (ll pushed = dfs(source, 1e18)) {
        flow += pushed;
      }
    }
    return flow;
  }
};

{
  /*
    In a graph whose edges have capacity 0 or 1,
    the following subroutine finds a path in the
    graph. This modifies the graph. If you call
    it again, you will get another path, disjoint
    from the first one. Call it k times (where
    k is the maximum flow) to get the maximum
    number of disjoint paths.
  */
  flowgraph<505> g;
int maxflow;
vi curr;
int n, m;
void dfs(int x) {
  curr.pb(x);
  if (x == n) return;
  for (int i : g.g[x]) {
    int y = g.edges[i].to;
    if (g.edges[i].flow == 1 && g.edges[i].cap == 1) {
      g.edges[i].flow = 0;
      dfs(y);
      return;
    }
  }
}
}

 
int main(){
	
	flowgraph z;

	int n, m;
	cin >> n >> m;
	z.n = n;
	z.source = 1;
	z.sink = n;
	for(int i = 0; i < m; i++){
		int u, v, c; cin >> u >> v >> c;
		if(u != v){
			z.addedge(u, v, c);
			z.addedge(v, u, c);
		}
	}
	cout << z.dinic() << endl;

	return 0;
}
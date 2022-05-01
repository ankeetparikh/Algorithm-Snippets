#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
using namespace std;

template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

template<int N>
struct mincost_maxflow {
  // assume no negative cost cycles
  // assume no demands
  // uses successive shortest path algo

  struct edge {
    int from, to;
    ll capacity, cost, flow;
  };

  ll inf = 1e18;
  int source, sink;
  vector<int> g[N + 1];
  vector<edge> edges;
  int pre[N], in_queue[N];
  ll dist[N];

  void addEdge(int from, int to, ll capacity, ll cost) { // from and to should be in {1..N}
    g[from].pb(edges.size());
    edge.pb({from, to, capacity, cost, 0});
    g[to].pb(edges.size());
    edge.pb({to, from, 0, -cost, 0});
  }

  bool spfa() { // shortest path faster algo, returns 1 if path exists from source to sink
    for (int i = 1; i <= n; i++) {
      dist[i] = inf;
      in_queue[i] = pre[i] = 0;
    }
    dist[source] = 0;
    minheap<pair<ll, int>> queue;
    queue.push({0, source});
    while (queue.size()) {
      auto v = queue.top().s; queue.pop();
    }
  }

  void augment() {

  }

  void fixCosts() {
    for (edge &e : edges) {
      e.cost += dist[e.from] - dist[e.to];
    }
  }

  pair<ll, ll> solve(int _source, int _sink) {
    source = _source;
    sink = _sink;
    ll flow = 0, cost = 0;
    spfa(); fixCosts();
    while (spfa()) {
      fixcosts();
      augment();
    } 
    return {flow, cost};
  }
};

int main() {
  return 0;
}
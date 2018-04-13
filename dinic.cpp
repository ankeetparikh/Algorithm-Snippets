#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;

struct edge{
	int a, b; ll flow, cap;
};


const int V = 5555;

struct flowgraph{
	// vertices are 0 indexed (0...n-1)
	vector<int> g[V];
	vector<edge> ed;
	int q[V], d[V], ptr[V];

	int n;
	int source, sink;

	void addedge(int a, int b, int c){
		edge u = {a, b, 0, c};
		edge v = {b, a, 0, 0};
		g[a].pb(ed.size());
		ed.pb(u);
		g[b].pb(ed.size());
		ed.pb(v);
	}
	bool bfs(){
		fill(d, d + n, -1);
		int qh = 0, qt = 0;
		q[qt++] = source;
		d[source] = 0;

		while(qh < qt && d[sink] == -1){
			int x = q[qh++];
			for(int i : g[x]){
				int y = ed[i].b;
				if(d[y] == -1 && ed[i].flow < ed[i].cap){
					d[y] = d[x] + 1;
					q[qt++] = y;
				}
			}
		}
		return d[sink] != -1;
	}
	ll dfs(int v, ll flow){
		if(!flow) return 0;
		if(v == sink) return flow;
		for(;ptr[v] < g[v].size(); ptr[v]++){
			int i = g[v][ptr[v]];
			int y = ed[i].b;
			if(d[y] != d[v] + 1) continue;
			ll pushed = dfs(y, min(flow, ed[i].cap - ed[i].flow));
			if(pushed){
				ed[i].flow += pushed;
				ed[i ^ 1].flow -= pushed; // back edge
				return pushed;
			}
		}
		return 0;
	}

	ll dinic(){
		ll flow = 0;
		while(bfs()){
			fill(ptr, ptr + n, 0);
			while(ll pushed = dfs(source, 1e18)){
				flow += pushed;
			}
		}
		return flow;
	}
};
int main(){
	
	flowgraph z;

	int n, m;
	cin >> n >> m;
	z.n = n + 1;
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
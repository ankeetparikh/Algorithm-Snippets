#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;



template<int N> struct scc {
	vector<int> g[N]; 		// directed graph
	vector<int> cond[N]; 	// condensation of g
	vector<int> rev[N]; 	// transpose of g
	vector<int> L;			// SCCs grouped topologically
	int mapping[N];	  		// node i in g corresponds to mapping[i] in h
	int visited[N];
	int n;
	int comps = 0;

	scc() {}
	scc(int _n) {n = _n;}

	/* directed edge from u to v in g */
	void addEdge(int u, int v) {
		g[u].pb(v);
		rev[v].pb(u);
	}

	void visit(int u) {
		if (!visited[u]) {
			visited[u] = true;
			for (int v : g[u]) visit(v);
			L.pb(u);
		}
	}

	void assign(int v, int root) {
		mapping[v] = root;
		for (int u : rev[v]) {
			if (mapping[u] == 0) 
				assign(u, root);
		}
	}

	void computeSCC() {
		for (int i = 1; i <= n; i++) visit(i);
		reverse(L.begin(), L.end());
		for (int x : L) cout << x << endl;
		for (int u : L) {
			if (mapping[u] == 0) assign(u, ++comps);
		}
		for (int i = 1; i <= n; i++) {
			for (int j : g[i]) {
				if (mapping[i] == mapping[j]) continue;
				cond[mapping[i]].pb(mapping[j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			sort(cond[i].begin(), cond[i].end());
			cond[i].resize(unique(cond[i].begin(), cond[i].end()) - cond[i].begin());
		}
	}
};

const int N = 2e5 + 10;
scc<N> graph;
int main() {
	int n; cin >> n;
	graph.n = n;
	for (int i = 1; i <= n; i++) {
		while (true) {
			int x; cin >> x; ++x;
			if (x == 0) break;
			graph.addEdge(i, x);
		}
	}
	graph.computeSCC();
	cout << graph.comps << endl;
	for (int i = 1; i <= graph.comps; i++) {
		for (int y : graph.cond[i]) {
			cout << y - 1 << " ";
		}
		cout << -1 << endl;
	}
	return 0;
}
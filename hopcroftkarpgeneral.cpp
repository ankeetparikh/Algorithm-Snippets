#include <bits/stdc++.h>
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

// NOTE: you might as well run dinic's algorithm
// b/c it has the same complexity on bipartite graphs
// and it is easier to understand
// for general bipartite graph
// if input graph is not bipartite, then an error message is printed 
// to the screen and the entire program is terminated.
// V vertices, labeled 1 to N
// E edges
// runs in O(E * V^0.5) worst case
// with high probability, runs in O(E logV)
// the indices are 1-indexed

struct HopcroftKarpMatching{
	static const int N = 1e5 + 10;
	static const int inf = 2e9;
	static const int NIL = 0;
	int n; 			  // number of vertices
	vector<int> g[N]; // input graph
	vector<int> b[N]; // relabeled graph, first part is right partition, second part is left
	int newlabel[N]; // label after relabeling
	int dist[N];      // 
	int match[N];     // match[i] = vertex i is matched to
	int U = 0, V = 0; // size of respective partitions
	int size = 0;     // size of matching


	void prepare(){
		function<int(int)> sgn = [&](int x) -> int{return (x > 0) - (x < 0);};
		function<void(int, bool)> init = [&](int x, bool left) -> void{
			if(left)
				newlabel[x] = ++U;
			else
				newlabel[x] = -(++V);

			for(int y : g[x]){
				if(newlabel[y] == 0) init(y, !left);
				if(sgn(newlabel[x]) == sgn(newlabel[y])){
					cout << "The input graph is not bipartite.\n";
					exit(0);
				}
			}
		};
		for(int i = 1; i <= n; i++){
			if(newlabel[i] == 0){
				init(i, true);
			}
		}
		for(int i = 1; i <= n; i++){
			if(newlabel[i] < 0){
				newlabel[i] *= -1;
				newlabel[i] += U;
			}
		}
		for(int i = 1; i <= n; i++){
			for(int j : g[i]){
				b[newlabel[i]].pb(newlabel[j]);
				b[newlabel[j]].pb(newlabel[i]);
			}
		}

	}

	bool bfs(){
		queue<int> qu;
		for(int i = 1; i <= U; i++){
			if(match[i] == NIL){
				dist[i] = 0;
				qu.push(i);
			}
			else{
				dist[i] = inf;
			}
		}
		dist[NIL] = inf;
		while(!qu.empty()){
			int left= qu.front(); qu.pop();
			if(left != NIL){
				for(int right : b[left]){
					if(dist[match[right]] == inf){
						dist[match[right]] = dist[left] + 1;
						qu.push(match[right]);
					}
				}
			}
		}
		return dist[NIL] != inf;
	}

	bool dfs(int left){
		if(left != NIL){
			for(int right : b[left]){
				if(dist[match[right]] == dist[left] + 1){
					if(dfs(match[right])){
						match[right] = left;
						match[left] = right;
						return true;
					}
				}
			}
			dist[left] = inf;
			return false;
		}
		return true;
	}

	int maxmatching(){
		prepare();
		memset(match, 0, sizeof(match));
		size = 0;
		while(bfs()){
			for(int i = 1; i <= U; i++){
				if(match[i] == NIL && dfs(i)){
					size++;
				}
			}
		}
		return size;
	}
};

int main(){


	HopcroftKarpMatching h;
	h.n = 20;
	vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {18, 19}, {1, 3}};
	for(pair<int, int> e : edges){
		int u, v; 
		tie(u, v) = e;
		h.g[u].pb(v);
		h.g[v].pb(u);
	}
	cout << h.maxmatching() << endl;

	return 0;
}
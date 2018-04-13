#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int N = 1e5;

vector<int> tree[N];
vector<int> cent[N]; // centroid tree
bool centroidMarked[N];
int subtree_size[N];

void dfs(int u, int p){
	subtree_size[u] = 1;
	for(auto v : tree[u]){
		if(v != p && !centroidMarked[v]){
			dfs(v, u);
			subtree_size[u] += subtree_size[v];
		}
	}
}
int getCentroid(int u, int p, int n){
	bool is_centroid = true;
	int heaviest_child = -1;

	for(auto v: tree[u]){
		if(v != p && !centroidMarked[v]){
			if(subtree_size[v] > n / 2)
				is_centroid = false;
			if(heaviest_child == -1 || subtree_size[v] > subtree_size[heaviest_child])
				heaviest_child = v;
		}
	}
	if(is_centroid && n - subtree_size[u] <= n / 2){
		return u;
	}
	return getCentroid(heaviest_child, u, n);
}

int getCentroid(int u){
	dfs(u, -1);
	int centroid = getCentroid(u, -1, subtree_size[u]);
	centroidMarked[centroid] = true;
	return centroid;
}

int centroidDecomp(int root){
	int centroid = getCentroid(root);
	for(auto v : tree[centroid]){
		if(!centroidMarked[v]){
			int centroidsub = centroidDecomp(v);
			cent[centroid].pb(centroidsub);
			cent[centroidsub].pb(centroid);
		}
	}
	return centroid;
}
void addEdge(int a, int b){
	tree[a].pb(b);
	tree[b].pb(a);
}
int main(){
	addEdge(1, 4);
	addEdge(2, 4);
	addEdge(3, 4);
	addEdge(4, 5);
	addEdge(5, 6);
	addEdge(6, 7);
	addEdge(7, 8);
	addEdge(7, 9);
	addEdge(6, 10);
	addEdge(10, 11);
	addEdge(11, 12);
	addEdge(11, 13);
	addEdge(12, 14);
	addEdge(13, 15);
	addEdge(13, 16);

	int c = centroidDecomp(1);
	for(auto x : cent[c]){
		cout << x << endl;
	}
	return 0;
}
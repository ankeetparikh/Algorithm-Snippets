#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 100000;
const int L = 20;
int n; // # of nodes in the graph

int dep[N], p[N][L];
vector<int> g[N];

void dfs(int x, int par){
	dep[x] = 0;
	if(0 <= par && par < n) p[x][0] = par, dep[x] = dep[par] + 1;
	for(int ch : g[x]){
		if(ch != par) dfs(ch, x);
	}
}

void preprocess(){
	// assume p[i][0] is the parent of i, -1 if i is the root

	for(int j = 1; (1 << j) < n; j++){
		for(int i = 0; i < n; i++){
			if(p[i][j - 1] != -1){
				p[i][j] = p[p[i][j - 1]][j - 1];
			}
		}
	}
}

int lca(int a, int b){
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

int main(){
	memset(p, -1, sizeof p);
	n = 5;
	g[0] = {1, 2};
	g[1] = {0};
	g[2] = {0, 3, 4};
	g[3] = {2};
	g[4] = {2};
	dfs(0, -1);
	preprocess();
	cout << lca(2, 3) << endl;
	return 0;
}
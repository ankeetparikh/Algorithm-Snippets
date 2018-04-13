#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 100000;
vector<int> g[N];
int n;

int low[N], val[N], timer = 0;

void dfs(int x, int p){
	val[x] = timer;
	low[x] = timer;
	timer++;
	for(int u : g[x]){
		if(u == p) continue;
		if(val[u] == -1){
			dfs(u, x);
			if(low[u] > val[x]){
				printf("%d to %d is a bridge\n", x, u);
			}
			low[x] = min(low[x], low[u]);
		}
		else low[x] = min(low[x], low[u]);
	}
}


int main(){
	fill(val, val + N, -1); //NEED THIS!!
	n = 7;
	g[0] = {1};
	g[1] = {0,2,3};
	g[2] = {1};
	g[3] = {1, 4, 6};
	g[4] = {3, 5};
	g[5] = {4, 6};
	g[6] = {3, 5};
	dfs(0, -1);

	return 0;
}
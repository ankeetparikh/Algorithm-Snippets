#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <bitset>
#include <map>
#include <queue>
#include <complex>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <stack>

typedef long long ll;
typedef long double ld;

#define pb push_back
#define mp make_pair

using namespace std;

const int N = 555;
vector<int> g[N];
int n, m, s, t;
ll res[N][N];
set<int> u;
bool vis[N];
int pre[N];

void clear(){
	for(int i=0; i<N; i++) vis[i] = false;
	for(int i=0; i<N; i++) pre[i] = i;
}

bool bfs(){
	clear();
	u.clear();
	queue<int> nds;
	nds.push(s);
	vis[s] = true;
	while(!nds.empty()){
		auto x = nds.front(); nds.pop();
		u.insert(x);
		for(int nei: g[x]){
			if(!vis[nei] && res[x][nei] > 0){
				pre[nei] = x;
				vis[nei] = true;
				nds.push(nei);
			}
		}
	}
	return pre[t] != t;

}

int main(){
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i=0; i<m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(u == v) continue;
		if(res[u][v] == 0) g[u].pb(v);
		res[u][v] += w;
		if(res[v][u] == 0) g[v].pb(u);
		
	}
	
	while(bfs()){
		ll minf = 1e18;
		for(int ptr = t; ptr != s; ptr = pre[ptr]){
			int pp = pre[ptr], nn = ptr;
			minf = min(minf, res[pp][nn]);
		}
		for(int ptr = t; ptr != s; ptr = pre[ptr]){
			int pp = pre[ptr], nn = ptr;
			res[pp][nn] -= minf;
			res[nn][pp] += minf;
		}
	}
	printf("%d\n", (int)u.size());
	for(auto x : u){
		printf("%d\n", x);
	}
	return 0;
}
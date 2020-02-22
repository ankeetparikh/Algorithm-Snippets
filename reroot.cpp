#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;

const int N = 2e5 + 10;
int n, a[N];
ll sum[N];
vector<int> g[N];

void init(int x, int p = 0){
	sum[x] = a[x];
	for(int y : g[x]){
		if(y == p) continue;
		init(y, x);
		sum[x] += sum[y];
	}
}

void go(int x, int p = 0){
	// now, sum[i] is the sum of a[j] such that j is in the subtree of i rooted at x

	for(int y : g[x]){
		if(y == p) continue;

		// root at y
		sum[x] -= sum[y];
		sum[y] += sum[x];

		go(y, x);

		// undo root (in other words, root at x)
		sum[y] -= sum[x];
		sum[x] += sum[y];
	}
}

int main(){
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		g[u].pb(v); g[v].pb(u);
	}
	init(1); // argument to init and go must be the same
	go(1);

	return 0;
}
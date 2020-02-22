#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

/*
	Queries supported:
	add point to plane
	remove point from plane
	# of points in rectangular region

	Time complexity: n * logn * logn per query
	Space complexity: roughly n * logn
	Constraints: MAX_X <= 2e5
				 MAX_Y <= 2e5
	
	Queries must be known in advance so as to determine
	which BITs will contain the points

*/
const int N = 2e5 + 10;
int a[N], b[N], posa[N], posb[N];
int n, m;
vector<int> q[N];
vector<int> vals[N];
vector<int> f[N];

void addupdate(int x, int y){
	if(x < 0 || y < 0) return;
	for(int i = x; i < N; i |= i + 1){
		vals[i].pb(y);
	}
}

void addget(int x, int y){
	if(x < 0 || y < 0) return;
	for(int i = x; i >= 0; i = (i & (i + 1)) - 1){
		vals[i].pb(y);
	}
}

void update(int x, int y, int delta){
	// cout << "update " << x << " " << y << endl;
	for(int i = x; i < N; i |= i + 1){
		int j = lower_bound(vals[i].begin(), vals[i].end(), y) - vals[i].begin();
		for(; j < f[i].size(); j |= j + 1){
			f[i][j] += delta;
		}
	}	
}

int get(int x, int y){
	// cout << "get " << x << " " << y << endl;
	if(x < 0 || y < 0) return 0;
	int res = 0;
	for(int i = x; i >= 0; i = (i & (i + 1)) - 1){
		// cout << f[i].size() - 1 << " " << *lower_bound(vals[i].begin(), vals[i].end(), y) << endl;
		int j = lower_bound(vals[i].begin(), vals[i].end(), y) - vals[i].begin();
		for(; j >= 0; j = (j & (j + 1)) - 1){
			res += f[i][j];
		}
	}
	return res;
}

int main(){

	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]); 
		a[i]--;
		posa[a[i]] = i;
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &b[i]); 
		b[i]--;
		posb[b[i]] = i;
	}
	for(int i = 0; i < m; i++){
		int t; scanf("%d", &t);
		if(t == 1){
			int l, r, ll, rr; scanf("%d%d%d%d", &l, &r, &ll, &rr);
			--l; --r; --ll; --rr;
			q[i] = {t, l, r, ll, rr};
		} else {
			int x, y; scanf("%d%d", &x, &y); 
			--x; --y;
			q[i] = {t, x, y};
		}
	}
	vector<int> tmp(b, b + n);
	for(int i = 0; i < n; i++) addupdate(posa[i], posb[i]);
	for(int i = 0; i < m; i++){
		int t = q[i][0];
		if(t == 1){
			int x = q[i][1], xx = q[i][2], y = q[i][3], yy = q[i][4];
			addget(xx, yy); addget(xx, y - 1); addget(x - 1, yy); addget(x - 1, y - 1);
		} else {
			int x = q[i][1], y = q[i][2];
			addupdate(posa[b[x]], posb[b[x]]);
			addupdate(posa[b[y]], posb[b[y]]);
			swap(b[x], b[y]); swap(posb[b[x]], posb[b[y]]);
			addupdate(posa[b[x]], posb[b[x]]);
			addupdate(posa[b[y]], posb[b[y]]);
		}
	}
	for(int i = 0; i < n; i++) b[i] = tmp[i], posb[b[i]] = i;
	for(int i = 0; i < N; i++){
		sort(vals[i].begin(), vals[i].end());
		vals[i].resize(unique(vals[i].begin(), vals[i].end()) - vals[i].begin());
		f[i].resize(vals[i].size(), 0);
	}
	for(int i = 0; i < n; i++) update(posa[i], posb[i], 1);
	for(int i = 0; i < m; i++){
		int t = q[i][0];
		if(t == 1){
			int x = q[i][1], xx = q[i][2], y = q[i][3], yy = q[i][4];

			int res = 0;
			res += get(xx, yy);
			res -= get(xx, y - 1);
			res -= get(x - 1, yy);
			res += get(x - 1, y - 1);
			printf("%d\n", res);
		} else {
			int x = q[i][1], y = q[i][2];
			update(posa[b[x]], posb[b[x]], -1);
			update(posa[b[y]], posb[b[y]], -1);
			swap(b[x], b[y]); swap(posb[b[x]], posb[b[y]]);
			update(posa[b[x]], posb[b[x]], 1);
			update(posa[b[y]], posb[b[y]], 1);
		}
	}
	return 0;
}
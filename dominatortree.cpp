#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define vld vector<ld>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vpll vector<pll>
#define rep(s, l, r) for (int s = l; s < r; s++)
#define per(s, r, l) for (int s = r - 1; s >= l; s--)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

// 0 to n - 1
struct dsu {
	vi f;
	dsu(int n) {
		f.resize(n);
		iota(all(f), 0);
	}
	int find(int x) {
		return f[x] == x ? x : (f[x] = find(f[x]));
	}
	void merge(int x, int y) {
		f[find(x)] = find(y);
	}
};

// 0 to n - 1
struct Dominator {
	int n;
	vvi g, rg, tree, bucket;
	vi sdom, par, dom, label, arr, rev;
	dsu d;
	int T;
	Dominator(const vvi _g): 
		n(_g.size()),
		g(_g), rg(n), tree(n), bucket(n),
		sdom(n), par(n), dom(n), label(n), arr(n), rev(n),
		d(n), 
		T(0) {}
	

	void dfs(int u) {
		T++;
		arr[u] = T;
		rev[T] = u;
		label[T] = sdom[T] = T;
		for (int w : g[u]) {
			if (!arr[w]) {
				dfs(w);
				par[arr[w]] = arr[u];
			}
			rg[arr[w]].pb(arr[u]);
		}
	}

	void build(int root) {
		dfs(root);
		per(i, n, 0) {
			for (int j : rg[i]) setmin(sdom[i], )
		}
	}
};

int main() {
	return 0;
}
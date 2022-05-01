#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
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
template<class T> using maxheap = priority_queue<T, vector<T>, less<T>>;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

struct Kuhn {
	// Maximum bipartite matching algorithm (without edge weights)
	// This algo is used b/c it's simple to implement. However, using Dinic's algorithm for 
	// the same problem is faster - O(V^0.5 * E).
	// Runtime: O(VE) = O((A + B) * AB) ~ O(n^3)
	// Memory: O(V + E) = O(A + B + AB) = O(AB)
	int A, B; // size of LEFT and RIGHT parts respectively (nodes must be indexed from 0..A-1, 0..B-1)
	vvi g; // only contains adj lists of nodes in LEFT part
	vi match; // i is in the RIGHT set, match[i] is in the LEFT set, match[i] = -1 if no match
	vector<bool> used; // for elements in the LEFT set

	Kuhn(int AA, int BB): A(AA), B(BB) {
		g.assign(A, {});
		match.assign(B, -1);
	}

	// a must be in left part, b in right
	// must have 0 <= a < A, 0 <= b < B
	void add_edge(int a, int b) {
		g[a].pb(b);
		match[b] = -1;
	}

	// a must be in the LEFT part
	bool try_kuhn(int a) {
		if (used[a]) {
			return false;
		}
		used[a] = true;
		for (int to : g[a]) {
			if (match[to] == -1 || try_kuhn(match[to])) {
				match[to] = a;
				return true;
			}
		}
		return false;
	}

	void solve() {
		for (int a = 0; a < A; a++) {
			used.assign(A, false);
			try_kuhn(a);
		}
		for (int b = 0; b < B; b++) {
			int a = match[b];
			if (a != -1) {
				cout << a << " is matched to " << b << endl;
			}
		}
	}
};

int main() {
	Kuhn k(2, 2);
	k.add_edge(0, 1);
	k.add_edge(1, 0);
	k.add_edge(1, 1);
	k.solve();
	return 0;
};
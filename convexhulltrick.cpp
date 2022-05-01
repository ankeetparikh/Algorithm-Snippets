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
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
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

struct CHTAscending {
	/* 
		UNTESTED
		Insert lines in ascending (non-decreasing) order of slope.
		Query a point x, returns min(mx + b) for all lines (m, b) in the set.
		Runtime is 
			O(1) amortized for addLine
			O(logn) for query
		For Descending (non-increasing):
			If the slopes are descending, then the negative slopes are ascending.
			Also,
				max(m_j * x_i + b_j) = max((-m_j) * (-x_i) + b_j)
			So, insert the lines with negative slopes, and then query at -x
	*/

	struct seg {
		ld x; ll m, b;
	};
	vector<seg> hull;

	void addLine(ll m, ll b) {
		if (hull.size()) {
			assert(hull.back().m <= m);
		}
		while (hull.size()) {
			seg s = hull.back();
			if (s.b + s.m * s.x > b + m * s.x) {
				if (s.m - m) hull.pb({(b - s.b) / ld(s.m - m), m, b});
				return;
			}
			hull.pop_back();
		}
		hull = {{LLONG_MIN, m, b}};
	}

	ll query(ll x) {
		seg s = *--upper_bound(all(hull), x, [](ll a, seg b){ return a < b.x; });
		return s.m * x + s.b;
	}
};

struct LiChaoTree {
	/*
		Untested (use at your own risk) 
		Works if N = MAXN is not too high (something like 2e5)
		O(logN) everywhere
	*/
	struct line {
		ll m, b;
	};
	const int N = 2e5 + 10;
	vector<line> tree;
	LiChaoTree() {
		tree.resize(4 * N);
	}
private:
	ll f(const line &a, const ll &x) {
		return a.m * x + a.b;
	}
	void addLine(int node, int lo, int hi, line a) {
		int mid = (lo + hi) / 2;
		bool L = f(a, lo) < f(tree[node], lo);
		bool M = f(a, mid) < f(tree[node], mid);
		if (M) {
			swap(tree[node], a);
		}
		if (lo == hi) {
			return;
		} else if (L != M) {
			addLine(2 * node + 1, lo, mid, a);
		} else {
			addLine(2 * node + 2, mid + 1, hi, a);
		}
	}
	ll get(int node, int lo, int hi, ll x) {
		int mid = (lo + hi) / 2;
		if (lo == hi) {
			return f(tree[node], x);
		} else if (x <= mid) {
			return min(f(tree[node], x), get(2 * node + 1, lo, mid, x));
		} else {
			return min(f(tree[node], x), get(2 * node + 2, mid + 1, hi, x));
		}
	}
public:
	void addLine(ll m, ll x) {
		addLine(0, 0, N - 1, {m, x});
	}

	ll get(ll x) {
		return get(x, 0, 0, N - 1);
	}
};

int main() {
  return 0;
}
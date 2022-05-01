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

struct dsu {
	int n;
	vi f;
	dsu(int _n) {
		n = _n;
		f.resize(n);
		iota(all(f), 0);
	}
	int find(int x) {
		return x == f[x] ? x : (f[x] = find(f[x]));
	}
	void merge(int x, int y) {
		int xx = find(x);
		int yy = find(y);
		if (xx != yy) f[xx] = yy;
	}
};

int main(){
	
	return 0;
}

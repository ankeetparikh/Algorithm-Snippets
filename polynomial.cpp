#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

vector<ll> interpolate(vector<ll> x, vector<ll> y) {
	int k = x.size() - 1;
	vector<ll> res;
	for (int j = 0; j <= k; j++) {
		vector<ll> poly = {1};
		ll denom = 1;
		for (int m = 0; m <= k; m++) {
			if (m == j) continue;
			vector<ll> copy = poly;
			vector<ll> copy2 = poly;
			copy.insert(copy.begin(), 0);
			for (ll& x : copy2) x = (x * -m % mod + mod) % mod;
			poly = add(copy, copy2);
			denom = denom * inv[(j - m + mod) % mod] % mod;
		}

		denom %= mod; denom += mod; denom %= mod;
		
		for (ll& x : poly) x = (x * denom) % mod;
		for (ll& x : poly) x = (x * y[j]) % mod;
		res = add(res, poly);
	}
	return res;
}

struct polynomial {
	vector<ll> p;

	polynomial() {}
	polynomial(ll x) {
		p = {x};
	}
	polynomial(vector<ll> pp) {
		p = pp;
		while (p.size() && p.back() == 0) p.pop_back();
		if (p.size() == 0) p = {0};
	}

	ll operator[](int x) {
		assert(0 <= x && x < p.size());
		return p[x];
	}

	bool isZero() {
		return p.size() == 1 && p[0] == 0;
	}

	// naive O(n^2)
	// use ntt when the size of p or b is large
	polynomial operator*(polynomial b) {
		int n = p.size();
		int m = b.p.size();
		vector<ll> c(n + m - 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				c[i + j] += p[i] * b[j];
			}
		}
		return polynomial(c);
	}

	polynomial operator+(polynomial b) {
		vector<ll> c(max(p.size(), b.p.size()), 0);
		for (int i = 0; i < c.size(); i++) {
			ll u = i < p.size() ? p[i] : 0;
			ll v = i < b.p.size() ? b[i] : 0;
			c[i] = u + v;
		}
		return polynomial(c);
	}

	polynomial operator-(polynomial b) {
		return *this + (b * -1);
	}

	ostream& operator<<(ostream& os) {
		for (int i = 0; i < p.size(); i++) {
			os << p[i];
			
		}
		return os;
	}
};

int main() {

	polynomial a({1, 2, 3});
	polynomial b({3, 4, 5});
	cout << (a + b) << endl;
	return 0;
}
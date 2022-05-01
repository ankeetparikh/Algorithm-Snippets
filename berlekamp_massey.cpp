#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

vector<ll> operator+(vector<ll> a, vector<ll> b) {
	vector<ll> c(max(a.size(), b.size()));
	for (int i = 0; i < c.size(); i++) {
		ll u = i < a.size() ? a[i] : 0;
		ll v = i < b.size() ? b[i] : 0;
		c[i] = u + v;
	}
	return c;
}

vector<ll> berlekamp_massey(vector<ll> s) {
	int N = s.size();

	vector<ll> C = {0, 1};
	vector<ll> B = {0, 1};
	int L = 0;
	int m = 0;
	ll b = 1;

	for (int n = 0; n < N; n++) {
		// calculate discrepancy
		ll d = s[n];
		for (int i = 1; i <= L && n - i >= 0; i++)
			d += C[i] * s[n - i];
		if (d == 0) {
			m++
		} else if (2 * L <= n) {

		} else {
			
		}
	}

	return C;
}

int main() {
	vector<ll> a = {1, 2, 3};
	vector<ll> b = {1, 2};
	vector<ll> c = a + b;
	for (ll x : c) cout << x << endl;
	return 0;
}
#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;

const int MX = 63;

// computes rref
vector<bitset<MX>> gaussmod2(vector<bitset<MX>> a, int n, int m) {
	for (int i = 0, j = 0; i < n && j < m; j++) {
		for (int k = i; k < n; k++) if (a[k][j]) swap(a[i], a[k]);
		if (!a[i][j]) continue;
		for (int k = 0; k < n; k++) if (k != i && a[k][j]) a[k] ^= a[i];
		i++;
	}
	return a;
}

int main() {
	
	// max xor subsequence
	int n; cin >> n;
	vector<ll> x(n);
	for(ll &xx : x) cin >> xx;
	sort(x.rbegin(), x.rend());
	vector<bitset<MX>> a;
	for (int i = 0; i < n; i++) {
		bitset<MX> bs;
		for (int j = 0; j < MX; j++) {
			bs[MX - 1 - j] = x[i] & (1ll << j);
		}
		a.pb(bs);
	}
	a = gaussmod2(a, n, MX);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < MX; j++) {
			if (a[i][j]) ans ^= 1ll << (MX - 1 - j);
		}
	}
	cout << ans << endl;

	return 0;
}
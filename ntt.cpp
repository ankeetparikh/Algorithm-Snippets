#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/* How to find the variables gen, root, root_1, root_pw with Mathematica:

mod = 7340033;
FactorInteger[mod - 1]
c = mod - 1;
While[Mod[c, 2] == 0, c /= 2;]
c
gen = PrimitiveRoot[mod]
root = PowerMod[gen, c, mod]
root1 = PowerMod[root, mod - 2, mod] 

*/

// int mod = 7340033;      // 2 ^ k * c + 1
// int gen = 3;			   // primitive root modulo mod
// int root = 2187;        // root ^ (2 ^ k) = 1 (modulo mod)
// int root_1 = 4665133;   // root * root_1 = 1 (modulo mod)
// int root_pw = (1<<20);  // (1 << k) , or equivalently, (p - 1) / c

int mod = 1004535809;   // 2 ^ k * c + 1
int gen = 3;			// primitive root modulo mod
int root = 702606812; 	// root ^ (2 ^ k) = 1 (modulo mod)
int root_1 = 700146880;	// root * root_1 = 1 (modulo mod)
int root_pw = (1<<21);  // (1 << k) , or equivalently, (p - 1) / c



ll powmod(ll a, ll b, ll mod){
	if(b == 0) return 1 % mod;
	if(b & 1) return powmod(a, b - 1, mod);
	return powmod(a * a % mod, b / 2, mod);
}

void ntt(vector<ll> &a, bool invert){
	int n = a.size();

	// bit reverse copy procedure
	for(int i = 1, j = 0; i < n; i++){
		int bit = n / 2;
		for(; j >= bit; bit /= 2){
			j -= bit;
		}
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len *= 2){
		
		ll wlen = invert ? root_1 : root;
		for(int i = len; i < root_pw; i *= 2){
			wlen = wlen * wlen % mod;
		}
		for(int i = 0; i < n; i += len){
			ll w = 1;
			for(int j = 0; j < len / 2; j++){
				ll u = a[i + j];
				ll v = a[i + j + len / 2] * w % mod;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;

				if(a[i + j] >= mod) a[i + j] -= mod;
				if(a[i + j + len / 2] < 0) a[i + j + len / 2] += mod;
				w = w * wlen % mod;
			}
		}
	}

	if(invert){
		ll ninv = powmod(n, mod - 2, mod);
		for(int i = 0; i < n; i++) a[i] = a[i] * ninv % mod;
	}
}

vector<ll> multiply(vector<ll> a, vector<ll> b){
	int n = 1;
	while(n < 2 * max(a.size(), b.size())) n *= 2;
	a.resize(n);
	b.resize(n);

	ntt(a, false);
	ntt(b, false);

	for(int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;

	ntt(a, true);
	a.resize(n / 2);
	return a;
}

vector<ll> powmod(vector<ll> a, int b){
	if(b == 1) return a;
	vector<ll> c = powmod(a, b/2);
	c = multiply(c, c);
	if(b&1) c = multiply(c, a);
	return c;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N = 250000;
	vector<bool> pr(N, true);
	pr[0] = pr[1] = false;
	for(int i = 2; i < N; i++){
		if(pr[i]){
			for(int j = i + i; j < N; j+=i){
				pr[j] = false;
			}
		}
	}
	vector<int> prpi(N, 0);
	for(int i = 2; i < N; i++){
		prpi[i] += prpi[i-1];
		if(pr[i]) prpi[i]++;
	}

	int n = 20000;
	vector<ll> ct(n+1, 0);
	for(int i = 1; i < N; i++){
		if(prpi[i] <= n) ct[prpi[i]]++;
	}
	
	
	cout << powmod(ct, n)[n] << endl;

	return 0;
}







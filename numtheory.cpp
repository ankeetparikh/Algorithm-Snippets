#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll mod = 1e9 + 7;

ll powmod(ll a, ll b, ll mod){
	if(b == 0) return 1;
	if(b & 1) return 
}

void mobiusseive(int *mu, int n){ // bound is inclusive
	for(int i = 0; i <= n; i++) mu[i] = 0;
	mu[1] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 2 * i; j <= n; j+=i){
			mu[j] -= mu[i];
		}
	}
}

vector<ll> generate(vector<int> primes, ld bound){
	// generate all positive integers that are <= bound
	// and whose prime factors are in the vector primes
	if(primes.empty()){
		return {1LL};
	}
	int p = primes.back();
	primes.pop_back();
	vector<ll> res = generate(primes, bound);
	for(int i = 0; i < res.size(); ++i){
		if(res[i] * 1.0 * p > bound) continue;
		res.push_back(res[i] * p);
	}
	return res;
}

void totientsieve(int *tot, int n){
	for(int i=1;i<=n;i++)tot[i]=i;
	for(int i=2;i<=n;i++){
		if(tot[i] == i){
			for(int j=i; j<=n; j+=i) 
				tot[j] = tot[j] / i * (i-1); 
		}
	}
}

//inverse with eed (a and m must be coprime, returns 0 if they are not)
int inv(int a, int m) {
	return a < 2 ? a : ((1 - m * 1ll * inv(m % a, a)) / a % m + m) % m;
}

void factandinv(ll* inv, ll* fac, ll* finv, ll n, ll mod){

	// i!, 1/i and 1/(i!)
	fac[0] = fac[1] = 1;
	inv[1] = 1;
	finv[0] = finv[1] = 1;
	for(int i=2; i<=n; i++){
		fac[i] = (i * fac[i-1]) % mod;
		inv[i] = (mod - (mod/i) * inv[(mod%i)] % mod) % mod;
		finv[i] = (inv[i] * finv[i-1]) % mod;
	}
}


// stirling numbers of the second kind
// paritions of a set of size n into k nonempty subsets
ll stirling2(ll* inv, ll* fac, ll* finv, int n, int k){
	ll ans = 0;
	for(int j = 0; j <= k; j++){
		ll cur = fac[k] * finv[j] % mod * finv[k - j] % mod * powmod(j, n, mod) % mod;
		if((k - j) & 1) ans -= cur;
		else ans += cur;
		ans %= mod;
	}
	return ans * finv[k] % mod;
}

multiset<int> factor(int x){
	multiset<int> sol;
	while(x%2==0) x/=2, sol.insert(2);
	for(int i = 3; i*i <= x; i+=2){
		while(x%i==0) sol.insert(i), x/=i;
	} 
	if(x > 2) sol.insert(x);
	return sol;
}

ll russianpeasantmultiply(ll a, ll b, ll mod){
	// if (mod + mod) does not overflow, then you should be good
	a %= mod;
	b %= mod;
	if(a > b) swap(a, b);
	ll c = 0;
	while(a){
		if(a & 1) c = (c + b) % mod;
		a >>= 1;
		b = (b + b) % mod;
	}
	return c;
}


ll powmod64(ll a, ll b, ll m){
    if(b == 0) return 1;
    if(b & 1) return russianpeasantmultiply(a, powmod64(a, b - 1, m), m);
    return powmod64(russianpeasantmultiply(a,a,m),b/2,m);
}

// deterministic variant for integers <= 2^63 - 1
// needs powmod64 and russianpeasantmultiply
bool miller(ll n){
	// make this global
	vector<ll> a = {2, 325, 9375, 28178, 450775, 9780504, 1795265022ll};
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;

    ll d = n - 1, r = 0;
    while(d % 2 == 0) d /= 2, r++;
    
    for(int i = 0; i < a.size(); i++){
        if(a[i] < n &&  n % a[i] == 0) return false;
        ll aa = a[i];
        if(aa < n && n % aa == 0) return false;
        aa %= n;
        if(aa == 0) continue;
        ll x = powmod64(aa, d, n);
        if(x == 1 || x == n - 1) continue;
        ll dd = d;
        while(dd != n - 1){
            x = russianpeasantmultiply(x, x, n);
            if(x == 1) return false;
            if(x == n - 1) break;
            dd *= 2;
        }
        if(dd == n - 1 && x != -1) return false;
    }
    return true;
}


int main(){
	
	int n; cin >> n;
	int mu[n + 1];
	mobiusseive(mu, n + 1);
	cout << mu[n] << endl;

	return 0;
}
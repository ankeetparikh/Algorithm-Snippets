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

// russian peasant multiplication
ll multiply(ll a, ll b, ll mod){
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

ll powmod(ll a, ll b, ll m){
	if(b == 0) return 1;
	ll c = powmod(a, b / 2, m);
	c = multiply(c, c, m);
	if(b & 1) c = multiply(c, a, m);
	return c;
}

ll gcd(ll a, ll b){
	return  b == 0 ? a : gcd(b, a%b);
}

// given a and b
// computes integers x and y such that
// a*x + b*y = g
// g = gcd(a,b);

void eed(ll a, ll b, ll *x, ll *y, ll *g){
	if(a == 0){
		*x = 0, *y = 1 , *g = b;
		return;
	}
	ll x1,y1;
	eed(b%a, a, &x1, &y1, g);
	*x = y1 - (b/a)*x1;
	*y = x1;
	
}

// true if prime
// if n + n does not overflow we should be good
// need multiply and powmod methods above
bool miller(ll n){

	static ll bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

	if(n < 2) return false;
	if(n == 2 || n == 3) return true;
	if(n % 2 == 0) return false;
	ll r = 0, d = n - 1;
	while(d % 2 == 0){
		r++;
		d /= 2;
	}
	for(int i = 0; i < 7; i++){
		ll a = bases[i] % n;
		ll x = powmod(a, d, n);
		if(x == 1 || x == n - 1) continue;
		bool pr = 0;
		for(int j = 0; j < r - 1; j++){
			if(x == 0) return 1;
			x = multiply(x, x, n);
			if(x == n - 1){
				pr = 1; break;
			}
		}
		if(x == 0) return 1;
		if(pr) continue;
		return 0;
	}
	return 1;
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

multiset<int> factor(int x){
	multiset<int> sol;
	while(x%2==0) x/=2, sol.insert(2);
	for(int i = 3; i*i <= x; i+=2){
		while(x%i==0) sol.insert(i), x/=i;
	} 
	if(x > 2) sol.insert(x);
	return sol;
}


ll get_nontrivial_factor(ll n) {
  auto g = [=](ll x) -> ll {
    ll result = multiply(x, x, n) + 1;
    if (result >= n) result -= n;
    return result;
  };
  for (int i = 2; i <= 2; i++) {
    ll x = i, y = i, d = 1;
    while (d == 1) {
      x = g(x); y = g(g(y)); d = gcd(abs(x - y), n);
    }
    if (d != 1 && d != n) return d;   
  }
  return n;
}

// returns prime factors of n
// faster than trial division for large n
vector<ll> factor_rho(ll n) {
  if (miller(n)) return {n};
  vector<ll> factors;
  while (n > 1) {
    ll f = get_nontrivial_factor(n);
    if (miller(f)) {
      factors.push_back(f);
    } else {
      for (auto pr : factor_rho(f))
        factors.push_back(pr);
    }
    n /= f;
  }
  return factors;
}

int main(){
  ll N = 1238926361552897L;
  auto result = factor_rho(N);
  for (auto pr : result) {
    cout << pr << endl;
  }
	return 0;
}
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define pb push_back


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

int main(){
	cout << russianpeasantmultiply(923874528345ll, 20394875345ll, 500) << endl;
	return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>
#include <complex>

typedef long long ll;
typedef long double ld;

using namespace std;


// extended euclidean algorithm
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

// finds the solution to the system
// x = a0 (mod n0)
// x = a1 (mod n1)
// ...
// x = a_{k-1} (mod n_{k-1})
// where ni and nj are coprime for i != j
// a and n are arrays of the same size, k is the length


ll crt(ll* a, ll* n, int k){
	ll P = 1; // will hold prod of all n_i
	for(int i=0; i<k; i++) P*=n[i];
	ll x = 0;
	for(int i=0; i<k; i++){
		ll M, m, g, Ni = P/n[i];
		eed(Ni , n[i], &M, &m, &g);
		x += a[i] * M % P * Ni % P;
		x %= P;
	}
	return x % P;
}

int main(){
	ll a[3] = {2,3,2};
	ll n[3] = {3,5,7};
	ll x = crt(a, n, 3);
	cout << x << endl;
	return 0;
}






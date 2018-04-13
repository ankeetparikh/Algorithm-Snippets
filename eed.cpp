#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>


typedef long long ll;
using namespace std;


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

int main(){
	ll x,y,g;
	ll a = 5, b = 15;
	eed(a,b,&x,&y,&g);
	cout << g << endl;
}

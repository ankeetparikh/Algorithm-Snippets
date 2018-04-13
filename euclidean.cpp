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

ll gcd(ll a, ll b){
	return  b == 0 ? a : gcd(b, a%b);
}

int main(){
	ll a = 5;
	ll b = 10;
	ll g = gcd(a,b);
	printf("%lld\n", g);
}
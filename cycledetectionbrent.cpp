#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
using namespace std;

const int MX = 2000000;
ll a, b, c;

ll f(ll x) {
	return (a * x + x % b) % c;
}

ll brent() {
	ll power, lambda, tortoise, hare, x0 = 1, mu;
	power = lambda = 1;
	tortoise = x0;
	hare = f(x0);
	while (tortoise != hare) {
		if (power == lambda) {
			tortoise = hare;
			power *= 2;
			lambda = 0;
		}
		hare = f(hare);
		lambda++;
		if (lambda > MX) return -1;
	}

	mu = 0;
	tortoise = hare = x0;
	for (int i = 0; i < lambda; i++) hare = f(hare);

	while (tortoise != hare) {
		tortoise = f(tortoise);
		hare = f(hare);
		mu++;
	}
	if (mu + lambda > MX) return -1;
	return mu + lambda;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> a >> b >> c;
	cout << brent() << endl;
	return 0;
}
#include <bits/stdc++.h>
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;


int main(){
	// rng based on a high precision clock
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	// get a random integer
	cout << rng() << " " << rng() << endl;

	// randomly shuffle an array
	vector<int> a = {1, 2, 3, 4, 5};
	shuffle(a.begin(), a.end(), rng);
	for(auto aa : a) cout << aa << " "; cout << endl;

	// in a range (for longs)
	uniform_int_distribution<ll> uid(40,50);
	cout << uid(rng) << " " << uid(rng) << endl;

  // in a range (for doubles)
  uniform_real_distribution<ld> rand_double(0, 1);
  cout << rand_double(rng) << endl;

	return 0;
}
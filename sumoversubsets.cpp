#include<bits/stdc++.h>
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

const int C = 20;
int f[1 << C];

// f[mask] will store sum of a[i] for all i that is
// a subset of mask: O(C * 2^C) where C is the number
// of bits in the representation of any a[i];

void compute(vector<int> a){

	for(int x : a){
		f[x] = x;
	}

	for(int i = 0; i < C; i++){
		for(int mask = 0; mask < (1 << C); mask++){
			if(mask & (1 << i))
				f[mask] += f[mask^(1<<i)];
		}
	}
}

int main(){

	return 0;
}
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

#define MAX 10000
bool pr[MAX];
vector<int> primes;

void primelist(int n){
	primes.clear();
	for(int i=0; i<=n; i++) pr[i] = true;
	for(int i=2; i<=n; i++){
		if(pr[i]){
			primes.push_back(i);
			for(int j=2*i; j<=n; j+=i) pr[j] = false;
		}
	}
}

int main(){
	primelist(100);
	for( auto k : primes){
		printf("%d\n", k);
	}
	return 0;
}

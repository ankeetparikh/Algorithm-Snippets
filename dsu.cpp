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

#define N 100100

int P[N];


void pre(){
	for(int i=0; i<N; i++) P[i] = i;
}

int find(int x){
	return P[x] == x ? x : (P[x] = find(P[x]));
}

void merge(int p, int q){
	P[find(p)] = find(q);
}

int main(){
	pre();
	return 0;
}

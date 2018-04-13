#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <queue>
#include <set>
#include <algorithm>
#include <stack>
#include <complex>
#include <cmath>
using namespace std;

typedef long long ll;
typedef long double ld;

/////////////////////////////////////////////////

const int maxn = 1e5;
int f[maxn];

int n = 50000;

// 0 indexed

inline void add(int ind, int x){
	for(int i = ind; i<n; i |= (i+1)) f[i]+=x;
}


inline int sum(int ind){
	int s = 0;
	for(int i = ind; i>=0; i = (i&(i+1))-1) s+=f[i];
	return s;
}

// 1 indexed
inline void add(int ind, int x){
	for(int i = ind; i <= n; i += i&-i) f[i]+=x;
}

inline int sum(int ind){
	int s = 0;
	for(int i = ind; i>0; i-=i&-i) s+=f[i];
	return s;
}


/////////////////////////////////////////////////




int main(){
	
	return 0;
}

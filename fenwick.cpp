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

// range update point query:
// update(i, j, x): increase all values in a[i..j] by x
// value(i): return a[i]

inline void add(int ind, int x) {
	for (int i = ind; i <= n; i += i & -i) f[i] += x; 
}
inline void range_add(int l, int r, int delta) {
	add(l, delta);
	add(r + 1, -delta);
}
inline int point_query(int ind) {
	int s = 0;
	for (int i = ind; i > 0; i -= i & -i) s += f[i];
	return s;
}

// range update range query:
// update(i, j, x): increase all values in a[i..j] by x
// sum(i): return a[1] + a[2] + ... + a[i]

int b1[maxn], b2[maxn];

inline void add(int *b, int ind, int delta) {
	for (int i = ind; i <= n; i += i & -i) b[i] += delta;
}
inline void range_add(int l, int r, int delta) {
	add(b1, l, delta);
	add(b1, r + 1, -delta);
	add(b2, l, x * (l - 1));
	add(b2, r + 1, - x * r);
}
inline int sum(int *b, int ind) {
	// return b[1] + b[2] + ... + b[ind]
	int s = 0;
	for (int i = ind; i > 0; i -= i & -i) s += b[i];
	return s;
}
inline int prefix_sum(int ind) {
	return sum(b1, ind) * ind - sum(b2, ind);
}

/////////////////////////////////////////////////




int main(){
	
	return 0;
}

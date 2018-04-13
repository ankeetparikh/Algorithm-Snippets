#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <bitset>
#include <set>
#include <complex>
#include <queue>
#include <stack>


#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

const ld pi = acos(-1.0);
const ld e  = exp(1.0);

// solution to rmqsq
int inf = numeric_limits<int>::max();
int n;
int q;
int a[100010];
int st[4*100010];

void update(int nind, int ns, int ne, int vind, int v){
	if(ne < vind || ns > vind) return;
	if(ns == ne){
		st[nind] = v;
		return;
	}
	int mid = (ns+ne)>>1;
	update(2*nind+1, ns, mid, vind, v);
	update(2*nind+2, mid+1, ne, vind, v);
	st[nind] = min(st[2*nind+1], st[2*nind+2]); 
}

int rmq(int nind, int ns, int ne, int qs, int qe){
	if(ns > qe || ne < qs) return inf;
	if(ns >= qs && ne <= qe) return st[nind];
	int mid = (ns+ne)>>1;
	return min(rmq(2*nind+1, ns, mid, qs, qe), rmq(2*nind+2, mid+1, ne, qs, qe));
}


int main(){
	scanf("%d", &n);	
    for(int i=0; i<n; i++){
    	 scanf("%d", a+i);
    	 update(0, 0, n-1, i, a[i]);
    }
    scanf("%d", &q);
    for(int i=0; i<q; i++){
    	int x, y;
    	scanf("%d%d", &x, &y);
    	printf("%d\n", rmq(0,0,n-1,min(x,y), max(x,y)));
    }
    return 0;
}
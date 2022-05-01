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
#include <climits>


#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

const ld pi = acos(-1.0);
const ld e  = exp(1.0);

struct RMQ {
  int n, L;
  vi a;
  vvi table;

  RMQ(vi _a) {
    a = _a;
    n = a.size();
    L = 32 - __builtin_clz(n);
    table.assign(L, vi(n, 0));
    rep(i, 0, n) {
      table[0][i] = a[i];
    }
    rep(j, 1, L) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int get_min(int L, int R) {
    int d = R - L + 1;
    int j = 31 - __builtin_clz(d);
    return min(table[j][L], table[j][R - (1 << j) + 1]);
  }
};

int n;
int q;
int a[100010];
int sp[100010][17];

void buildsparsetable(){
	for(int i=0; i<n; i++) sp[i][0] = a[i];
	
	for(int j=1; (1<<j) <= n; j++){
		for(int i=0; i + (1<<j) - 1 < n; i++){
			sp[i][j] = min(sp[i][j-1], sp[i+(1<<(j-1))][j-1]);
		}
	}	
}

int rmq(int l, int r){
	int d = (int)(log(r-l+1) / log(2.0));
	return min(sp[l][d], sp[r-(1<<d)+1][d]);
}

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", a+i);
	buildsparsetable();
	scanf("%d", &q);
	for(int qq = 1; qq<=q; qq++){
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", rmq(min(x,y), max(x,y)));
	}
    return 0;
}
#include <bits/stdc++.h>
typedef long long ll;    
typedef long double ld;  
#define pb push_back     
using namespace std;

#define N 5
#define T (1<<N)

int x[T];
int y[T];

bitset<T> convolution(bitset<T> X, bitset<T> Y){
	#define REP(i, n) for((i)=0;(i) < (n); (i)++)
	int i,j;
	
	REP(i,T) x[i] = X[i];
	REP(i,N) REP(j,T) if(!(j&(1<<i))) x[j^(1<<i)] += x[j];
	
	REP(i,T) y[i] = Y[i];
	REP(i,N) REP(j,T) if(!(j&(1<<i))) y[j^(1<<i)] += y[j];
	
	REP(i,T) x[i] *= y[i];
	
	REP(i,N) REP(j,T) if(j&(1<<i)) x[j] -= x[j^(1<<i)];
	
	bitset <T> ans;
	REP(i,T) ans[i] = (x[i] != 0);
	#undef REP
	return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    bitset<T> a;
    bitset<T> b;
    a[0] = a[2] = 1;
    b[1] = b[3] = 1;
    bitset<T> c = convolution(a, b);
    for(int i = 0; i < T; i++) cout << a[i];
    cout << endl;
    for(int i = 0; i < T; i++) cout << b[i];
    cout << endl;
    for(int i = 0; i < T; i++) cout << c[i];
    cout << endl;
    

    return 0;
}

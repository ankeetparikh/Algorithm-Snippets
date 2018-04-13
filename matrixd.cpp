#include <bits/stdc++.h>


#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

// matrix of 64 bit floating point integers
// useful for numerical problems
//////////////////////////////////////////////////////////////
const int MAXN = 20;

struct matrix{
	int N = MAXN; // N <= MAXN
	ld a[MAXN][MAXN]; 
	
	matrix(){
		memset(a, 0, sizeof(a));
	}
	matrix(int n){
		N = n;
		memset(a, 0, sizeof(a));
	}
	decltype(a[0]) operator[](int x){
		return a[x];
	}
	static matrix  I(int n){
		matrix m(n);
		for(int i = 0; i < n; i++) m[i][i] = 1.0;
		return m;
	}

	matrix friend inverse(matrix &a){
		matrix c;
		
		return c;
	}
	
	matrix friend operator*(matrix &a, matrix &b){
		matrix c;
		for(int i=0; i<a.N; i++){
			for(int j=0; j<a.N; j++){
				for(int k = 0; k<a.N; k++){
					c[i][j] += 1ll * a[i][k] * b[k][j] % mod;
					if(c[i][j] >= mod) c[i][j] -= mod;
				}
			}
		}
		return c;
	}
	matrix friend operator^(matrix &a, ll b){
		if(b < 0){
			return inverse(a)^-b;
		}
		matrix ans = I(a.N);
		while(b){
			if(b%2!=0) ans = ans*a;
			a = a*a;
			b>>=1;
		}
		return ans;
	}
	
};
//////////////////////////////////////////////////////////////


int main(){
	
	matrix m(2);
	m[0][0] = 0;
	m[0][1] = 3;
	m[1][0] = 1;
	m[1][1] = 2;
	
	ll n;
	cin >> n;
	
	m = m ^ n;
	
	cout << (m[0][0])<< endl;
	
    return 0;
}














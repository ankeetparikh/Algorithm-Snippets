#include <bits/stdc++.h>
using namespace std;

typedef __int128 ll;
ostream& operator<<(ostream& os, __int128 a){
	stack<int> st;
	if(a < 0) {
		os << "-"; a = -a;
	}
	if(a == 0){
		os << 0; return os;
	}
	while(a > 0){
		st.push(a % 10);
		a /= 10;
	}
	while(st.size()){
		os << st.top(); st.pop();
	}
	return os;
}

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}
struct frac{
	ll n, d;

	void reduce(){
		ll g = gcd(n, d);
		if(g){
			n /= g; d /= g;
		}
	}

	frac(){}
	frac(ll nn, ll dd): n(nn), d(dd) {
		if(n == 0 || d == 0){
			n = 0; d = 1;
		}
		reduce();
	}
	friend ostream& operator<<(ostream& os, frac a){
		os << a.n << "/" << a.d; return os;
	}
	friend frac operator+(frac a, frac b){
		return frac(a.n * b.d + a.d * b.n, a.d * b.d);
	}
	friend frac operator-(frac a, frac b){
		return frac(a.n * b.d - a.d * b.n, a.d * b.d);
	}
	friend frac operator*(frac a, frac b){
		return frac(a.n * b.n, a.d * b.d);
	}
	friend frac operator/(frac a, frac b){
		return frac(a.n * b.d, a.d * b.n);
	}
	friend frac operator-(frac a){
		return frac(-a.n, a.d);
	}
};


char p[20], s[20];
frac mat[20][20];

ll g(){
	int n = strlen(p);
	for(int i = 0; i <= n; i++) s[i] = p[i];
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= n; j++){
			mat[i][j] = frac(0,0);
			if(j == n) mat[i][j] = frac(10,1);
		}
	}
	mat[0][0] = frac(1,1);
	mat[0][1] = frac(-1,1);

	for(int i = 1; i < n; i++){
		s[i-1] = p[i-1];
		mat[i][i] = frac(10,1);
		for(int d = 0; d < 10; d++){
			// get digit d as next digit
			s[i] = d + '0';
			if(s[i] == p[i]){
				if(i < n - 1) mat[i][i + 1] = frac(-1,1);
				continue;
			}
			int mxlen = 0;
			for(int len = 1; len <= i + 1; len++){
				
				for(int k = 0; k < len; k++){
					if(p[k] != s[i + 1 - len + k]) break;
					if(k == len - 1) mxlen = len;
				}
			}
			mat[i][mxlen] = mat[i][mxlen] + frac(-1,1);
		}
	}
	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j <= n; j++){
	// 		cout << mat[i][j].n << " ";
	// 	}
	// 	cout << endl;
	// }
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			frac mul = mat[j][i] / mat[i][i];
			for(int k = 0; k <= n; k++) 
				mat[j][k] = mat[i][k] * -mul + mat[j][k];
		}	
	}
	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j <= n; j++){
	// 		cout << mat[i][j].n << " ";
	// 	}
	// 	cout << endl;
	// }
	ll sum = 0;
	for(int i = 0; i < n; i++) sum += mat[i][n].n;
	if(sum < 0) {
		printf("%s\n", p);
	}
	return sum - n + 1;
}

int main(){
	
	// sprintf(p, "%lld", (long long) 3030303030303L);
	// cout << g() << endl;
	ll ans = 0;
	for(int n = 2; n <= 999999; n++){
		long long up = 1e16;
		long long x = up / n;
		sprintf(p, "%lld", x);
		ans += g();
	}
	cout << ans << endl;
	return 0;
}
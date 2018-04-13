#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define pb push_back
using namespace std;

typedef complex<ld> cld;
const double pi = acos(-1.0);
const int N = 500500;

void fft(vector<cld> &a, bool invert){
	int n = a.size();

	// bit reverse copy procedure
	for(int i = 1, j = 0; i < n; i++){
		int bit = n / 2;
		for(; j >= bit; bit /= 2){
			j-=bit;
		}
		j+=bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len *= 2){
		double angle = 2 * pi / len * (invert ? -1 : 1);
		cld wnrt = cld(cos(angle), sin(angle));
		for(int i = 0; i < n; i+=len){
			cld w(1);
			for(int j = 0; j < len / 2; j++){
				cld u = a[i + j], v = w * a[i + j + len / 2];
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wnrt;
			}
		}
	}

	if(invert){
		for(int i = 0; i < n; i++) a[i] /= (ld)n;
	}

}

vector<int> multiply(vector<int> &a, vector<int> &b){
	vector<cld> fa(a.begin(), a.end()), fb(a.begin(), a.end());
	int n = 1;
	while(n < 2 * max(a.size(), b.size())) n*=2;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);
	for(int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	vector<int> c(n);
	for(int i = 0; i < n; i++){
		c[i] = (int)round(fa[i].real());
	}
	return c;
}

int main(){
	vector<int> a = {1,1,2,2};
	vector<int> b = {1,1};
	vector<int> c = multiply(a, a);
	for(int u : c ) cout << u << " ";
	cout << endl;
	return 0;
}
#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T v, T lo, T hi) { return lo <= v && v <= hi; };

typename<class T>
struct Complex {
  T a, b;
  
};

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
  srand(time(NULL));
	const int N = 1e6;
  vi a(N), b(N);
  for (int i = 0; i < N; i++) {
    a[i] = rand();
    b[i] = rand();
  }
  ld start = clock();
  vi product = multiply(a, b);
  ld finish = clock();
  cout << "time taken: " << (finish - start) / CLOCKS_PER_SEC << " seconds" << endl;
	return 0;
}
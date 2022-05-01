#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vl vector<ll>
#define vvl vector<vl>
#define vld vector<ld>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vpll vector<pll>
#define rep(s, l, r) for (int s = l; s < r; s++)
#define per(s, r, l) for (int s = r - 1; s >= l; s--)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using maxheap = priority_queue<T, vector<T>, less<T>>;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

namespace XorConvolution {

	void xor_transform(vl &a, bool invert = false) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		for (int L = 2; L <= n; L *= 2) {
			for (int i = 0; i < n; i += L) {
				for (int j = 0; j < L / 2; j++) {
					ll u = a[i + j];
					ll v = a[i + j + L / 2];
					a[i + j] = u + v;
					a[i + j + L / 2] = u - v;
					if (invert) {
						a[i + j] /= 2;
						a[i + j + L / 2] /= 2;
					}
				}
			}
		}
	}

	vl xor_convolution(vl a, vl b) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		assert(n == b.size());
		xor_transform(a);
		xor_transform(b);
		vl c(n);
		rep(i, 0, n) c[i] = a[i] * b[i];
		xor_transform(c, true);
		return c;
	}
};

namespace OrConvolution {
		void or_transform(vl &a, bool invert = false) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		for (int L = 2; L <= n; L *= 2) {
			for (int i = 0; i < n; i += L) {
				for (int j = 0; j < L / 2; j++) {
					ll u = a[i + j];
					ll v = a[i + j + L / 2];
					if (!invert) {
						a[i + j] = u + v;
						a[i + j + L / 2] = u;
					} if (invert) {
						a[i + j] = v;
						a[i + j + L / 2] = u - v;
					}
				}
			}
		}
	}

	vl or_convolution(vl a, vl b) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		assert(n == b.size());
		or_transform(a);
		or_transform(b);
		vl c(n);
		rep(i, 0, n) c[i] = a[i] * b[i];
		or_transform(c, true);
		return c;
	}
};

namespace AndConvolution {
		void and_transform(vl &a, bool invert = false) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		for (int L = 2; L <= n; L *= 2) {
			for (int i = 0; i < n; i += L) {
				for (int j = 0; j < L / 2; j++) {
					ll u = a[i + j];
					ll v = a[i + j + L / 2];
					if (!invert) {
						a[i + j] = u + v;
						a[i + j + L / 2] = v;
					} if (invert) {
						a[i + j] = u - v;
						a[i + j + L / 2] = v;
					}
				}
			}
		}
	}

	vl and_convolution(vl a, vl b) {
		int n = a.size();
		assert((n & (n - 1)) == 0);
		assert(n == b.size());
		and_transform(a);
		and_transform(b);
		vl c(n);
		rep(i, 0, n) c[i] = a[i] * b[i];
		and_transform(c, true);
		return c;
	}
};

void pr(vl c) {
	cout << '[';
	for (int i = 0; i < c.size(); i++) {
		cout << c[i];
		if (i + 1 < c.size()) cout << ", ";
	}
	cout << "]\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    vl a = {3, 4};
    vl b = {5, 2};

    pr(XorConvolution::xor_convolution(a, b));
    pr(OrConvolution::or_convolution(a, b));
    pr(AndConvolution::and_convolution(a, b));

    return 0;
}

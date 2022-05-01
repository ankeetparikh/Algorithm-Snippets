#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define pii pair<int, int>
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define rep(s, l, r) for (int s = l; s < r; s++)
#define per(s, r, l) for (int s = r - 1; s >= l; s--)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> void setmax(T& a, T b) { a = max(a, b); };
template<typename T> void setmin(T& a, T b) { a = min(a, b); };
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

template<ll MOD>
struct ModInt {
	ll x = 0;
	ModInt() { x = 0; }
	ModInt(ll _x) { 
		x = _x; 
		if (x >= MOD || x <= -MOD) x %= MOD;
		if (x < 0) x += MOD;
	}
	friend ModInt operator+(ModInt a, ModInt b) {
		return ModInt(a.x + b.x);
	}
	friend ModInt operator-(ModInt a, ModInt b) {
		return ModInt(a.x - b.x);
	}
	friend ModInt operator*(ModInt a, ModInt b) {
		return ModInt(a.x * b.x);
	}
	friend ModInt operator/(ModInt a, ModInt b) {
		return a * inv(b);
	}
	friend ModInt operator+=(ModInt &a, ModInt b) {
		return a = a + b;
	}
	friend ModInt power(ModInt a, ll b) {
		if (b == 0) return 1;
		ModInt c = power(a, b / 2);
		return c * c * ((b & 1) ? a : 1);
	}
	friend ModInt inv(ModInt a) {
		// this only works for nonzero elements
		return power(a, MOD - 2);
	}
	friend ostream& operator<<(ostream &os, const ModInt &a) {
		os << a.x;
		return os;
	}
	friend istream& operator>>(istream &is, ModInt &a) {
		ll y; is >> y; a = ModInt(y);
		return is;
	}
};

using mint = ModInt<1000000007>;
using vm = vector<mint>;
using vvm = vector<vm>;


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  mint b = 1 / 2;
  cout << b << endl;

  return 0; 
}
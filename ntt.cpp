#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int mod = 998244353;    // 2 ^ k * c + 1
const int g = 3;        // primitive root modulo mod 
 
namespace ntt{
  int root = -1; 
  int root_1 = -1;
 
  ll powmod(ll a, ll b, ll mod){
    ll res = 1;
    ll pow_a = a;
    while (b) {
      if (b & 1) {
        res = res * pow_a % mod;
      }
      b >>= 1;
      pow_a = pow_a * pow_a % mod;
    }
    return res;
  }
  
  ll fix(ll x){
    if(x < 0) x += mod;
    if(x >= mod) x -= mod;
    return x;
  }
 
  void ntt(vector<ll> &a, bool invert){
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
      int bit = n / 2;
      for(; j >= bit; bit /= 2) j -= bit;
      j += bit; if(i < j) swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len *= 2){
      ll wlen = invert ? root_1 : root;
      for(int i = len; i < n; i *= 2) wlen = wlen * wlen % mod;
      for(int i = 0; i < n; i += len){
        for(int j = 0, w = 1; j < len / 2; j++, w = (w * wlen) % mod){
          ll u = a[i + j];
          ll v = a[i + j + len / 2] * w % mod;
          a[i + j] = fix(u + v);
          a[i + j + len / 2] = fix(u - v);
        }
      }
    }
 
    if(invert){
      ll inv_n = powmod(n, mod - 2, mod);
      for(int i = 0; i < n; i++)
        a[i] = a[i] * inv_n % mod;
    }
  }
 
  void clamp(vector<ll> &a) {
    while (a.size() > 1 && a.back() == 0)
      a.pop_back();
  }
 
  vector<ll> naive_multiply(vector<ll> &a, vector<ll> &b) {
    int n = a.size();
    int m = b.size();
    vector<ll> c(n + m - 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        c[i + j] += a[i] * b[j] % mod;
        c[i + j] %= mod;
      }
    }
    return c;
  }
 
  vector<ll> multiply(vector<ll> &a, vector<ll> &b){
    clamp(a); clamp(b);
    int n = a.size() + b.size();
    if (n <= 200) {
      return naive_multiply(a, b);
    }
    while(n & (n - 1)) n += n & -n;
    a.resize(n);
    b.resize(n);
    root = powmod(g, (mod - 1) / n, mod);
    root_1 = powmod(root, mod - 2, mod);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    ntt(a, true);
    clamp(a);
    return a;
  }
 
  // returns only the first few coefficients 
  // folded on each other of course 
  // so make sure the length is sufficiently high before
  // calling this method
  vector<ll> powmod(vector<ll> a, ll b){
    int n = a.size();
    while(n & (n - 1)) n += n & -n;
    a.resize(n);
    root = powmod(g, (mod - 1) / n, mod);
    root_1 = powmod(root, mod - 2, mod);
    ntt(a, false);
    for(int i = 0; i < n; i++) 
      if(a[i] != 0) 
        a[i] = powmod(a[i], b, mod);
    ntt(a, true);
    return a;
  }
}

int main(){
	vector<ll> a = {1, 2, 3, 0, 0, 0, 0};
	for(ll aa : ntt::multiply(a, a)) cout << aa << " "; cout << endl;
	for(ll aa : ntt::powmod(a, 2)) cout << aa << " "; cout << endl;
	return 0;
}


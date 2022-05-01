#include <bits/stdc++.h>
#define f first
#define s second
#define endl '\n'
#define pb push_back
#define pii pair<int, int>
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
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };
struct timestamp {
  string algo;
  ld A, B;

  timestamp(string _algo) {
    algo = _algo;
    A = B = clock();
  }
  void print() {
    ld B_ = clock();
    ld section = (B_ - B) / CLOCKS_PER_SEC;
    ld cumulative = (B_ - A) / CLOCKS_PER_SEC;
    cout << algo << " profile(seconds): section " << section << " cumulative: " << cumulative << endl << flush;
    B = B_;
  }
} t("pe 501");

/*
  Meissel-Lehmer algorithm
*/

const int MX = 4e7; // MX is the maximum value of sqrt(N) + 2
bool isPrime[MX];
int primePi[MX];
vector<ll> P;

void init() {
  for (int i = 2; i < MX; i++)
    isPrime[i] = true;
  for (int i = 2; i < MX; i++) {
    if (isPrime[i]) {
      for (int j = i + i; j < MX; j += i) {
        isPrime[j] = false;
      }
    }
  }
  for (int i = 2; i < MX; i++) {
    primePi[i] = primePi[i - 1] + isPrime[i];
  }
  for (int i = 2; i < MX; i++) {
    if (isPrime[i]) {
      P.push_back(i);
    }
  }
}

/*
  number of integers in 2..N whose smallest prime factor is <= P[K]
*/
ll rec(ll N, int K) {
  if (N <= 1 || K < 0) return 0;
  if (N <= P[K]) return N - 1;
  if (N < MX && ll(P[K]) * P[K] > N) {
    return (N - 1) - (primePi[N] - primePi[P[K]]);
  }

  const int LIM = 250;
  static int memo[LIM * LIM][LIM];
  bool do_mem = N < LIM * LIM;
  if (do_mem && memo[N][K]) return memo[N][K];
  
  ll result = N / P[K] - rec(N / P[K], K - 1) + rec(N, K - 1);
  
  if (do_mem) memo[N][K] = result;
  return result;
}

ll count_primes(ll N) {
  if (N < MX)
    return primePi[N];
  static map<ll, ll> memo;
  if (memo.count(N)) return memo[N];
  int K = primePi[(int)sqrt(N) + 1];
  return memo[N] = (N - 1) - (rec(N, K) - primePi[P[K]]);
}

ll power(ll a, ll b) {
  if (b == 0) return 1;
  return power(a, b - 1) * a;
}
int main(){
  init();

  ll n = 1e12;
  ll result = 0;

  for (int i = 0; power(P[i], 7) <= n; i++) {
    result++;
  }
  for (int i = 0; power(P[i], 3) <= n; i++) {
    ll qmax = n / power(P[i], 3);
    result += count_primes(qmax);
    if (qmax >= P[i])
      result--;
  }
  for (int i = 0; power(P[i], 3) <= n; i++) {
    for (int j = i + 1; j < P.size() && P[i] * P[j] * P[j] < n; j++) {
      ll qmax = n / (P[i] * P[j]);
      result += count_primes(qmax) - j - 1;
    }
  }
  cout << result << endl;
  t.print();
	return 0;
}
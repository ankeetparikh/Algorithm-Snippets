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
template<typename T> bool in(T lo, T v, T hi) { return lo <= v && v <= hi; };

// useful for profiling algorithms
// (or sections of algorithms)

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
    cout << algo << " profile(seconds): section: " << section << " cumulative: " << cumulative << endl << flush;
    B = B_;
  }
};

int main() {
  timestamp t("algo");
  int x = 0;
  for (int i = 0; i < 1010101; i++) x+=i;
  cout << x << endl;
  t.print();
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#define rep(i, a, b) for (int i = a; i < b; i++)
using namespace std;



template<typename T>
struct MinFunctor {
  T operator()(T a, T b) { return min(a, b); }
};

// F must be associative!
template<typename T, typename F>
struct SparseTable {
  F f;
  int n, L;
  vector<vector<T>> table;

  SparseTable(const vector<T> _a, F _f) {
    f = _f;
    n = _a.size();
    L = 32 - __builtin_clz(n);
    table.assign(L, vector<T>(n, T()));
    rep(i, 0, n) {
      table[0][i] = _a[i];
    }
    rep(j, 1, L) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        table[j][i] = f(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int get(int L, int R) {
    int d = R - L + 1;
    int j = 31 - __builtin_clz(d);
    return f(table[j][L], table[j][R - (1 << j) + 1]);
  }
};

int main() {
    
  vector<int> a = {4, 9, 1, 8};

  SparseTable s(a,  MinFunctor<int>());
  
  cout << s.get(0, 1) << endl;
  cout << s.get(1, 3) << endl;

  return 0;
}
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
typedef long long ll;
typedef long double ld;
using namespace std;
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

/*
  Uses the Hungarian algorithm to solve the Assignment problem.
  Note: The assignment problem is to find the MAXIMUM total
  sum. If you want min, then turn each weight w into 
  MAX_WEIGHT - w.

  Input: Square matrix of side length N with non-negative entries.
  Output: Array [c_0, c_1, ..., c_{N-1}] where the assignments
  are (0, c_0), (1, c_1), ..., (N - 1, c_{N - 1})

  Complexity: O(N ^ 3)

  https://www.cc.gatech.edu/~rpeng/18434_S15/hungarianAlgorithm.pdf
*/

int n, k; // bipartitions
vvi g;
vi mt;
vi used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int y : g[v]) {
    if (mt[y] == -1 || try_kuhn(mt[y])) {
      mt[y] = v;
      return true;
    }
  }
  return false;
}

void solve() {
  mt.assign(k, -1);
  for (int v = 0; v < n; v++) {
    assert(mt[v] == -1); // can remove this assertion, just notice that it evals to true!
    used.assign(n, 0);
    try_kuhn(v);
  }
  for (int i = 0; i < k; i++) {
    if (mt[i] != -1) {
      printf("%d %d\n", mt[i] + 1, i + 1);
    }
  }
}
int main() {
  return 0;
}
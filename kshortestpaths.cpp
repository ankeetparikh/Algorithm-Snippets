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
  Finds the lengths of the k shortest paths
  from 1 to n.
  
  Complexity:
  O(k * n * log(k * n))

  Source:
  https://en.wikipedia.org/wiki/K_shortest_path_routing

  Solution to:
  https://cses.fi/problemset/task/1196

  Algorithm paraphrased:
    Keep track of count[u], which is the number of paths
    from source to u found. These paths are the shortest
    length paths. Keep paths in a heap, pull out the path
    with the shortest length, and add edges incrementally.
*/

const int N = 1e5 + 10;
vpii g[N];
int cnt[N];
vector<ll> lengths;
int n, m, k;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].pb({b, c});
  }

  // {cost, endpoint}
  multiset<pair<ll, int>> B;
  B.insert({0, 1});
  while (B.size() && cnt[n] < k) {
    auto [cost, endpt] = *B.begin();
    B.erase(B.begin());
    cnt[endpt]++;
    if (endpt == n) {
      lengths.pb(cost);
    }
    if (cnt[endpt] <= k) {
      for (auto [y, wei] : g[endpt]) {
        B.insert({cost + wei, y});
      }
    }
  }

  for (auto len : lengths) {
    cout << len << " ";
  }
  cout << endl;
  return 0;
}
#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

// solution to https://www.spoj.com/problems/MATSUM/
// sum of rectangle and point update

const int N = 1030;
int tree[4 * N][4 * N];
char s[4];
int n;
int x, y, num;
int xx, yy;

void update(int node_x, int lo_x, int hi_x, int node_y, int lo_y, int hi_y) {
  if (y < lo_y || hi_y < y) return;
  if (lo_y == hi_y) {
    if (lo_x == hi_x) {
      tree[node_x][node_y] = num;
    } else {
      tree[node_x][node_y] = tree[2 * node_x + 1][node_y] + tree[2 * node_x + 2][node_y];
    }
  } else {
    int mid = (lo_y + hi_y) / 2;
    update(node_x, lo_x, hi_x, 2 * node_y + 1, lo_y, mid);
    update(node_x, lo_x, hi_x, 2 * node_y + 2, mid + 1, hi_y);
    tree[node_x][node_y] = tree[node_x][2 * node_y + 1] + tree[node_x][2 * node_y + 2];
  }
}

void update(int node_x, int lo_x, int hi_x) {
  if (x < lo_x || hi_x < x) return;
  if (lo_x < hi_x) {
    int mid = (lo_x + hi_x) / 2;
    update(2 * node_x + 1, lo_x, mid);
    update(2 * node_x + 2, mid + 1, hi_x);
  }
  update(node_x, lo_x, hi_x, 0, 0, n - 1);
}

void update() {
  update(0, 0, n - 1);
}

int sum(int node_x, int lo_x, int hi_x, int node_y, int lo_y, int hi_y) {
  if (yy < lo_y || hi_y < y) return 0;
  if (y <= lo_y && hi_y <= yy) {
    return tree[node_x][node_y];
  }
  int mid = (lo_y + hi_y) / 2;
  return sum(node_x, lo_x, hi_x, 2 * node_y + 1, lo_y, mid) + sum(node_x, lo_x, hi_x, 2 * node_y + 2, mid + 1, hi_y);
}

int sum(int node_x, int lo_x, int hi_x) {
  if (xx < lo_x || hi_x < x) return 0;
  if (x <= lo_x && hi_x <= xx) {
    return sum(node_x, lo_x, hi_x, 0, 0, n - 1);
  }
  int mid = (lo_x + hi_x) / 2;
  return sum(2 * node_x + 1, lo_x, mid) + sum(2 * node_x + 2, mid + 1, hi_x);
}

int sum() {
  return sum(0, 0, n - 1);
}

void solve() {
  scanf("%d", &n);
  vector<pair<int, int>> locs;
  while (true) {
    scanf("%s", s);
    if (s[1] == 'E') {
      scanf("%d%d%d", &x, &y, &num);
      update();
      locs.pb({x, y});
    } else if (s[1] == 'U') {
      scanf("%d%d%d%d", &x, &y, &xx, &yy);
      printf("%d\n", sum());
    } else {
      break;
    }
  }

  for (auto& p : locs) {
    int u = p.f, v = p.s;
    x = u; y = v; num = 0;
    update();
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
#include<bits/stdc++.h>

typedef long long ll;
typedef long double ld;

#define pb push_back
#define mp make_pair

using namespace std;

int n, m;

const int N = 400010;
vector<int> g[N];
vector<int> tour;
int first[N], last[N];
ll st[4*N], lazy[4*N];
int c[N];
int qs, qe, v;

void dfs(int x, int p){
    tour.pb(x);
    first[x] = tour.size();
    for(int ch : g[x]){
        if(ch != p) dfs(ch, x);
    }
    last[x] = tour.size();
}

inline void push(int nind, int ns, int ne){
    if(lazy[nind]){
        st[nind] = (1ll << lazy[nind]);
        if(ns != ne){
            lazy[nind*2+1] =  lazy[nind * 2 + 2] = lazy[nind];
        }
    }
    lazy[nind] = 0;
}

void update(int nind, int ns, int ne){
    push(nind, ns, ne);
    if(ns > qe || ne < qs) return;
    if(qs <= ns && ne  <= qe){
        lazy[nind] = v;
        push(nind, ns, ne);
        return;
    }
    int mid = (ns + ne) / 2;
    update(nind*2+1, ns, mid);
    update(nind*2+2, mid + 1, ne);
    st[nind] = st[nind*2+1] | st[nind*2+2];
}

ll get(int nind, int ns, int ne){
    if(qe < ns || ne < qs){
        return 0;
    }
    push(nind, ns, ne);
    if(qs <= ns && ne <= qe) return st[nind];
    int mid = (ns + ne) / 2;
    return get(nind*2+1, ns, mid) | get(nind*2+2, mid+1, ne);
}


template<int SZ>
struct LazySegTree {
  const ll inf = 1e18;
  ll tree[4 * SZ];
  ll lazy[4 * SZ];

  LazySegTree() {
    for (int i = 0; i < 4 * SZ; i++) {
      tree[i] = -inf;
      lazy[i] = 0;
    }
  }

  void push(int node, int lo, int hi) {
    if (lazy[node]) {
      tree[node] += lazy[node];
      if (lo != hi) {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
      }
    }
    lazy[node] = 0;
  }

  // add delta to each of [L..R]
  void add(int node, int lo, int hi, int L, int R, ll delta) {
    push(node, lo, hi);
    if (hi < L || R < lo) return;
    if (L <= lo && hi <= R) {
      lazy[node] += delta;
      push(node, lo, hi);
      return;
    }
    int mid = (lo + hi) / 2;
    add(2 * node + 1, lo, mid, L, R, delta);
    add(2 * node + 2, mid + 1, hi, L, R, delta);
    tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
  }

  // max on [L..R]
  ll get(int node, int lo, int hi, int L, int R) {
    push(node, lo, hi);
    if (hi < L || R < lo) return -inf;
    if (L <= lo && hi <= R) {
      return tree[node];
    }
    int mid = (lo + hi) / 2;
    return max(get(node, lo, mid, L, R), get(node, mid + 1, hi, L, R));
  }

};

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &c[i]);
    }
    for(int i = 0; i < n-1; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1, 0);
    for(int i = 1; i<=n; i++){
        qs = first[i];
        qe = first[i];
        v = c[i];
        update(0, 1, n);
    }


    while(m--){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int y, z;
            scanf("%d%d", &y, &z);
            qs = first[y];
            qe = last[y];
            v = z;
            update(0, 1, n);
        }
        else{
            int y;
            scanf("%d", &y);
            qs = first[y];
            qe = last[y];
            int ans = __builtin_popcountll(get(0,1,n));
            printf("%d\n", ans);
        }
    }
    return 0;
}

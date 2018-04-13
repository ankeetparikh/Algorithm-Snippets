#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <bitset>
#include <map>
#include <queue>
#include <complex>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
#include <set>
typedef long long ll;
typedef long double ld;

#define pb push_back
#define mp make_pair

using namespace std;

const int N = 10000;
const int inf = 2e9+20;
const int NIL = 0;
vector<int> g[N];
int leftsz; 
int match[N];
int dist[N];
ll a[N], b[N];
ll ans[N];
map<ll, int> loc;
int rptr = 0;
bool bfs(){
	queue<int> qu;
	for(int i=1; i<=leftsz; i++){ // do this for only left nodes
		if(match[i] == NIL){
			dist[i] = 0;
			qu.push(i);
		}
		else{
			dist[i] = inf;
		}
	}
	dist[NIL] = inf;
	while(!qu.empty()){
		int left = qu.front();
		qu.pop();
		if(left != NIL){
			for(int right : g[left]){
				if(dist[match[right]] == inf){
					dist[match[right]] = dist[left] + 1;
					qu.push(match[right]);
				}
			}
		}
	}
	return dist[NIL] != inf;
	
}

bool dfs(int left){
	if(left != NIL ){
		for(int right : g[left]){
			if(dist[match[right]] == dist[left] + 1){
				if(dfs(match[right])){
					match[right] = left;
					match[left] = right;
					return true;
				}
			}
		}
		dist[left] = inf;
		return false;
	}
	return true;
}

void add(ll x){
	if(loc.find(x) == loc.end()){
		loc[x] = rptr++;
		ans[rptr-1] = x;
	}
}

int main(){
	scanf("%d", &leftsz);
	rptr = leftsz+1;
	for(int i=1; i<=leftsz; i++){
		scanf("%d%d", a+i, b+i);
		ll u = a[i] + b[i];
		ll v = a[i] - b[i];
		ll z = a[i] * b[i];
		add(u); add(v); add(z);
		set<int> ss;
		ss.insert(loc[u]);
		ss.insert(loc[v]);
		ss.insert(loc[z]);
		for(auto ind : ss){
			g[i].pb(ind);
			g[ind].pb(i);
		}
	}
	int mts = 0;
	while(bfs()){
		for(int i = 1 ; i <= leftsz; i++){
			if(match[i] == NIL && dfs(i)){
				mts++;
			}
		}
	}
	//cout << mts << endl;
	if(mts != leftsz){
		cout << "impossible\n";
		return 0;
	}
	for(int i=1; i<= leftsz; i++){
		char c = 'x';
		ll sol = ans[match[i]];
		if(sol == a[i]+b[i]) c = '+';
		if(sol == a[i]-b[i]) c = '-';
		if(sol == a[i]*1ll*b[i]) c = '*';
		printf("%d %c %d = %lld\n", a[i], c, b[i], ans[match[i]]);
	}
	return 0;
}



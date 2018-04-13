#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <bitset>
#include <set>
#include <queue>
#include <complex>
#include <functional>

#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

// solution starts here
#define N 100100
#define INF 1e18

int pre[N];
vector<pair<int, int> > g[N];
ll dist[N];

void dijkstra(int source, int sink){
	for(int i=0; i<N; i++) dist[i] = INF;
	
	priority_queue<pair<ll,int> > pq;
	
	pre[source] = source; 
	dist[source] = 0;
	pq.push(mp(0,source));
	
	while(pq.size()){
		int vert = pq.top().second; pq.pop();
		for(pair<int,int>& edge : g [vert]){
			int nei = edge.second;
			ll  w = edge.first;
			ll tent = dist[vert] + w;
			if(dist[nei] > tent){
				dist[nei] = tent;
				pre[nei] = vert;
				pq.push(mp(-dist[nei], nei));
			}
		}
	}
}

int main(){
    
	
    return 0;
}
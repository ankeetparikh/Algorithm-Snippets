#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;

using namespace std;


// 0 will be added "source", N will be "sink"
// so for vertices indexed 1 to 10, make N = 11
template<int N> struct mcf {
	struct edge{
		int from, to;
		ll flow, cap, cost;
	};
	ll inf = 1e18;
	int source = 0, sink = N;			// if there are no demands, set source = 1, sink = N - 1
	ll flow, totcost;
	int pre[N + 1], inqueue[N + 1];
	ll d[N + 1], demand[N + 1];
	vector<edge> edges;
	vector<int> g[N + 1];

	void addEdge(int u, int v, ll cap, ll cost){
		g[u].pb(edges.size());
		edges.pb({u, v, 0, cap, cost});
		g[v].pb(edges.size());
		edges.pb({v, u, 0, 0, -cost});
	}

	void addDemand(int vertex, ll dem){
		demand[vertex] = dem;
	}

	void prepare(){
		for(int i = 1; i < N; i++){
			if(demand[i] > 0) addEdge(0, i,  demand[i], 0);
			if(demand[i] < 0) addEdge(i, N, -demand[i], 0);
		}
	}

	bool spfa(){
		for(int i = 0; i <= N; i++) d[i] = inf, inqueue[i] = 0;
		d[source] = 0;
		priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
		q.push({source,0}); inqueue[source] = 1;
		while(q.size()){
			int u = q.top().s; q.pop();
			inqueue[u] = 0;
			for(int edgeIndex : g[u]){
				edge uv = edges[edgeIndex];
				if(uv.cap == 0) continue;
				int v = uv.to;
				if(d[u] + uv.cost < d[v]){
					pre[v] = edgeIndex;
					d[v] = d[u] + uv.cost;
					if(inqueue[v] == 0){
						q.push({d[v],v});
						inqueue[v] = 1;
					}
				}
			}
		}
		return d[sink] != inf;
	}

	void reduceCost(){
		for(edge ed : edges){
			ed.cap += d[ed.from] - d[ed.to];
		}
	}

	void augment(){
		ll flowDelta = 1e18;
		for(int vertex = sink; vertex != source; vertex = edges[pre[vertex]].from){
			flowDelta = min(flowDelta, edges[pre[vertex]].cap);
		}
		flow += flowDelta;
		for(int vertex = sink; vertex != source; vertex = edges[pre[vertex]].from){
			edges[pre[vertex]].cap -= flowDelta;
			edges[pre[vertex] ^ 1].cap += flowDelta;
			totcost += edges[pre[vertex]].cost * flowDelta;
		}
	}

	pair<ll,ll> mincostflow() {
		prepare();
		flow = totcost = 0;
		
		while(1){
			if(!spfa()) break;
			reduceCost();
			augment();	
		}
		return {flow, totcost};
	}
};

int main(){
	mcf<3> m;
	m.addEdge(1,2,2,-5);
	m.addDemand(1, 2);
	m.addDemand(2, -2);
	pair<ll,ll> z = m.mincostflow();
	cout << z.f << ' ' << z.s << endl;
	return 0;
}
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


// N >= num vertices
template<int N>
struct EulerianPath {
  // graph must be UNDIRECTED and CONNECTED
  // returns eulerian cycle (if it exists)
  // or eulerian path (if it exists)
  // or empty list
  // O(n) time

  /* Psuedocode:
    
    stack St
    put the start vertex in St
    until St is empty
    let V be the vertex on top
    if deg(V) == 0
      add V to the answer
      remove V from the top of St
    else
      find any edge (V, Y)
      remove this edge from the graph
      push Y to the top of St
  */

private:
  struct edge {
    int to, on = 1;
  }
  vector<edge> edges;
  vector<int> g[N];

public:
  // a != b
  void addEdge(int a, int b) {

  }

  vector<int> getPath() {

  }

}

int main() {

  return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;
vector<int> g[N];
int color[N];
int white = 0, grey = 1, black = 2;

// only in DIRECTED GRAPHS!!
bool dfs(int x){
	color[x] = grey;
	for(int y : g[x]){
		if(color[y] == grey) return true;
		if(color[y] == white && dfs(y)) return true;
	}
	color[x] = black;
	return false;
}

int main(){
	//dfs from everywhere	
	return 0;
}

#include <bits/stdc++.h>
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

// test if degree sequence is graphical
// sorting takes O(nlogn) time
// the rest takes O(n) time
// source: http://compalg.inf.elte.hu/~tony/Kutatas/EGHH/Comb-IvanyiLucz-23Nov.pdf
bool isgraphical(vector<int> degs){
	sort(degs.begin(), degs.end());
	reverse(degs.begin(), degs.end());
	int n = degs.size();
	vector<int> b(n + 1, 0);
	vector<ll>  H(n + 1, 0);
	copy(degs.begin(), degs.end(), b.begin() + 1);
	partial_sum(b.begin() + 1, b.end(), H.begin() + 1, [](int x, int y){return (ll)(x + y);});
	if(H[n]&1) return false;
	int w = n;
	for(int i = 1; i <= n; i++){
		while(w > 0 && b[w] < i) w--;
		int y = max(w, i);
		if(H[i] > i * 1ll * (y - 1) + H[n] - H[y]) return false;
	}
	return true;

}

int main(){
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vector<int> d(n);
		for(int & x : d) cin >> x;
		if(isgraphical(d)) cout << "POSSIBLE\n";
		else cout << "IMPOSSIBLE\n";
	}
	return 0;
}
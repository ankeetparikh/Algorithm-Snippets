#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
using namespace std;

const int N = 1e5 + 10;
const int L = 20;

int ans[N];

/////////////////////////////////////////////
char s[N];
int p[L][N], suf[N], lcp[N];
int n;
int lg; // will hold ceil(log2(n));
// n*log(n)*log(n)
// works for any alphabet
// after build(), lg will hold
// the index of the last row of p
// s[0..n-1] = original string
// p[lg][i] = index of s[i..n-1] in the suffix array
// suf[i] = ith suffix in sorted order (this is the suffix array!)

struct suffixarray{
	pair<pair<int, int>, int> t[N]; // temp array

	void order(int j){
		sort(t, t + n);
		for(int i = 0; i < n; i++){
			p[j][t[i].s] = i;
			if(i > 0 && t[i].f == t[i - 1].f){
				p[j][t[i].s] = p[j][t[i - 1].s];
			}
		}
	}
	// assume s has already been constructed
	void build(){
		for(lg = 0; lg == 0 ||1 << (lg - 1) < n; lg++){
			for(int i = 0; i < n; i++){
				if(lg == 0){
					t[i] = {{s[i],-1}, i}; continue;
				}
				int cnt = 1 << (lg - 1);
				t[i] = {{p[lg - 1][i], -1}, i};
				if(i + cnt < n) t[i].f.s = p[lg - 1][i + cnt];
			}
			order(lg);
		}
		lg--;
		for(int i = 0; i < n; i++) suf[p[lg][i]] = i;		
	}
	
	// i and i + 1 in the suffix array
	// therefore lcp[n - 1] is equal to 0 by convention
	void lcp(){
		int k = 0;
		for(int i = 0; i < n; i++){
			if(p[lg][i] == n - 1){
				k = 0; continue;
			}
			int j = suff[p[lg][i] + 1];
			while(i + k < n && j + k < n  && s[i + k] == s[j + k]) k++;
			lcp[p[lg][i]] = k;
			if(k > 0) k--;
		}
	}

	int operator[](int i){
		return suf[i];
	}

	suffixarray(const char* z){
		n = strlen(z);
		for(int i = 0; i < n; i++) s[i] = z[i]; build();
	}
	
	suffixarray(const string z){
		n = z.length();
		for(int i = 0; i < n; i++) s[i] = z[i]; build();
	}
};

/////////////////////////////////////////////


int main(){

	string s; cin >> s;
	suffixarray sa(s);

	for(int i = 0; i < s.length(); i++) printf("%d\n", sa[i]);

	return 0;
}
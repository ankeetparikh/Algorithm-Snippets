#include <bits/stdc++.h>
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;


int main(){
	int t; scanf("%d", &t);
	while(t--){
		int n; scanf("%d", &n);
		multiset<int> low, hi;
		for(int i = 0; i < n; i++){
			int x; scanf("%d", &x);
			hi.insert(x);
			while(hi.size() > low.size() + 1){
				int v = *hi.begin();
				hi.erase(hi.begin());
				low.insert(v);
			}
			if(hi.size() == low.size()){
				printf("%.12LF\n", (ld)(*low.rbegin() + *hi.begin()) / 2.0);
			}
			else{
				printf("%d\n", *hi.begin());
			}
		}
	}
	return 0;
}
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main(){
	vector<int> a = {1, 2, 4, 4, 4};
	set<int> s;
	for(int x : a){
		if(!s.count(x)){
			s.insert(x);
			auto it = s.find(x);
			it++;
			if(it!= s.end()) s.erase(it);
		}
	}
	// s is NOT THE LIS, but s.size() is the length of the LIS
	cout << s.size() << endl;
	return 0;
}

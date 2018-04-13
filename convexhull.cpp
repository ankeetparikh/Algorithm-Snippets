#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>

#define pb push_back
#define mp make_pair
typedef long long ll;
typedef long double ld;
using namespace std;

const ld eps   = 1e-12;
const int MAXN =  500000;
int n; // number of points we are considering

struct point{
	ll x, y;
	point(){}
	point(ll xx, ll yy){x=xx, y=yy;}
	point operator-(const point &b) const{
		return point(x-b.x, y- b.y);
	}
	ll operator^(const point &b) const{
		return x*b.y - y*b.x;
	}
	bool operator<(const point &b) const{
		if(x!=b.x) return x < b.x;
		return y < b.y;
	}
	bool operator==(const point &b) const{
		return x == b.x && y == b.y;
	}
};

vector<point> hull(vector<point> s){
	sort(s.begin(), s.end());
	vector<point> up, dn;
	for(int i=0; i<s.size(); i++){
		while(up.size() > 1 && ((up.back() - up[up.size()-2])^(s[i] - up.back())) > 0){
			up.pop_back();
		}
		up.pb(s[i]);
	}
	
	for(int i = s.size() - 1; i>=0; i--){
		while(dn.size() > 1 && ((dn.back() - dn[dn.size()-2])^(s[i] - dn.back())) > 0){
			dn.pop_back();
		}
		dn.pb(s[i]);
	}
	for(int i=1; i<dn.size() - 1; i++){
		up.pb(dn[i]);
	}
	return up;
}


int main(){
	
	return 0;
}

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
#include <complex>
#include <queue>
#include <stack>


#define mp make_pair
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;




priority_queue<pair<int,int> > pq;
int main(){
	pq.push(mp(0,0));
	pq.push(mp(1,1));
	
	while(pq.size()){
		pair<int, int> x = pq.top(); pq.pop();
		cout << x.first << " " << x.second  << endl;
	}
	
    return 0;
}
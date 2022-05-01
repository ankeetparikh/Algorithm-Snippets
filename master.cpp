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



int main(){
    
	vector<char> a;
	vector<char> b;
	a.push_back('k');
	b.push_back('g');
	a.insert(a.end(), b.begin(), b.end());
	string res(a.begin(), a.end());
	cout << res << endl;
    return 0;
}
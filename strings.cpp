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

// returns vector of tokens of this string
// "hello there" --> {"hello", "there"}
vector<string> tokenize(const string x){
	// tokenize by spaces
	vector<string> ans;
	char *dup = strdup(x.c_str());
	char *tk = strtok(dup, " ");
	while(tk){
		ans.push_back(tk);
		tk = strtok(NULL, " ");
	}
	return ans;
}

vector<string> split(const string x, const char a){
	string u = x;
	for(int i=0; i<u.length(); i++) if(u[i] == a) u[i] = ' ';
	stringstream ss(u);
	vector<string> ans;
	string temp;
	while(ss >> temp) ans.push_back(temp);
	return ans;
	
}

int main(){
	vector<string> res = split("hello:there", ':');
	for(string s: res)
		cout << s <<endl;
	
	return 0;
}

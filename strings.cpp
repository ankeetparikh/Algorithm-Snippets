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

/*
	Returns the lyndon factorization of the string a.
	a = w_1w_2w_3...w_k 
	where each w_i is simple, and w_i >= w_i+1 (lex compare)
	a string is simple if it is STRICTLY smaller than any of
	its nontrivial suffixes (smaller than any cyclic shifts)
	
	the lyndon factorization of a string exists and is unique
	time complexity: O(n)
*/

vector<string> lyndon(string s) {
	vector<string> w;
	int n = s.size();
	int i = 0;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while (i <= k) {
			w.pb(s.substr(i, j - k));
			i += j - k;
		}
	}
	return w;
}

/*
	Returns the edit distance between the two strings.
	Insertions, deletions, and substitutions.
	time complexity: O(a.length() * b.length())
*/
int levenshtein(string a, string b) {
	int n = a.length();
	int m = b.length();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (min(i, j) == 0) dp[i][j] = max(i, j);
			else dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + (a[i - 1] != b[j - 1])));
		}
	}
	return dp[n][m];
}


int main(){
	vector<string> res = split("hello:there", ':');
	for(string s: res)
		cout << s <<endl;
	
	cout << levenshtein("hi", "ho") << endl;
	return 0;
}

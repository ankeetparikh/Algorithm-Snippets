
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

const int MAXN = 1000000;
int n,m; // length of text, length of pattern
char T[MAXN]; //text
char P[MAXN]; //pattern
int  pf[MAXN];

void preffunc(){
	pf[0]=0;
	int k = 0;
	for(int q=1; q<m; q++){
		while(k>0 && P[k] != P[q]) k = pf[k-1];
		if(P[k] == P[q]) k++;
		pf[q] = k;
	}
}

void kmp(){
	preffunc();
	int q=0;
	for(int i=0; i<n; i++){
		while(q>0 && P[q] != T[i]) {
			q = pf[q-1];
		}
		if(P[q] == T[i]) q++;
		if(q==m){
			printf("Pattern found at shift %d.\n", i-m+1);
			q = pf[q-1];
		}
	}
}



int main(){
    return 0;
}














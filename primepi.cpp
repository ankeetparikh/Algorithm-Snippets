#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>

typedef long long ll;

using namespace std;

#define MAX (int)1e7

// only needs to be 2*sqrt(n);


ll V[MAX];

ll primepi(ll n){
		int r = (int)sqrt(n);
        
        int ct = 0;
        
        for(int i=1; i<r+1; i++)
        {
            V[ct++] = n/i;
        }
        
        for(ll i = V[ct-1]-1; i>0; i--)
        {
            V[ct++] = i;
        }
        
        map<ll,ll> S;
        
        for(int i=0; i<r+r; i++)
            S[V[i]] = V[i]-1;
        
        for(ll p = 2; p<r+1; p++)
        {
            if(S[p] > S[p-1])
            {
                ll sp = S[p-1];
                ll p2 = p*p;
                for(int v = 0; v < r+r; v++)
                {
                    if(V[v]<p2) break;
                    S[V[v]] = S[V[v]]- (S[V[v]/p] - sp);
                }
            }
        }
		
        return S[n];
}


int main(){
	cout << primepi(10000000000000L) <<endl;
	return 0;
}
#include <bits/stdc++.h>
#define pb push_back
#define rep(i,a,b) for(int i = a; i < b; i++)
#define per(i,a,b) for(int i = a - 1; i >= b; i--)

typedef long long ll;
typedef long double ld;

using namespace std;

// z[i] = length of longest substring, starting from s[i]
// that is also a prefix of s[0,...,n-1]
// Complexity: O(n)
vector<int> zfunc(string s){
    int n = s.length();
    vector<int> z(n);
    z[0] = n;
    int L = 0, R = 0;
    for(int i = 1; i < n; i++){
        if(i > R){
            L = R = i;
            while(R < n && s[R - L] == s[R]) R++;
            z[i] = R - L;
            R--;
        }
        else{
            k = i - L;
            if(z[k] < R - i + 1) z[i] = z[k];
            else{
                L = i;
                while(R < n && s[R - L] == s[R]) R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
    return z;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);



    return 0;
}
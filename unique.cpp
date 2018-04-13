#include <bits/stdc++.h>
typedef long long ll;    
typedef long double ld;  
#define pb push_back     
using namespace std;



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

   	// resizes to only include unique elements in a vector
   	// in sorted order

   	vector<int> a = {2, 2, 3, 1, 4, 5, 6, 6};

   	sort(a.begin(), a.end());
   	a.resize(unique(a.begin(), a.end()) - a.begin());

   	cout << a.size() << endl;


    return 0;

}

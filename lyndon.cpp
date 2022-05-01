#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

struct Lyndon {

  vector<string> decomp;

  Lyndon() {}

  void decompose(const string &s) {
    decomp.clear();
    int n = s.length();
    int i = 0;
    while (i < n) {
      int k = i, j = i + 1;
      while (j < n && s[k] <= s[j]) {
        if (s[k] < s[j]) {
          k = i;
        } else {
          k++;
        }
        j++;
      }
      while (i <= k) {
        decomp.pb(s.substr(i, j - k));
        i += j - k;
      }
    }
  }
};

int main() {
  Lyndon d;
  d.decompose("bc");
  for (auto str : d.decomp) {
    cout << str << endl;
  }
	return 0;
}
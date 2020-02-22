#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;

const int N = 1e6 + 10;
char s[N];
int z[N];
int n;

vector<int> compute(string s) {
  int n = s.length();
  vector<int> z(n, 0);
  z[0] = n;
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - L], R - i + 1));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      L = i; R = i + z[i]; z[i]++;
    }
  }
  return z;
}

vector<int> z_arr(string s) {
  int n = s.length();
  vector<int> z(n, 0);
  z[0] = n;
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - L], R - i + 1));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      L = i; R = i + z[i]; z[i]++;
    }
  }
  return z;
}

int main() {

	scanf("%s", s);
	n = strlen(s);
	z[0] = n;
	int L = -1, R = -1;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R] == s[R - L]) R++;
			z[i] = R - L;
			R--;
		} else {
			int k = i - L;
			if (z[k] < R - i + 1) {
				z[i] = z[k];
			} else {
				L = i;
				while (R < n && s[R] == s[R - L]) R++;
				z[i] = R - L;
				R--;
			}
		}
	}

	return 0;
}
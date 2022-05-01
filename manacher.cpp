#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;
typedef long double ld;
using namespace std;

template<int N>
struct Manacher {
  char s[N];
  int n;
  
  // values available after compute()
  
  int even[N]; // middle is i - 1 and i
  int odd[N];  // middle is i

  Manacher() {}
  void set(char *a, int _n) {
    n = _n;
    for (int i = 0; i < n; i++) s[i] = a[i];
  }
  void set(string &a) {
    n = a.length();
    for (int i = 0; i < n; i++) s[i] = a[i];
  }
  
  /*
    O(n)
    returns length of longest palindrome
    also computes even[] and odd[]
  */
  int compute() {
    for (int i = 0, L = 0, R = -1; i < n; i++) {
      int k = (i > R) ? 1 : min(odd[L + R - i], R - i + 1);
      while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        ++k;
      odd[i] = k--;
      if (i + k > R) {
        R = i + k;
        L = i - k;
      }
    }

    for (int i = 0, L = 0, R = -1; i < n; i++) {
      int k = (i > R) ? 0 : min(even[L + R - i + 1], R - i + 1);
      while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        k++;
      even[i] = k--;
      if (i + k > R) {
        R = i + k;
        L = i - k - 1;
      }
    }

    return max(
      (*max_element(odd, odd + n)) * 2 - 1, 
      (*max_element(even + 1, even + n)) * 2
    );
  }
};

const int N = 1e6 + 10;
Manacher<N> m;

int main() {
  scanf("%s", m.s);
  m.n = strlen(m.s);
  int len = m.compute();
  for (int i = 0; i < m.n; i++) {
    if (m.odd[i] * 2 - 1 == len) {
      for (int j = i - m.odd[i] + 1; j < i + m.odd[i]; j++) {
        printf("%c", m.s[j]);
      }
      return 0;
    }
    if (i > 0 && m.even[i] * 2 == len) {
      for (int j = i - m.even[i]; j < i + m.even[i]; j++) {
        printf("%c", m.s[j]);
      }
      return 0;
    }
  }

  return 0;
}
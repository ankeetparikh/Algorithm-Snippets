#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;
typedef long double ld;
using namespace std;

template<int N>
struct Palindromic {
  // palindromic tree
  // O(n)
  struct node {
    map<char, int> children;
    int suffix_link = 0;
    node() {}
    node(int _s) {
      suffix_link = _s;
    }
  };

  char s[N];
  node nodes[N];
  int n, avail, cur;
  int imag = 0, real = 1;

  Palindromic() {init();}

  void init() {
    fill(s, s + N, 0);
    nodes[imag] = node(imag); // len = -1 (imaginary)
    nodes[real] = node(imag); // len = 0
    n = 0;
    avail = 2;
    cur = 0;
  }

  void add_char(char ch) {
    s[n++] = ch;
    
  }

  void build_from(const string &a) {
    for (char ch : a) 
      add_char(ch);
  }

  void build_from(int *a, int n) {
    for (int i = 0; i < n; i++) {
      add_char(a[i]);
    }
  }

};

Palindromic<100> p;

int main() {
  cout << p.ptr << endl;
  return 0;
}
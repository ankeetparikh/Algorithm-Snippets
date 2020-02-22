#include<bits/stdc++.h>
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 20;

/*
  Computes the zeta transform of a, stores in f.
  f[S] = sum of a[X] where X is a subset of S
  Complexity: O(N * 2 ^ N)
*/
void zeta(int a[1 << N], int f[1 << N]) {
  for (int i = 0; i < (1 << N); i++) {
    f[i] = a[i];
  }
  for (int k = 0; k < N; k++) {
    for (int mask = 0; mask < (1 << N); mask++) {
      if (mask >> k & 1) {
        f[mask] += f[mask ^ (1 << k)];
      }
    }
  }
}

/*
  Computes the mobius transform of a and stores in f.
  a[S] = sum of f[X] where X is a subset of S
  (Note: a is the INPUT and f is the OUTPUT)
  Complexity: O(N * 2 ^ N)
  Note: The mobius transform inverses the zeta transform.
*/

void mobius(int a[1 << N], int f[1 << N]) {
  for (int i = 0; i < (1 << N); i++) {
    f[i] = a[i];
  }
  for (int k = 0; k < N; k++) {
    for (int mask = 0; mask < (1 << N); mask++) {
      if (mask >> k & 1) {
        f[mask] -= f[mask ^ (1 << k)];
      }
    }
  }
}

// In case you forget :)
void zeta_inv(int a[1 << N], int f[1 << N]) {
  mobius(a, f);
}

void mobius_inv(int a[1 << N], int f[1 << N]) {
  zeta(a, f);
}

/*
  Computes the subset convolution of a and b and stores in f.
  f[S] = sum of a[T] * b[S\T] where T is a subset of S
  Complexity:
*/

void subset_conv(int a[1 << N], int b[1 << N], int f[1 << N]) {

}

int a[1 << N];

int main(){
  a[0] = 1; a[1] = 2; a[2] = 3;
  zeta(a, a);
  mobius(a, a);
  for (int i = 0; i < 3; i++) {
    cout << a[i] << endl;
  }
	return 0;
}
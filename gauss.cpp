#include <bits/stdc++.h>
#define pb push_back
typedef long double ld;
using namespace std;

const int MAXN = 256;
const int INF  = 1e9;
const ld eps   = 1e-9;

// here, A is the augmented matrix
// if we wanted to solve A'x = b, then 
// A = [A' b]
// so A is n x (n + 1)
 
int gauss(vector<vector<ld>> A, vector<ld> &x){
	int n = A.size();
	int m = A[0].size() - 1;
	vector<int> loc(m, -1);
	for(int row = 0, col = 0; row < n; col < m; col++){
		int sel = row;
		for(int j = row; j < n; j++){
			if(fabs(A[j][col]) > fabs(A[sel][col])) sel = j;
		}
		if(fabs(A[sel][col]) < eps) continue;
		loc[col] = row;
		for(int j = 0; j <= m; j++) swap(A[row][j], A[sel][j]);
		for(int i = 0; i < n; i++){
			if(i == row) continue;
			ld ratio = A[i][col] / A[row][col];
			for(int j = 0; j <= m; j++){
				A[i][j] -= A[row][j] * ratio;
			}
		}
		row++;
	}
	x.assign(m, 0);
	for(int j = 0; j < m; j++){
		if(where[j] != -1){
			x[j] = a[where[j]][m] / a[where[j]][j];
		}
	}
	//check
	for(int i = 0; i < n; i++){
		ld sum = 0;
		for(int j = 0; j < m; j++){
			sum += a[i][j] * x[j];
		}
		if(fabs(sum - a[i][m]) > eps){
			return 0;
		}
	}
	for(int j = 0; j < m; j++){
		if(where[j] == -1){
			return INF;
		}
	}
	return 1;
}

// here, A is the augmented matrix
// if we wanted to solve A'x = b, then 
// A = [A' b]
// so A is n x (n + 1)
int gaussmod2(int n, int A[MAXN][MAXN], int x[MAXN]){
	return 0;
}

int main(){
	gauss(0,0,NULL, NULL);
	return 0;
}
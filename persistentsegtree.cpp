#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct node{
	node* l;
	node* r;
	int val;
	node(): l(NULL), r(NULL), val(0){}
	node(int x): l(NULL), r(NULL), val(x){}
	node(node* lc, node* rc, int x): l(lc), r(rc), val(x){};
};

const int N = 1e5 + 10;

int arr[N];
node* version[N];

//construct version 0
void build(node* n, int low, int hi){
	if(low == hi){
		n->val = arr[low];
		return;
	}
	int mid = (low + hi) / 2;
	n->l = new node(NULL, NULL, 0);
	n->r = new node(NULL, NULL, 0);
	build(n->l, low, mid);
	build(n->r, mid + 1, hi);
	n->val = n->l->val + n->r->val;
}

// point update
void upgrade(node* prev, node* curr, int low, int hi, int ind, int val){
	if(ind < low || ind > hi || low > hi){
		return;
	}
	if(low == hi){
		curr->val = val;
		return;
	}
	int mid = (low + hi) / 2;
	if(ind <= mid){
		curr->l = new node(NULL, NULL, 0);
		curr->r = prev->r;
		upgrade(prev->l, curr->l, low, mid, ind, val);
	}
	else{
		curr->l = prev->r;
		curr->r = new node(NULL, NULL, 0);
		upgrade(prev->r, curr->r, mid + 1, hi , ind, val);
	}


	curr->val = curr->l->val + curr->r->val;

}

//this example is for range sum query
int query(node* n, int low, int hi, int ql, int qr){
	if(ql > hi || qr < low || low > hi) return 0;
	if(ql <= low && hi <= qr) return n->val;
	int mid = (low + hi) / 2;
	return query(n->l, low, mid, ql, qr) + query(n->r, mid+1, hi, ql, qr);
}

int main(){

	int a[5] = {1, 2, 3, 4, 5};
	int n = sizeof(a) / sizeof(a[0]);
	
	for(int i = 0; i < n; i++) arr[i] = a[i];

	version[0] = new node(NULL, NULL, 0);
	build(version[0], 0, n - 1);

	return 0;
}
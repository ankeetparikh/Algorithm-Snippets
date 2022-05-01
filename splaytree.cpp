#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;

/*
	Left Rotate (x) :
		p              x
	   / \            / \
	  x   c   =>     a   p
	 / \                / \
	a   b              b   c

	Right Rotate (x) :
		p              x
	   / \            / \
	  a   x   =>     p   c
	     / \        / \
	    b   c      a   b
*/

template<class T>
struct SplayTree {
	struct node {
		node *parent, *left, *right;
		T key;
		node() {
			left = right = parent = nullptr;
		}
		node(T k) {
			key = k; left = right = parent = nullptr;
		}
		~node() {}
	};
	node *root;
	int size;

	SplayTree() {
		root = nullptr;
		size = 0;
	}

	SplayTree(node* tree) {
		root = tree;
		size = 0;
	}

private:
	bool isLeftChild(node* x, node* p) {
		assert(x != nullptr && p != nullptr);
		return p->left == x;
	}

	bool isRightChild(node* x, node* p) {
		assert(x != nullptr && p != nullptr);
		return p->right = x;
	}

	void leftRotate(node* x) {
		if (!x) return;
		node *p = x->parent;
		if (!p) return;
		node *g = p->parent;
		if (g) {
			if (isLeftChild(p, g)) g->left = x;
			else g->right = x;
		}
		if (x->right) x->right->parent = p;
		p->left = x->right;
		x->parent = g;
		p->parent = x;
		x->right = p;
	}

	void rightRotate(node* x) {
		if (!x) return;
		node *p = x->parent;
		if (!p) return;
		node *g = p->parent;
		if (g) {
			if (isRightChild(p, g)) g->right = x;
			else g->left = x;
		}
		if (x->left) x->left->parent = p;
		p->right = x->left;
		x->parent = g;
		p->parent = x;
		x->left = p;
	}

	void splay(node *x) {
		if (!x) return;
		while (x->parent) {
			node *p = x->parent;
			if (!p->parent) {
				if (isLeftChild(x, p)) { 
					leftRotate(x);
				} else {
					rightRotate(x); 
				}
			} else if (p->parent->left == p && p->left == x) { 
				leftRotate(x);
				leftRotate(x);
			} else if (p->parent->left == p && p->right == x) {
				rightRotate(x);
				leftRotate(x);
			} else if (p->parent->right == p && p->left == x) {
				leftRotate(x);
				rightRotate(x);
			} else {
				rightRotate(x);
				rightRotate(x);
			}
		}
	}
public:

	void inOrder(node *x) {
		if(!x) return;
		inOrder(x->left);
		cout << x->key << endl;
		inOrder(x->right);
	}

	node* find(const T& key) {
		node* ptr = root;
		while (ptr) {
			if (key < ptr->key) ptr = ptr->left;
			else if (key > ptr->key) ptr = ptr->right;
			else return ptr;
		}
		return nullptr;
	}

	node* findMax(node* root) {
		node *ptr = root;
		while (ptr) ptr = ptr->right;
		return ptr;
	}

	node* findMin(node* root) {
		node *ptr = root;
		while (ptr) ptr = ptr->left;
		return ptr;
	}

	// ensure that a and b are the roots of their
	// respective trees
	node* join(node* a, node* b) {

		if (!a) return b;
		if (!b) return a;

		a->parent = nullptr;
		b->parent = nullptr;

		node* amax = findMax(a);

		splay(amax);
		amax->right = b;
		return amax;
	}

	void insert(const T& key) {
		node *ptr = root, *p = nullptr;
		while (ptr) {
			p = ptr;
			if (key <= ptr->key) ptr = ptr->left;
			else ptr = ptr->right;
		}
		node *toAdd = new node(key);
		if (!p) {
			root = toAdd;
		} else {
			if (key <= p->key) p->left = toAdd;
			else p->right = toAdd;
		}
		splay(toAdd);
		size++;
	}

	// if multiple, an arbitrary one is deleted
	bool erase(const T& key) {
		node *ptr = find(key);
		if (!ptr) return false;
		cout << "hi " << findMax(ptr)->key << endl;
		splay(ptr);

		node* left = ptr->left;
		node* right = ptr->right;


		delete ptr;

		if (left) left->parent = nullptr;
		if (right) right->parent = nullptr;

		root = join(left, right);
		
		size--;
		return true;
	}
};

int main() {

	SplayTree<int> t;
	for (int i = 5; i >= 1; i--) t.insert(i);
	t.inOrder(t.root);
	t.erase(3);
	t.inOrder(t.root);
	return 0;
}
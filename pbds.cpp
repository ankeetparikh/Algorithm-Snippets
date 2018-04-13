// NOTE TO SELF: this will not compile on your computer (ext cannot be found for some reason)
// perhaps try to fix in the future

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main(){
	Tree<int> x;
	x.insert(1);
	x.insert(2);

	cout << x.find_by_order(1) << endl;

	return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define endl '\n'

namespace print {
	template<class T> 
	void pr(T a) {
		cout << a;
	}

	template<class T>
	void pr(vector<T> v) {
		for (T x : v) {
			pr(x); pr(" ");
		}
		pr(endl);
	}

	template<class A, class B>
	void pr(pair<A, B> p) {
		pr(p.f); pr(" "); pr(p.s); pr(endl);
	}

	template<class A, class... Args>
	void pr(A arg, Args... args) {
		cout << "in variadic " << arg << " " << sizeof...(args) << endl << flush;
		pr(arg);
		pr(args...);
	}
};

using namespace print;

int main() {

	pr(4);
	vector<int> a = {1, 2, 3};
	pr(a);
	pr(1, 2);

	return 0;
}
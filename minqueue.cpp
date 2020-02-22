#include <bits/stdc++.h>
#define pb push_back

typedef long long ll;
typedef long double ld;

using namespace std;

/*
	normal queue with the following operations:
	s.min()
	s.push(int x)
	s.pop()
	s.front()
	s.back()
	s.empty()
	s.size()
*/

struct min_queue{
	vector<pair<ll, ll>> a, b;

	int size(){
		return a.size() + b.size();
	}

	bool empty(){
		return a.empty() && b.empty();
	}

	void clear(){
		a.clear(); b.clear();
	}

	ll min_element() const {
		ll v = 3e18;
		if(b.size()) v = min(v, b.back().second);
		if(a.size()) v = min(v, a.back().second);
		return v;
	}

	void push(ll x){
		a.push_back({x, a.empty() ? x : min(x, a.back().second)});
	}

	void pop(){
		if(empty()) return;
		if(b.empty()) transfer();
		b.pop_back();
	}

	int front(){
		if(b.empty()) transfer();
		return b.back().first;
	}

	int back(){
		return a.size() ? a.back().first : b.front().first;
	} 

	void transfer(){
		if(!b.empty()) return;
		while(!a.empty()){
			ll x = a.back().first; 
			a.pop_back();
			b.push_back({x, b.empty() ? x : min(x, b.back().second)});
		}
	}
};


struct max_queue{
	vector<pair<ll, ll>> a, b;

	int size(){
		return a.size() + b.size();
	}

	bool empty(){
		return a.empty() && b.empty();
	}

	void clear(){
		a.clear(); b.clear();
	}

	ll max_element() {
		ll v = -3e18;
		if(b.size()) v = max(v, b.back().second);
		if(a.size()) v = max(v, a.back().second);
		return v;
	}

	void push(ll x){
		a.push_back({x, a.empty() ? x : max(x, a.back().second)});
	}
	
	void pop(){
		if(empty()) return;
		if(b.empty()) transfer();
		b.pop_back();
	}

	int front(){
		if(b.empty()) transfer();
		return b.back().first;
	}

	int back(){
		return a.size() ? a.back().first : b.front().first;
	}

	void transfer(){
		if(!b.empty()) return;
		while(!a.empty()){
			ll x = a.back().first; 
			a.pop_back();
			b.push_back({x, b.empty() ? x : max(x, b.back().second)});
		}
	}
};

int main(){
	min_queue m;
	m.push(1); m.push(2); m.push(3);
	m.pop();
	cout << m.min_element() << endl;
	m.pop();
	cout << m.min_element() << endl;
}

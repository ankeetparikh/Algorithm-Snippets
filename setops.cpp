#include <iostream>
#include <set>

using namespace std;



void add(multiset<int> myset, int x){
	myset.insert(x);
}

void remove(multiset<int> myset, int x){
	// remove one occurrence
	auto it = myset.find(x);
	if(it != myset.end())
		myset.erase(it);
}

void removemin(multiset<int> myset){
	myset.erase(myset.begin());
}

void removemax(multiset<int> myset){
	myset.erase(myset.find(*myset.rbegin()));
}

int main(){
	return 0;
}
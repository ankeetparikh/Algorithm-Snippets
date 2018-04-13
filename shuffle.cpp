#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

int main(){
	vector<int> a = {1,2,3,4,5,6};
	
    shuffle (a.begin(), a.end(), default_random_engine(time(0)));
    
	for(int i=0; i<a.size(); i++) cout << a[i] << " ";
	cout << endl;
	return 0;
}
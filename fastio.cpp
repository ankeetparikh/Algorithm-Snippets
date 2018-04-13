#include <bits/stdc++.h>
using namespace std;

// works for int/ll/short
template <class _T> inline void rd(_T &_a) {
	int _f=0,_ch=getchar();_a=0;
	while(_ch<'0' || _ch>'9'){if(_ch=='-')_f=1;_ch=getchar();}
	while(_ch>='0' && _ch<='9')_a=(_a<<1)+(_a<<3)+_ch-'0',_ch=getchar();
	if(_f)_a=-_a;
}
int main(){

	return 0;
}
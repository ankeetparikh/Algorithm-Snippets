#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<set>
#include<complex>
#include<bitset>
#include<cstring>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;
typedef long long ll;
typedef long double ld;

ld eps = 1e-12;
bool eq(ld a, ld b){
	return fabs(b-a) < eps;
}

template<typename T>
struct point {
  T x, y;
  point(){}
  point(T xx, T yy){x = xx, y = yy;}
  point operator+(point b) {
    return point(x + b.x, y + b.y);
  }
  point operator-(point b) {
    return point(x - b.x, y - b.y);
  }
  friend point operator*(T s, point a) {
    return point(a.x * s, a.y * s);
  }
  T operator^(point b) {
    return x * b.y - y * b.x;
  }
  bool operator<(const point b) const{
    if(x!=b.x) return x < b.x;
    return y < b.y;
  }
  bool operator==(const point &b) const{
    return x == b.x && y == b.y;
  }
};

{
    pointR get_intersection(pointR a, pointR b, pointR c, pointR d) {
      // doesn't check edge cases when line segments don't intersect
      pointR r = b - a;
      pointR s = d - c;

      auto t = ((c - a) ^ s) / (r ^ s);

      return a + (t * r);
    }

}

// don't use this one, use the one above and specify the generic type (rat is in the fraction.cpp class if needed)
struct point{
	ll x=0, y=0;
	point(){x = 0; y = 0;}
	point(ll xx, ll yy){ x = xx; y = yy;}
	point operator+(point b){ return point(x+b.x, y+b.y);}
	point operator-(point b){ return point(x-b.x, y-b.y);}
	ll operator*(point b){ return x*b.x + y*b.y;}
	ll operator^(point b){ return x*b.y - y*b.x;}
};
struct pointd{
	ld x, y;
	pointd(){x = 0; y = 0;}
	pointd(ld xx, ld yy){ x = xx; y = yy; };
	pointd(point a){ x = a.x; y = a.y};
	pointd operator+(pointd b){ return pointd(x+b.x, y+b.y);}
	pointd operator-(pointd b){ return pointd(x-b.x, y-b.y);}
	pointd operator/(ld s){return pointd(x/s, y/s);}
	ld operator*(pointd b){ return x*b.x + y*b.y;}
	pointd operator*(ld s){return pointd(x * s, y * s);}
	ld operator^(pointd b){ return x*b.y - y*b.x;}
	bool operator==(const pointd b) const{return eq(this->x, b.x) && eq(this->y, b.y);}
	bool operator<(const pointd b) const {return !(*this == b) && (this->x < b.x || (eq(this->x, b.x) && this->y < b.y));}
	ld norm(){return sqrt(x * x + y * y);}
};
struct line{
	ll a, b, c;
	line(ll aa, ll bb, ll cc){
		a = aa; b = bb; c = cc;
	}
	line(point u, point v){
		a = v.y - u.y;
		b = u.x - v.x;
		c = -a * u.x - b * u.y;
	}
	ll operator()(point p){
		return a * p.x + b * p.y + c;
	}
};

pointd cross(line u, line v){
	ld z  = u.a * v.b - u.b * v.a ;
	ld zx = u.c * v.b - u.b * v.c ;
	ld zy = u.a * v.c - u.c * v.a ;
	pointd ans(-zx/z, -zy/z);
	return ans;
};

ld area_tri(pointd a, pointd b, pointd c){
	return 0.5*abs(a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));
}

// returns 0 points if no intersection
// returns 1 point if tangent
// 2 points if nonempty intersection
vector<pointd> CircleCircleIntersection(pointd a, int r1, pointd b, int r2){
	ld d = dist(a, b);
	if(eq(d, r1 + r2)){
		pointd z = b - a;
		z = z / norm(z) * r1 + a;
		return {z};
	}
	if(eq(r1, d + r2)){
		pointd z = (b - a);
		z = z * (r1 / d);
		return {a + z};
	}
	if(eq(r2, r1 + d)){
		pointd z = (a - b);
		z = z * (r2 / d);
		return {b + z};
	}
	if(d > r1 + r2) return {};
	if(r1 > r2 + d || r2 > r1 + d) return {};

	ld l = (r2 * r2 - r1*r1 + distsq(a, b)) / (2 * d);
	ld h = sqrt(r2 * r2 - l * l);
	
	pointd z = a - b; // vector from b to a
	z = z / norm(z);
	pointd zz(-z.y, z.x);
	pointd A = b + z * l + zz * h;
	pointd B = b + z * l - zz * h;
	return {A, B};
}


int main(){

	return 0;
}

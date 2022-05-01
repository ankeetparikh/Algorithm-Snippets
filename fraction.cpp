#include <iostream>
typedef long long ll;

using namespace std;

template<typename T>
T gcd(T a, T b) {
  return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
struct rat {
  T a, b;
  rat() {a = 0, b = 1;}
  rat(T aa) {
    a = aa;
    b = 1;
  }
  rat(T aa, T bb) {
    a = aa;
    b = bb;
    assert(b != 0);
    if (b < 0) {
      b = -b;
      a = -a;
    }
    T g = gcd(a, b);
    a /= g;
    b /= g;
  }

  rat operator+(const rat& y) const {
    T g = gcd(b, y.b);
    return rat(a * (y.b / g) + (b / g) * y.a, b / g * y.b);
  }

  rat operator-(const rat& y) const {
    T g = gcd(b, y.b);
    return rat(a * (y.b / g) - (b / g) * y.a, b / g * y.b);
  }

  rat operator*(const rat& y) const {
    return rat(a * y.a, b * y.b);
  }

  rat operator/(const rat& y) const {
    assert(y.a != 0);
    return rat(a * y.b, b * y.a);
  }

  friend rat operator/(const ll z, const rat& y) {
    return rat(z * y.b, y.a);
  }

  bool operator<(const rat y) const {
    return a * y.b - b * y.a < 0;
  }
  bool operator>(const rat y) const {
    return a * y.b - b * y.a > 0;
  }
  bool operator!=(const rat y) const {
    return a != y.a || b != y.b;
  }
  bool operator==(const rat y) const {
    return a == y.a && b == y.b;
  }
  friend ostream& operator<<(ostream& os, const rat &x) {
    os << x.a << "/" << x.b << " ";
    return os;
  }
};


class Fraction{
	private:
		int num, den;
	public:
		Fraction(int n, int d){
			num = n;
			den = d;
			reduce();
		}
		friend Fraction operator+(const Fraction& a, const Fraction& b){
			Fraction sum(a.num*b.den + b.num*a.den, a.den*b.den);
			return sum;
		}
		friend Fraction operator-(const Fraction& a, const Fraction& b){
			Fraction diff(a.num*b.den - b.num*a.den, a.den*b.den);
			return diff;
		}
		friend Fraction operator*(const Fraction& a, const Fraction& b){
			Fraction prod(a.num*b.num, a.den*b.den);
			return prod;
		}
		friend Fraction operator/(const Fraction& a, const Fraction& b){
			Fraction quot(a.num*b.den, a.den*b.num);
			return quot;
		}
		void reduce(){
			int g = gcd(num,den);
			num/=g;
			den/=g;
		}
		int gcd(int a, int b){
			return b  == 0? a : gcd(b, a%b);
		}
		void print(){
			printf("%d/%d\n", num, den);
		}
};


int main(){
	Fraction f1(1,4);
	Fraction f2(1,4);
	Fraction f3 = f1 / f2;
	f3.print();
	return 0;
}
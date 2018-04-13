#include <iostream>

using namespace std;

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
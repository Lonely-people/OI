#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 1e7 + 10;
const double Pi = acos(-1.0);

struct Complex {
	double x, y;
	Complex(double xx = 0, double yy = 0) {
		x = xx, y = yy;
	}
}a[MAXN], b[MAXN];

Complex operator + (Complex x, Complex y) {
	return Complex(x.x + y.x, x.y + y.y);
}

Complex operator - (Complex x, Complex y) {
	return Complex(x.x - y.x, x.y - y.y);
}

Complex operator * (Complex x, Complex y) {
	return Complex(x.x * y.x - x.y * y.y, x.y * y.x + x.x * y.y);
}

int n, m, l, limit = 1;
int r[MAXN];

inline void fft(Complex * a, int type) {
	for(register int i = 0; i < limit; ++i)
	    if(i < r[i]) swap(a[i], a[r[i]]);
	for(register int Mid = 1; Mid < limit; Mid <<= 1) {
		Complex Wn(cos(Pi / Mid), type * sin(Pi / Mid));
		for(register int R = Mid << 1, j = 0; j < limit; j += R) {
			Complex w(1, 0);
			for(register int k = 0; k < Mid; ++k, w = w * Wn) {
				Complex x = a[j + k], y = w * a[j + Mid + k];
				a[j + k] = x + y, a[j + Mid + k] = x - y;
			}
		}
	}
}

inline int read() {
	register int x = 0, ch = getchar(), f = 1;
	while(!isdigit(ch)) {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

int main() {
	n = read(), m = read();
	for(register int i = 0; i <= n; ++i) {
		int val = read();
		a[i].x = val;
	}
	for(register int i = 0; i <= m; ++i) {
		int val = read();
		b[i].x = val;
	}
	while(limit <= n + m) limit <<= 1, ++l;
	for(register int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	fft(a, 1), fft(b, 1);
	for(register int i = 0; i <= limit; ++i) a[i] = a[i] * b[i];
	fft(a, -1);
	for(register int i = 0; i <= n + m; ++i) printf("%d ", (int) (a[i].x / limit + 0.5));
	return 0;
}

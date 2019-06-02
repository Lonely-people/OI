#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#define ll long long
#define MAXN 100010
#define eps 1e-6

using namespace std;

int n, k;

struct Item {
	int a, b;
	double f;
	bool operator < (const Item & rhs) const {
		return f > rhs.f;
	}
} a[MAXN];

double check(double x) {
	for(register int i = 1; i <= n; ++i) a[i].f = a[i].a - a[i].b * x;
	nth_element(a + 1, a + k + 1, a + n + 1);
	ll sa = 0, sb = 0;
	for(register int i = 1; i <= k; ++i) sa += a[i].a, sb += a[i].b;
	return (double) sa / sb;
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
	n = read(), k = read();
	for(register int i = 1; i <= n; ++i) a[i].a = read();
	for(register int i = 1; i <= n; ++i) a[i].b = read();
	ll sa = 0, sb = 0;
	for(register int i = 1; i <= k; ++i) sa += a[i].a, sb += a[i].b;
	double ans = (double) sa / sb, last;
	do ans = check(last = ans);
	while(ans - last > eps);
	printf("%.4lf\n", ans);
	return 0;
}

#include <iostream>
#include <stdio.h>
#include <algorithm>
#define int long long

using namespace std;

const int MAXN = 1e6 + 10;
const int p = 998244353;

int n, m, r[MAXN], a[MAXN], b[MAXN], Wn[MAXN];

int qpow(int a, int b, int MOD = p) {
	int base = 1;
	while(b) {
		if(b & 1) base = (base * a) % MOD;
		b >>= 1, a = (a * a) % MOD;
	}
	return base;
}

inline void NTT(int * a, int len, int o) {
	for(register int i = 0, j = 0; i < len; ++i) {
		if(i > j) swap(a[i], a[j]);
		for(register int l = len >> 1; (j ^= l) < l; l >>= 1);
	}
	int cnt = 0;
	for(register int i = 1; i < len; i <<= 1) {
		cnt++;
		for(register int j = 0; j < len; j += i << 1) {
			int w = 1;
			for(register int k = 0; k < i; ++k) {
				int x = a[j + k] % p, y = (w * a[j + k + i]) % p;
				a[j + k] = (x + y) % p, a[j + k + i] = (x - y + p) % p;
				w = (w * Wn[cnt]) % p;
			}
		}
	}
	if(!~ o) {
		reverse(a + 1, a + len);
		int inv = qpow(len, p - 2, p);
		for(register int i = 0; i < len; ++i) a[i] = (a[i] * inv) % p;
	}
}

inline void Inv(int deg, int * a, int * b) {
	static int tmp[MAXN];
	if(deg == 1) b[0] = qpow(a[0], p - 2);
	else {
		Inv((deg + 1) >> 1, a, b);
		int __ = 1;
		while(__ < deg << 1) __ <<= 1;
		copy(a, a + deg, tmp);
		fill(tmp + deg, tmp + __, 0);
		NTT(tmp, __, 1), NTT(b, __, 1);
		for(register int i = 0; i < __; ++i) b[i] = (2 - b[i] * tmp[i] % p + p) % p * b[i] % p;
		NTT(b, __, -1);
		fill(b + deg, b + __, 0);
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

signed main() {
	for(register int i = 0; i <= 20; ++i) Wn[i] = qpow(3, (p - 1) / (1 << i), p);
	n = read();
	for(register int i = 0; i < n; ++i) a[i] = read();
	int limit = 1, l = 0;
	while(limit <= n << 1) limit <<= 1, l++;
	Inv(n, a, b);
	for(register int i = 0; i < n; ++i) printf("%lld ", (b[i] + p) % p);
	return 0;
}

#include <iostream>
#include <stdio.h>
#define ll long long

using namespace std;

const int MAXN = 1e6 + 10;
const int P = 998244353;
const int inv2 = 499122177;
const int G = 332748118;

int r[MAXN], f[MAXN], g[MAXN], A[MAXN], B[MAXN], C[MAXN], D[MAXN];

int Add(int a, int b) {
    return (a += b) >= P ? a - P : a;
}

int qpow(int a, int b) {
    int base = 1;
    while(b) {
        if(b & 1) base = 1ll * base * a % P;
        b >>= 1, a = 1ll * a * a % P;
    }
    return (base + P) % P;
}

inline void NTT(int * a, int n, int o) {
    for(register int i = 0; i < n; ++i)
        if(i < r[i]) swap(a[i], a[r[i]]);
    for(register int Mid = 1; Mid < n; Mid <<= 1) {
        int cnt = qpow(o == 1 ? 3 : G, (P - 1) / (Mid << 1));
        for(register int j = 0; j < n; j += (Mid << 1)) {
            int w = 1;
            for(register int k = 0; k < Mid; ++k, w = 1ll * w * cnt % P) {
                int x = a[j + k], y = 1ll * w * a[j + k + Mid] % P;
                a[j + k] = (x + y) % P, a[j + k + Mid] = (ll) (x - y + P) % P;
            }
        }
    }
    if(o == 1) return;
    int inv = qpow(n, P - 2);
    for(register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * inv % P;
}

inline void Inv(int * a, int * b, int n) {
    b[0] = qpow(a[0], P - 2);
    int len, limit;
    for(len = 1; len < (n << 1); len <<= 1) {
        limit = len << 1;
        for(register int i = 0; i < len; ++i) A[i] = a[i], B[i] = b[i];
        for(register int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? len : 0);
        NTT(A, limit, 1), NTT(B, limit, 1);
        for(register int i = 0; i < limit; ++i) b[i] = ((2ll - 1ll * A[i] * B[i] % P) * B[i] % P + P) % P;
        NTT(b, limit, -1);
        for(register int i = len; i < limit; ++i) b[i] = 0;
    }
    for(register int i = 0; i < len; ++i) A[i] = B[i] = 0;
    for(register int i = n; i < len; ++i) b[i] = 0;
}

inline void Sqrt(int * a, int * b, int n) {
    b[0] = 1;
    int * A = C, * B = D, len, limit;
    for(len = 1; len < (n << 1); len <<= 1) {
        limit = len << 1;
        for(register int i = 0; i < len; ++i) A[i] = a[i];
        Inv(b, B, len);
        for(register int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? len : 0);
        NTT(A, limit, 1), NTT(B, limit, 1);
        for(register int i = 0; i < limit; ++i) A[i] = 1ll * A[i] * B[i] % P;
        NTT(A, limit, -1);
        for(register int i = 0; i < len; ++i) b[i] = 1ll * (b[i] + A[i]) % P * inv2 % P;
        for(register int i = len; i < limit; ++i) b[i] = 0;
    }
    for(register int i = 0; i < len; ++i) A[i] = B[i] = 0;
    for(register int i = n; i < len; ++i) b[i] = 0;
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
    int n = read();
    for(register int i = 0; i < n; ++i) f[i] = read();
    Sqrt(f, g, n);
    for(register int i = 0; i < n; ++i) printf("%d%c", g[i], " \n" [i == n - 1]);
    return 0;
}

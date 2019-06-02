// luogu-judger-enable-o2
#include <iostream>
#include <stdio.h>
#define ll long long
#define MAXN 55

using namespace std;

int n;
ll ans = 0, a[MAXN], p[MAXN << 1];

inline void insert(ll x) {
    for(register int i = 55; i >= 0; i--) {
        if(!(x >> i)) continue;
        if(!p[i]) {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
}

inline ll read() {
    register ll x = 0, ch = getchar(), f = 1;
    while(!isdigit(ch)) {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
    return x * f;
}

int main() {
    n = read();
    for(register int i = 1; i <= n; ++i) insert(a[i] = read());
    for(register int i = 55; i >= 0; i--)
        if((ans ^ p[i]) > ans) ans ^= p[i];
    cout << ans << endl;
    return 0;
}

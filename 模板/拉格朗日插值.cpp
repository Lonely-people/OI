// luogu-judger-enable-o2
#include <iostream>
#include <stdio.h>
#define ll long long
#define MOD 998244353
#define MAXN 2010

using namespace std;

ll x[MAXN], y[MAXN], n, k, ans = 0;

ll quickpow(ll a, ll b, ll n) {
    ll ret = 1;
    while(b) {
        if(b % 2 == 1) ret = ret * a % n;
        a = a * a % n;
        b >>= 1;
    }
    return ret;
}

ll inv(ll x) {
    return quickpow(x, MOD - 2, MOD);
}

int main() {
    cin >> n >> k;
    for(register int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    for(register int i = 1; i <= n; ++i) {
        ll s1 = y[i] % MOD, s2 = 1ll;
        for(register int j = 1; j <= n; ++j)
            if(i != j) s1 = s1 * (k - x[j]) % MOD, s2 = s2 * ((x[i] - x[j]% MOD) % MOD) % MOD;
        ans += s1 * inv(s2) % MOD, ans = (ans + MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}

/*
3 100
1 4
2 9
3 16
*/

/*
10201
*/

/*
3 100
1 1
2 2
3 3
*/

/*
100
*/

#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#define reg register
#define fp(i, a, b) for(reg int i = (a); i <= (b); ++i)
#define fd(i, a, b) for(reg int i = (a); i >= (b); i--)

using namespace std;

const int MAXN = 20010;

int s, t, dis[MAXN], dep[MAXN], n, m, u, v, c;

struct edge {
	edge * next, * rev;
	int to, v;
}pool[MAXN], * pt[MAXN], * p = pool, * cur[MAXN];

inline void add(int a, int b, int c) {
	* (++p) = (edge) { pt[a], p + 1, b, c }, pt[a] = p;
	* (++p) = (edge) { pt[b], p - 1, a, 0 }, pt[b] = p;
}

int maxflow(int u, int val) {
	if(u == t) return val;
	int v = val;
	for(; cur[u]; cur[u] = cur[u] -> next) {
		if(dis[cur[u] -> to] == dis[u] - 1 && cur[u] -> v) {
			int f = maxflow(cur[u] -> to, min(v, cur[u] -> v));
			cur[u] -> v -= f, cur[u] -> rev -> v += f, v -= f;
		    if(!v) return val;
		}
	}
	if(!--dep[dis[u]++]) dis[s] = n + 1;
	++dep[dis[u]], cur[u] = pt[u];
	return val - v;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	fp(i, 1, m) scanf("%d%d%d", &u, &v, &c), add(u, v, c);
	long long ans = 0;
	fp(i, 1, n) cur[i] = pt[i];
	for (dep[0] = n; dis[s] <= n; ans += maxflow(s, 0x3f3f3f3f));
	printf("%lld\n", ans);
	return 0;
}

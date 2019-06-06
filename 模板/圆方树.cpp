#include <bits/stdc++.h>

using namespace std;

#define N 200000
#define INF 0x3f3f3f3f
#define lson (o << 1)
#define rson (o << 1 | 1)
#define mid ((l + r) >> 1)

int n, m, q, tot;
int w[N + 5], dfn_clk, dfn[N + 5], low[N + 5], id[N + 5];
int stk[N + 5], tp;
int sz[N + 5], fa[N + 5], hson[N + 5], rt[N + 5], top[N + 5], d[N + 5];
vector<int> G[N + 5], T[N + 5];
int minv[4 * N + 5];
multiset<int> s[N + 5];

void tarjan(int u) {
    low[u] = dfn[u] = ++dfn_clk;
    stk[++tp] = u;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                ++tot;
                for (int x = 0; x != v; --tp) {
                    x = stk[tp];
                    T[tot].push_back(x);
                    T[x].push_back(tot);
                }
                T[tot].push_back(u);
                T[u].push_back(tot);
            }

        } else
            low[u] = min(low[u], dfn[v]);
    }
}

int minval(int u) {
    if (s[u].size())
        return *s[u].begin();
    else
        return INF;
}

void dfs1(int u, int pa) {
    fa[u] = pa;
    sz[u] = 1;
    d[u] = d[pa] + 1;
    for (int i = 0; i < T[u].size(); ++i) {
        int v = T[u][i];
        if (v == pa)
            continue;
        if (u > n)
            s[u].insert(w[v]);
        dfs1(v, u);
        if (sz[v] > sz[hson[u]])
            hson[u] = v;
        sz[u] += sz[v];
    }
}

void dfs2(int u, int tp) {
    dfn[u] = ++dfn_clk, id[dfn_clk] = u;
    top[u] = tp;
    if (hson[u])
        dfs2(hson[u], tp);
    for (int i = 0; i < T[u].size(); ++i) {
        int v = T[u][i];
        if (v == fa[u] || v == hson[u])
            continue;
        dfs2(v, v);
    }
    rt[u] = dfn_clk;
}

int lca(int x, int y) {
    while (top[x] != top[y]) d[top[x]] > d[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return d[x] < d[y] ? x : y;
}

void pushup(int o) { minv[o] = min(minv[lson], minv[rson]); }

void build(int o, int l, int r) {
    if (l == r) {
        minv[o] = id[l] > n ? minval(id[l]) : INF;
        return;
    }
    build(lson, l, mid), build(rson, mid + 1, r);
    pushup(o);
}

void modify(int o, int l, int r, int x, int k) {
    if (l == r) {
        minv[o] = k;
        return;
    }
    if (x <= mid)
        modify(lson, l, mid, x, k);
    else
        modify(rson, mid + 1, r, x, k);
    pushup(o);
}

int queryMin(int o, int l, int r, int L, int R) {
    if (L <= l && r <= R)
        return minv[o];
    int ret = INF;
    if (L <= mid)
        ret = min(ret, queryMin(lson, l, mid, L, R));
    if (R > mid)
        ret = min(ret, queryMin(rson, mid + 1, r, L, R));
    return ret;
}

int query(int x, int y) {
    int z = lca(x, y), ret = INF;
    while (top[x] != top[z]) ret = min(ret, queryMin(1, 1, tot, dfn[top[x]], dfn[x])), x = fa[top[x]];
    ret = min(ret, queryMin(1, 1, tot, dfn[z], dfn[x]));
    while (top[y] != top[z]) ret = min(ret, queryMin(1, 1, tot, dfn[top[y]], dfn[y])), y = fa[top[y]];
    ret = min(ret, queryMin(1, 1, tot, dfn[z], dfn[y]));
    if (z > n)
        ret = min(ret, w[fa[z]]);
    else
        ret = min(ret, w[z]);
    return ret;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    tot = n;
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y), G[y].push_back(x);
    }
    tarjan(1);
    dfn_clk = 0;
    dfs1(1, 0), dfs2(1, 1);
    build(1, 1, tot);
    char type[2];
    for (int i = 1, x, y; i <= q; ++i) {
        scanf("%s%d%d", type, &x, &y);
        if (type[0] == 'C') {
            if (x != 1) {
                int t = minval(fa[x]);
                s[fa[x]].erase(s[fa[x]].lower_bound(w[x]));
                s[fa[x]].insert(y);
                if (minval(fa[x]) != t)
                    modify(1, 1, tot, dfn[fa[x]], minval(fa[x]));
            }
            w[x] = y;
        } else {
            printf("%d\n", query(x, y));
        }
    }
    return 0;
}

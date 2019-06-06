#include<bits/stdc++.h>
using namespace std;
int read() {
    char cc = getchar(); int cn = 0, flus = 1;
    while (cc < '0' || cc > '9') { if (cc == '-') flus = -flus; cc = getchar(); }
    while (cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
    return cn * flus;
}
const int N = 1e5 + 5;
#define ls node * 2
#define rs node * 2 + 1
#define inf 999999999
struct Mat {
    int m[3][3];
    void init() {
        for (int i = 0; i <= 1; ++i)
            for (int j = 0; j <= 1; ++j)
                m[i][j] = -inf;
    }
}tr[N * 4], Val[N];
struct E {
    int to, next;
}e[N * 2];
struct Tree {
    int size, id, fa, top, son, dep, end;
}t[N * 2];
int n, m, cnt, ldp[N][2], dp[N][2], head[N], a[N], b[N], ctt;
void add(int x, int y) {
    e[++cnt] = (E) { y, head[x] }, head[x] = cnt;
    e[++cnt] = (E) { x, head[y] }, head[y] = cnt;
}
int dfs1(int x, int fa) {
    t[x].dep = t[fa].dep + 1, t[x].size = 1; t[x].fa = fa;
    int tot, maxson = 0;
    for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        t[x].size += (tot = dfs1(v, x));
        if (tot > maxson) maxson = tot, t[x].son = v;
    }
    return t[x].size;
}
void dfs2(int x, int high) {
    t[x].id = ++ctt, b[ctt] = x;
    t[high].end = ctt, t[x].top = high;
    if (!t[x].son) { return; }
    dfs2(t[x].son, high);
    for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == t[x].fa || v == t[x].son) continue;
        dfs2(v, v);
    }
}
void dfs3(int x) {
    ldp[x][1] = a[x];
    for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == t[x].fa || v == t[x].son) continue;
        dfs3(v); ldp[x][0] += max(dp[v][1], dp[v][0]), ldp[x][1] += dp[v][0];
    }
    dp[x][0] += ldp[x][0], dp[x][1] += ldp[x][1];
    if (!t[x].son) return;
    dfs3(t[x].son);
    dp[x][0] += max(dp[t[x].son][1], dp[t[x].son][0]);
    dp[x][1] += dp[t[x].son][0];
}
Mat Mul(Mat a, Mat b) {
    Mat ans; ans.init();
    for (int i = 0; i < 2; ++i)  for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)  ans.m[i][j] = max(ans.m[i][j], a.m[i][k] + b.m[k][j]);
    return ans;
}
void build(int node, int l, int r) {
    if (l == r) {
        Val[b[l]].m[0][0] = ldp[b[l]][0], Val[b[l]].m[1][0] = ldp[b[l]][1];
        Val[b[l]].m[0][1] = ldp[b[l]][0], Val[b[l]].m[1][1] = -inf;
        tr[node] = Val[b[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    tr[node] = Mul(tr[ls], tr[rs]);
}
Mat query(int node, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) return tr[node];
    int mid = (l + r) >> 1;
    if (mid >= qr) return query(ls, l, mid, ql, qr);
    if (mid < ql) return query(rs, mid + 1, r, ql, qr);
    return Mul(query(ls, l, mid, ql, qr), query(rs, mid + 1, r, ql, qr));
}
void update(int node, int l, int r, int wh) {
    if (l == r && l == wh) {
        tr[node] = Val[b[wh]];
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= wh) update(ls, l, mid, wh);
    else update(rs, mid + 1, r, wh);
    tr[node] = Mul(tr[ls], tr[rs]);
}
Mat last, newm, k_ans;
void Change(int u, int w) {
    Val[u].m[1][0] += w - a[u];
    a[u] = w;
    while (u != 0) {
        int now = t[u].top;
        last = query(1, 1, n, t[now].id, t[now].end);
        update(1, 1, n, t[u].id);
        newm = query(1, 1, n, t[now].id, t[now].end);
        u = t[now].fa;
        Val[u].m[0][0] += max(newm.m[0][0], newm.m[1][0]) - max(last.m[0][0], last.m[1][0]);
        Val[u].m[0][1] = Val[u].m[0][0];
        Val[u].m[1][0] += newm.m[0][0] - last.m[0][0];
    }
}
signed main() {
    n = read(), m = read(); int x, y, z;
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i < n; ++i) x = read(), y = read(), add(x, y);
    dfs1(1, 0), dfs2(1, 1), dfs3(1), build(1, 1, n);

    for (int i = 1; i <= m; ++i) {
        x = read(), y = read();
        Change(x, y);
        k_ans = query(1, 1, n, t[1].id, t[1].end);
        printf("%d\n", max(k_ans.m[0][0], k_ans.m[1][0]));
    }
    return 0;
}

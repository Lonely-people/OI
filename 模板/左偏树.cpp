// luogu-judger-enable-o2
#include <cstdio>
#include <iostream>
const int N = 100010;
#define reg register
#define swap _swap
#define ls S[x].Son[0]
#define rs S[x].Son[1]
using namespace std;
struct Tree {
    int dis, val, Son[2], rt;
}S[N];
int n, t;
void _swap(reg int &x, reg int &y) {
    x ^= y ^= x ^= y;
}
inline int Find(reg int x) {
    return S[x].rt == x ? x : S[x].rt = Find(S[x].rt);
}
inline int Merge(reg int x, reg int y) {
    if (!x || !y)
        return x + y;
    if (S[x].val > S[y].val || (S[x].val == S[y].val && x > y))
        swap(x, y);
    rs = Merge(rs, y);
    if (S[ls].dis < S[rs].dis)
        swap(ls, rs);
    S[ls].rt = S[rs].rt = S[x].rt = x, S[x].dis = S[rs].dis + 1;
    return x;
}
inline void Pop(reg int x) {
    S[x].val = -1, S[ls].rt = ls, S[rs].rt = rs, S[x].rt = Merge(ls, rs);
}
int main() {
    scanf("%d%d", &n, &t);
    S[0].dis = -1;
    for (reg int i = 1; i <= n; i++)
        S[i].rt = i, scanf("%d", &S[i].val);
    for (reg int i = 1; i <= t; i++) {
        int x, y, z;
        scanf("%d%d", &x, &y);
        if (x == 1) {
            scanf("%d", &z);
            if (S[y].val == -1 || S[z].val == -1)
                continue;
            int f1 = Find(y), f2 = Find(z);
            if (f1 != f2)
                S[f1].rt = S[f2].rt = Merge(f1, f2);
        }
        else {
            if (S[y].val == -1)
                printf("-1\n");
            else
                printf("%d\n", S[Find(y)].val), Pop(Find(y));
        }
    }
    return 0;
}

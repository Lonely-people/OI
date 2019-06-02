// luogu-judger-enable-o2
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 10010;
struct point {
    double x, y;
} p[MAXN];
int cmp1(const point a, const point b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
double k(point a, point b) { return a.x == b.x ? 1e18 : (b.y - a.y) / (b.x - a.x); }
double dis(point a, point b) {
    double px = b.x - a.x, py = b.y - a.y;
    return sqrt(px * px + py * py);
}
int n, top, st[MAXN];
double ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp1);
    for (int i = 1; i <= n; ++i) {
        while ((top > 1 && k(p[st[top - 1]], p[i]) < k(p[st[top - 1]], p[st[top]]))) --top;
        st[++top] = i;
    }
    for (int i = 2; i <= top; ++i) ans += dis(p[st[i]], p[st[i - 1]]);
    top = 0;
    for (int i = 1; i <= n; ++i) {
        while ((top > 1 && k(p[st[top - 1]], p[i]) > k(p[st[top - 1]], p[st[top]]))) --top;
        st[++top] = i;
    }
    for (int i = 2; i <= top; ++i) ans += dis(p[st[i]], p[st[i - 1]]);
    printf("%.2lf\n", ans);
    return 0;
}

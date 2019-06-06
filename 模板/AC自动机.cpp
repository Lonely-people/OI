#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
struct Tree {
    int fail;
    int vis[26];
    int end;
} AC[100000];
int cnt = 0;
struct Result {
    int num;
    int pos;
} Ans[100000];
bool operator<(Result a, Result b) {
    if (a.num != b.num)
        return a.num > b.num;
    else
        return a.pos < b.pos;
}
string s[100000];
inline void Clean(int x) {
    memset(AC[x].vis, 0, sizeof(AC[x].vis));
    AC[x].fail = 0;
    AC[x].end = 0;
}
inline void Build(string s, int Num) {
    int l = s.length();
    int now = 0;
    for (int i = 0; i < l; ++i) {
        if (AC[now].vis[s[i] - 'a'] == 0) {
            AC[now].vis[s[i] - 'a'] = ++cnt;
            Clean(cnt);
        }
        now = AC[now].vis[s[i] - 'a'];
    }
    AC[now].end = Num;
}
void Get_fail() {
    queue<int> Q;
    for (int i = 0; i < 26; ++i) {
        if (AC[0].vis[i] != 0) {
            AC[AC[0].vis[i]].fail = 0;
            Q.push(AC[0].vis[i]);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 26; ++i) {
            if (AC[u].vis[i] != 0) {
                AC[AC[u].vis[i]].fail = AC[AC[u].fail].vis[i];
                Q.push(AC[u].vis[i]);
            } else
                AC[u].vis[i] = AC[AC[u].fail].vis[i];
        }
    }
}
int AC_Query(string s) {
    int l = s.length();
    int now = 0, ans = 0;
    for (int i = 0; i < l; ++i) {
        now = AC[now].vis[s[i] - 'a'];
        for (int t = now; t; t = AC[t].fail) Ans[AC[t].end].num++;
    }
    return ans;
}
int main() {
    int n;
    while (233) {
        cin >> n;
        if (n == 0)
            break;
        cnt = 0;
        Clean(0);
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            Ans[i].num = 0;
            Ans[i].pos = i;
            Build(s[i], i);
        }
        AC[0].fail = 0;
        Get_fail();
        cin >> s[0];
        AC_Query(s[0]);
        sort(&Ans[1], &Ans[n + 1]);
        cout << Ans[1].num << endl;
        cout << s[Ans[1].pos] << endl;
        for (int i = 2; i <= n; ++i) {
            if (Ans[i].num == Ans[i - 1].num)
                cout << s[Ans[i].pos] << endl;
            else
                break;
        }
    }
    return 0;
}

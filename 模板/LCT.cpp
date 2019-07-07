#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;

int n, m;

struct Node;
Node *null;

struct Node {
    Node *ch[2], *fa;
    int val, sum;
    bool rev;
    Node() {
        ch[0] = ch[1] = fa = null;
        val = sum = rev = 0;
    }
    bool get() {
        return fa->ch[1] == this;
    }
    bool isroot() {
        return fa->ch[0] != this && fa->ch[1] != this;
    }
    void reverse() {
        rev ^= 1, std::swap(ch[0], ch[1]);
    }
    void pushup() {
        sum = ch[0]->sum ^ ch[1]->sum ^ val;
    }
    void pushdown() {
        if (rev) {
            ch[0]->reverse();
            ch[1]->reverse();
            rev = 0;
        }
    }
} *a[N];

struct LCT {
    LCT() {
        null = new Node();
        null->ch[0] = null->ch[1] = null->fa = null;
    }
    void build(int n) {
        for (int i = 1; i <= n; i++) {
            a[i] = new Node();
        }
    }
    void clear(int n) {
        delete null;
        for (int i = 1; i <= n; i++) {
            delete a[i];
        }
    }
    void pushtag(Node *x) {
        if (!x->isroot()) pushtag(x->fa);
        x->pushdown();
    }
    void rotate(Node *x) {
        Node *y = x->fa, *z = y->fa;
        int k = x->get();
        !y->isroot() && (z->ch[y->get()] = x), x->fa = z;
        y->ch[k] = x->ch[!k], x->ch[!k]->fa = y;
        x->ch[!k] = y, y->fa = x;
        y->pushup();
    }
    void splay(Node *x) {
        pushtag(x);
        while (!x->isroot()) {
            Node *y = x->fa;
            if (!y->isroot()) {
                rotate(x->get() == y->get() ? y : x);
            }
            rotate(x);
        }
        x->pushup();
    }
    void access(Node *x) {
        for (Node *y = null; x != null; x = (y = x)->fa) {
            splay(x), x->ch[1] = y, x->pushup();
        }
    }
    void makeroot(Node *x) {
        access(x), splay(x), x->reverse();
    }
    Node *findroot(Node *x) {
        access(x), splay(x);
        x->pushdown();
        while (x->ch[0] != null) {
            (x = x->ch[0])->pushdown();
        }
        return x;
    }
    void split(Node *x, Node *y) {
        makeroot(x), access(y), splay(y);
    }
    void link(Node *x, Node *y) {
        makeroot(x);
        if (findroot(y) != x) x->fa = y;
    }
    void cut(Node *x, Node *y) {
        makeroot(x);
        if (findroot(y) == x && x->fa == y && x->ch[1] == null) {
            x->fa = y->ch[0] = null, y->pushup();
        }
    }
};

int main() {
    scanf("%d%d", &n, &m);
    LCT T;
    T.build(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]->val);
    }
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0) T.split(a[x], a[y]), printf("%d\n", a[y]->sum);
        if (opt == 1) T.link(a[x], a[y]);
        if (opt == 2) T.cut(a[x], a[y]);
        if (opt == 3) T.splay(a[x]), a[x]->val = y;
    }
    T.clear(n);
    return 0;
}

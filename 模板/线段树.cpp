#include <iostream>
#include <stdio.h>
#define MAXN 100010
#define ll long long

using namespace std;

int n, m, p;
ll a[MAXN];

struct Node {
    int l, r;
    ll value, tag1, tag2;//mul, add
    Node * left, * right;
    Node(int l, int r, int v, Node * a, Node * b) : l(l), r(r), value(v), left(a), right(b), tag1(1), tag2(0) {}
} * root;

Node * build(int l, int r) {
    if(l == r) return new Node(l, r, a[l], 0, 0);
    int mid = (l + r) / 2;
    Node * left = build(l, mid), * right = build(mid + 1, r);
    return new Node(l, r, (left -> value + right -> value) % p, left, right);
}

ll Get(Node * cur) {
    return (cur -> value * cur -> tag1 % p + cur -> tag2 * (cur -> r - cur -> l + 1) % p) % p;
}

inline void pushdown(Node * cur) {
    if(cur -> tag1 == 1 && cur -> tag2 == 0) return;
    cur -> value = Get(cur);
    cur -> right -> tag1 = cur -> right -> tag1 * cur -> tag1 % p;
    cur -> right -> tag2 = (cur -> right -> tag2 * cur -> tag1 % p + cur -> tag2) % p;
    cur -> left -> tag1 = cur -> left -> tag1 * cur -> tag1 % p;
    cur -> left -> tag2 = ((cur -> left -> tag2 * cur -> tag1) % p + cur -> tag2) % p;
    cur -> tag1 = 1, cur -> tag2 = 0;
}

ll find(int l, int r, Node * cur) {
    if(l == cur -> l && r == cur -> r) return Get(cur);
    pushdown(cur);
    int mid = (cur -> l + cur -> r) / 2;
    if(r <= mid) return find(l, r, cur -> left);
    if(l > mid) return find(l, r, cur -> right);
    return (find(l, mid, cur -> left) + find(mid + 1, r, cur -> right)) % p;
}

inline void modify_tag1(int l, int r, ll v, Node * cur) {
    if(l == cur -> l && r == cur -> r) {
        cur -> tag1 = cur -> tag1 * v % p;
        cur -> tag2 = cur -> tag2 * v % p;
        return;
    }
    pushdown(cur);
    int mid = (cur -> l + cur -> r) / 2;
    if(r <= mid) modify_tag1(l ,r, v, cur -> left);
    else if(l > mid) modify_tag1(l, r, v, cur -> right);
    else {
        modify_tag1(l, mid, v, cur -> left);
        modify_tag1(mid + 1, r, v, cur -> right);
    }
    cur -> value = (Get(cur -> left) + Get(cur -> right)) % p;
}

inline void modify_tag2(int l, int r, ll v, Node * cur) {
    if(l == cur -> l && r == cur -> r) {
        cur -> tag2 = (cur -> tag2 + v) % p;
        return;
    }
    pushdown(cur);
    int mid = (cur -> l + cur -> r) / 2;
    if(r <= mid) modify_tag2(l, r, v, cur -> left);
    else if(l > mid) modify_tag2(l, r, v, cur -> right);
    else {
        modify_tag2(l, mid, v, cur -> left);
        modify_tag2(mid + 1, r, v, cur -> right);
    }
    cur -> value = (Get(cur -> left) + Get(cur -> right)) % p;
}

int main() {
    cin >> n >> m >> p;
    for(register int i = 1; i <= n; ++i) cin >> a[i];
    root = build(1, n);
    while(m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1) {
            ll v;
            cin >> v;
            modify_tag1(l, r, v, root);
        }
        else if(opt == 2) {
            ll v;
            cin >> v;
            modify_tag2(l, r, v, root);
        }
        else cout << find(l, r, root) << endl;
    }
    return 0;
}

#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Node;

Node * null;

struct Node {
	Node * ch[2], * fa;
	int val, cnt, sz;
	Node(int _val = 0) {
		ch[0] = ch[1] = fa = null, val = _val, cnt = sz = 1;
	}
	bool get() {
		return fa -> ch[1] == this;
	}
	inline void pushup() {
		sz = ch[0] -> sz + ch[1] -> sz + cnt;
	}
};

struct Splay {
	Node * rt;
	Splay() {
		null = new Node();
		null -> ch[0] = null -> ch[1] = null -> fa = null;
		null -> cnt = null -> sz = 0;
		rt = null;
	}
	inline void clear(Node * cur) {
		if(cur == null) return;
		clear(cur -> ch[0]), clear(cur -> ch[1]);
		delete cur;
	}
	inline void rotate(Node * cur) {
		Node * y = cur -> fa, * z = y -> fa;
		int k = cur -> get();
		z -> ch[y -> get()] = cur, cur -> fa = z;
		y -> ch[k] = cur -> ch[!k], cur -> ch[!k] -> fa = y;
		cur -> ch[!k] = y, y -> fa = cur;
		y -> pushup();
	}
	inline void splay(Node * x, Node * g) {
		while(x -> fa != g) {
			Node * y = x -> fa;
			if(y -> fa != g) rotate(x -> get() == y -> get() ? y : x);
			rotate(x);
		}
		x -> pushup();
		if(g == null) rt = x;
	}
	inline void find(int v) {
		if(rt == null) return;
		Node * u = rt;
		while(v != u -> val && u -> ch[v > u -> val] != null) u = u -> ch[v > u -> val];
		splay(u, null);
	}
	int rk(int v) {
		find(v);
		return rt -> ch[0] -> sz;
	}
	Node * kth(int k) {
		k++;
		Node * u = rt;
		while(1) {
			if(k <= u -> ch[0] -> sz) u = u -> ch[0];
			else if(k > u -> ch[0] -> sz + u -> cnt) k -= u -> ch[0] -> sz + u -> cnt, u = u -> ch[1];
			else return u;
		}
	}
	Node * pre(int v) {
		find(v);
		if(rt -> val < v) return rt;
		Node * u = rt -> ch[0];
		while(u -> ch[1] != null) u = u -> ch[1];
		return u;
	}
	Node * suc(int v) {
		find(v);
		if(rt -> val > v) return rt;
		Node * u = rt -> ch[1];
		while(u -> ch[0] != null) u = u -> ch[0];
		return u;
	}
	inline void ins(int v) {
		Node * u = rt, * f = null;
		while(u != null && v != u -> val) f = u, u = u -> ch[v > u -> val];
		if(u != null) u -> cnt++;
		else  {
			u = new Node(v);
			if(f != null) f -> ch[v > f -> val] = u, u -> fa = f;
		}
		splay(u, null);
	}
	inline void del(int v) {
		Node * lst = pre(v), * nxt = suc(v);
		splay(lst, null), splay(nxt, lst);
		Node * u = nxt -> ch[0];
		if(u -> cnt > 1) u -> cnt--, splay(u, null);
		else clear(nxt -> ch[0]), nxt -> ch[0] = null;
	}
} tree;

inline int read() {
	register int x = 0, ch = getchar(), f = 1;
	while(!isdigit(ch)) {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

int main() {
	tree.ins(-INF), tree.ins(INF);
	int m = read();
	while(m--) {
		int opt = read(), x = read();
		if(opt == 1) tree.ins(x);
		else if(opt == 2) tree.del(x);
		else if(opt == 3) printf("%d\n", tree.rk(x));
		else if(opt == 4) printf("%d\n", tree.kth(x) -> val);
		else if(opt == 5) printf("%d\n", tree.pre(x) -> val);
		else if(opt == 6) printf("%d\n", tree.suc(x) -> val);
	}
	return 0;
}

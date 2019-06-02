#include <iostream>
#include <stdio.h>
#define MAXN 100010

using namespace std;

int rt, tot, fa[MAXN], ch[MAXN][2], val[MAXN], cnt[MAXN], sz[MAXN];

struct Splay {
	inline void maintain(int x) {
	    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; 
	}
	bool get(int x) {
		return x == ch[fa[x]][1];
	}
	inline void clear(int x) {
		ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
	}
	inline void rotate(int x) {
		int y = fa[x], z = fa[y], chk = get(x);
		ch[y][chk] = ch[x][chk ^ 1];
		fa[ch[x][chk ^ 1]] = y;
		ch[x][chk ^ 1] = y;
		fa[y] = x, fa[x] = z;
		if(z) ch[z][y == ch[z][1]] = x;
		maintain(x), maintain(y);
	}
	inline void splay(int x) {
		for(register int f = fa[x]; f = fa[x], f; rotate(x))
		    if(fa[f]) rotate(get(x) == get(f) ? f : x);
		rt = x;
	}
	inline void ins(int k) {
		if(!rt) {
			val[++tot] = k;
			cnt[tot]++;
			rt = tot;
			maintain(rt);
			return;
		}
		int cnr = rt, f = 0;
		while(1) {
			if(val[cnr] == k) {
				cnt[cnr]++;
				maintain(cnr), maintain(f);
				splay(cnr);
				break;
			}
			f = cnr, cnr = ch[cnr][val[cnr] < k];
			if(!cnr) {
				val[++tot] = k, cnt[tot]++, fa[tot] = f, ch[f][val[f] < k] = tot;
				maintain(tot), maintain(f);
				splay(tot);
				break;
			}
		}
	}
	int rk(int k) {
		int res = 0, cnr = rt;
		while(1) {
			if(k < val[cnr]) cnr = ch[cnr][0];
			else {
				res += sz[ch[cnr][0]];
				if(k == val[cnr]) {
					splay(cnr);
					return res + 1;
				}
				res += cnt[cnr], cnr = ch[cnr][1];
			}
		}
	}
	int kth(int k) {
		int cnr = rt;
		while(1) {
			if(ch[cnr][0] && k <= sz[ch[cnr][0]]) cnr = ch[cnr][0];
			else {
				k -= cnt[cnr] + sz[ch[cnr][0]];
				if(k <= 0) return val[cnr];
				cnr = ch[cnr][1];
			}
		}
	}
	int pre() {
		int cnr = ch[rt][0];
		while(ch[cnr][1]) cnr = ch[cnr][1];
		return cnr;
	}
	int nxt() {
		int cnr = ch[rt][1];
		while(ch[cnr][0]) cnr = ch[cnr][0];
		return cnr;
	}
	inline void del(int k) {
		rk(k);
		if(cnt[rt] > 1) {
			cnt[rt]--;
			maintain(rt);
			return;
		}
		if(!ch[rt][0] && !ch[rt][1]) {
			clear(rt);
			rt = 0;
			return;
		}
		if(!ch[rt][0]) {
			int cnr = rt;
			rt = ch[rt][1], fa[rt] = 0;
			clear(cnr);
			return;
		}
		if(!ch[rt][1]) {
			int cnr = rt;
			rt = ch[rt][0], fa[rt] = 0;
			clear(cnr);
			return;
		}
		int x = pre(), cnr = rt;
		splay(x);
		fa[ch[cnr][1]] = x, ch[x][1] = ch[cnr][1];
		clear(cnr);
		maintain(rt);
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
	int n = read(), ans;
	while(n--) {
		int opt = read(), x = read();
		if(opt == 1) tree.ins(x);
		else if(opt == 2) tree.del(x);
		else if(opt == 3) printf("%d\n", tree.rk(x));
		else if(opt == 4) printf("%d\n", tree.kth(x));
		else if(opt == 5) tree.ins(x), printf("%d\n", val[tree.pre()]), tree.del(x);
		else tree.ins(x), printf("%d\n", val[tree.nxt()]), tree.del(x);
	}
	return 0;
}

//bzoj2648
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int INF = 1000000000, N = 500005;

int n, m, rot, D;
struct P {
	int d[2], mn[2], mx[2], l, r;
	inline int& operator[] (int x) {
		return d[x];
	}
	inline P(int x = 0, int y = 0) {
		l = r = 0;
		d[0] = x;
		d[1] = y;
	}
} p[N];
inline bool operator < (P a, P b) {
	return a[D] < b[D];
}
inline int dis(P a, P b) {
	return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}
struct kdtree {
	int ans;
	P t[N << 1], T;
	inline void updata(int k) {
		P l = t[t[k].l], r = t[t[k].r];
		for (int i = 0; i < 2; i++) {
			if (t[k].l) {
				t[k].mn[i] = min(t[k].mn[i], l.mn[i]);
				t[k].mx[i] = max(t[k].mx[i], l.mx[i]);
			}
			if (t[k].r) {
				t[k].mn[i] = min(t[k].mn[i], r.mn[i]);
				t[k].mx[i] = max(t[k].mx[i], r.mx[i]);
			}
		}
	}
	int build(int l, int r, int now) {
		D = now;
		int mid = l + r >> 1;
		nth_element(p + l, p + mid, p + r + 1);
		t[mid] = p[mid];
		for (int i = 0; i < 2; i++)
			t[mid].mn[i] = t[mid].mx[i] = t[mid][i];
		if (l < mid) t[mid].l = build(l, mid - 1, !now);
		if (mid < r) t[mid].r = build(mid + 1, r, !now);
		updata(mid);
		return mid;
	}
	inline int get(int k, P p) {
		int re = 0;
		for (int i = 0; i < 2; i++)
			re += max(0, t[k].mn[i] - p[i]);
		for (int i = 0; i < 2; i++)
			re += max(0, p[i] - t[k].mx[i]);
		return re;
	}
	void insert(int k, int now) {
		if (T[now] >= t[k][now]) {
			if (t[k].r)
				insert(t[k].r, !now);
			else {
				t[k].r = ++n;
				t[n] = T;
				for (int i = 0; i < 2; i++)
					t[n].mn[i] = t[n].mx[i] = t[n][i];
			}
		} else {
			if (t[k].l)
				insert(t[k].l, !now);
			else {
				t[k].l = ++n;
				t[n] = T;
				for (int i = 0; i < 2; i++)
					t[n].mn[i] = t[n].mx[i] = t[n][i];
			}
		}
		updata(k);
	}
	void query(int k, int now) {
		int d, dl = INF, dr = INF;
		d = dis(t[k], T);
		ans = min(ans, d);
		if (t[k].l) dl = get(t[k].l, T);
		if (t[k].r) dr = get(t[k].r, T);
		if (dl < dr) {
			if (dl < ans) query(t[k].l, !now);
			if (dr < ans) query(t[k].r, !now);
		} else {
			if (dr < ans) query(t[k].r, !now);
			if (dl < ans) query(t[k].l, !now);
		}
	}
	int query(P p) {
		ans = INF;
		T = p;
		query(rot, 0);
		return ans;
	}
	void insert(P p) {
		T = p;
		insert(rot, 0);
	}
} kd;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i][0], &p[i][1]);
	rot = kd.build(1, n, 0);
	while (m--) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			kd.insert(P(x, y));
		else
			printf("%d\n", kd.query(P(x, y)));
	}
}
/*
Description

这天，SJY显得无聊。在家自己玩。在一个棋盘上，有N个黑色棋子。他每次要么放到棋盘上一个黑色棋子，要么放上一个白色棋子，如果是白色棋子，他会找出距离这个白色棋子最近的黑色棋子。此处的距离是 曼哈顿距离 即(|x1-x2|+|y1-y2|) 。现在给出N<=500000个初始棋子。和M<=500000个操作。对于每个白色棋子，输出距离这个白色棋子最近的黑色棋子的距离。同一个格子可能有多个棋子。
 
Input

第一行两个数 N M
以后M行，每行3个数 t x y
如果t=1 那么放下一个黑色棋子
如果t=2 那么放下一个白色棋子
Output

对于每个T=2 输出一个最小距离
*/

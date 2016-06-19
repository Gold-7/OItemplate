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
typedef pair<int, int> PII;
#define fi first
#define se second
#define MP make_pair

int read()
{
	int v = 0, f = 1;
	char c = getchar();
	while (c < 48 || 57 < c) {if (c == '-') f = -1; c = getchar();}
	while (48 <= c && c <= 57) v = (v << 3) + v + v + c - 48, c = getchar();
	return v * f;
}

const int N = 500010;
int n, Q;
int a[N], fa[N], son[N][2], siz[N], rev[N], q[N];
bool isroot(int x)
{
	return son[fa[x]][0] != x && son[fa[x]][1] != x;
}
void up(int x)
{
	siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}
void dn(int x)
{
	if (rev[x])
	{
		rev[x] = 0;
		rev[son[x][0]] ^= 1;
		rev[son[x][1]] ^= 1;
		swap(son[x][0], son[x][1]);
	}
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], w = son[y][1] == x;
	if (!isroot(y))
		son[z][son[z][1] == y] = x;
	son[y][w] = son[x][w ^ 1];
	fa[son[y][w]] = y;
	son[x][w ^ 1] = y;
	fa[y] = x;
	fa[x] = z;
	up(y); up(x);
}
void splay(int x)
{
	q[q[0] = 1] = x;
	for (int i = x; !isroot(i); i = fa[i])
		q[++q[0]] = fa[i];
	for (int i = q[0]; i >= 1; i--)
		dn(q[i]);
	for (int y; y = fa[x], !isroot(x); rotate(x))
		if (!isroot(y))
			rotate((x == son[y][0]) ^ (y == son[fa[y]][0]) ? x : y);
}
void access(int x)
{
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		son[x][1] = t;
		up(x);
	}
}
void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x] ^= 1;
}
void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
}
void cut(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	son[y][0] = fa[x] = 0;
	up(y);
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		siz[i] = 1;
		a[i] = fa[i] = min(i + x, n + 1);
	}
	siz[n + 1] = 1;
	Q = read();
	while (Q--)
	{
		int op = read(), x = read() + 1;
		if (op == 1)
		{
			makeroot(n + 1);
			access(x);
			splay(x);
			printf("%d\n", siz[x] - 1);
		}
		else
		{
			int y = read();
			cut(x, a[x]);
			a[x] = min(n + 1, x + y);
			link(x, a[x]);
		}
	}
}


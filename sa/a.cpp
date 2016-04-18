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

const int N = 110000;
int a[N], n;
char ch[N];

#define REP for (int i = 0; i < n; i++)
#define PER for (int i = n - 1; i >= 0; i--)
#define REP2 for (int i = 0; i < m; i++)
#define REP3 for (int i = 1; i < m; i++)
#define REP4 for (int i = 1; i < n; i++)

int wa[N], wb[N], wc[N], wd[N], sa[N], rank[N], height[N];
int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}
void da(int *r, int *sa, int n, int m) {
	int *x = wa, *y = wb;
	REP2 wd[i] = 0;
	REP wd[x[i] = r[i]]++;
	REP3 wd[i] += wd[i - 1];
	PER sa[--wd[x[i]]] = i;
	for (int j = 1, p = 1; p < n; j *= 2, m = p) {
		p = 0;
		for (int i = n - j; i < n; i++) y[p++] = i;
		REP if (sa[i] >= j) y[p++] = sa[i] - j;
		REP wc[i] = x[y[i]];
		REP2 wd[i] = 0;
		REP wd[wc[i]]++;
		REP3 wd[i] += wd[i - 1];
		PER sa[--wd[wc[i]]] = y[i];
		swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		REP4 x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
}
void calheight(int *r, int *sa, int n) {
	int j, k = 0;
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 0; i < n; height[rank[i++]] = k)
		for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
}

int main() {
	scanf("%s", ch);
	n = strlen(ch);
	for (int i = 0; i < n; i++) a[i] = ch[i] - 'a' + 1;
	da(a, sa, n + 1, 27);
	calheight(a, sa, n);
	for (int i = 1; i <= n; i++) printf("%d ", sa[i] + 1);puts("");
	for (int i = 2; i <= n; i++) printf("%d ", height[i]);puts("");
}

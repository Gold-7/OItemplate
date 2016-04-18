//bzoj2301
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

const int N = 50005;
int a, b, c, d, k;
int sum[N], mu[N], pr[N];
bool vis[N];
void Linear_Shaker() {
	mu[1] = 1;
	for (int i = 2; i <= 50000; i++) {
		if (!vis[i]) {
			mu[i] = -1;
			pr[++pr[0]] = i;
		}
		for (int j = 1; j <= pr[0] && i * pr[j] <= 50000; j++) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				mu[i * pr[j]] = 0;
				break;
			} else mu[i * pr[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= 50000; i++)
		sum[i] = sum[i - 1] + mu[i];
}
int cal(int n, int m) {
	if (n > m) swap(n, m);
	int ans = 0, pos;
	for (int i = 1; i <= n; i = pos + 1) {
		pos = min(n / (n / i), m / (m / i));
		ans += (sum[pos] - sum[i - 1]) * (n / i) * (m / i);
	}
	return ans;
}
int main() {
	Linear_Shaker();
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		a--, c--;
		a /= k, b /= k, c /= k, d /= k;
		int ans = cal(a, c) + cal(b, d) - cal(a, d) - cal(b, c);
		printf("%d\n", ans);
	}
}
/*
对于给出的n个询问，每次求有多少个数对(x,y)，满足a≤x≤b，c≤y≤d，且gcd(x,y) = k，gcd(x,y)函数为x和y的最大公约数。
*/

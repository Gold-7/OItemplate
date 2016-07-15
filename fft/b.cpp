void NTT(ll *a, int n, int ty)
{
	for (int i = n >> 1, j = 1; j < n; j++)
	{
		if (i < j) swap(a[i], a[j]);
		int k = n >> 1;
		for (; k & i; i ^= k, k >>= 1);
		i ^= k;
	}
	ll g = pw(G, (MOD - 1) / n);
	if (fl == -1)
		g = pw(g, n - 1);
	cur[0] = 1;
	for (int i = 1; i < n; i++) cur[i] = cur[i - 1] * g % MOD;
	for (int m = 2, t = n >> 1; m <= n; m <<= 1, t >>= 1)
	{
		for (int i = 0; i < n; i += m)
			for (int j = i; j < i + (m >> 1); j++)
			{
				ll u = a[j], v = a[j + (m >> 1)] * cur[(j - i) * t] % MOD;
				a[j] = (u + v) % MOD;
				a[j + (m >> 1)] = (u - v + MOD) % MOD;
			}
	}
}

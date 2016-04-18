void dfs(int u) {
	dfn[u] = low[u] = ++cnt;
	stk[++top] = u;
	for (int e = head[u]; e; e = eg[e].b) {
		int v = eg[e].a;
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else
			if (!belong[u])
				low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		id++;
		while (stk[top] != u)
			belong[stk[top--]] = id;
		belong[u] = id;
		top--;
	}
}

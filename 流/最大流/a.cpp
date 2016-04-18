//Dinic
struct EG {
	int a, b, c;
} eg[M];
int head[N], en, S, T;
int dis[N];
bool vis[N];
void SetEdge(int u, int v, int w) {
	eg[++en] = (EG) {v, head[u], w}; head[u] = en;
	eg[++en] = (EG) {u, head[v], 0}; head[v] = en;
}
void Clear() {
	memset(head, 0, sizeof head);
	en = 1;
}
bool bfs() {
	memset(vis, 0, sizeof vis); vis[S] = 1;
	queue<int> Q; Q.push(S);
	dis[S] = 0;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (int e = head[u]; e; e = eg[e].b) {
			int v = eg[e].a;
			if (!vis[v] && eg[e].c > 0) {
				vis[v] = 1;
				dis[v] = dis[u] + 1;
				Q.push(v);
			}
		}
	}
	return vis[T];
}
int dfs(int u, int rem) {
	if (u == T || rem == 0) return rem;
	int flow = 0, f;
	for (int e = head[u]; e; e = eg[e].b) {
		int v = eg[e].a;
		if (dis[u] + 1 == dis[v] && (f = dfs(v, min(rem, eg[e].c))) > 0) {
			eg[e].c -= f;
			eg[e ^ 1].c += f;
			flow += f;
			rem -= f;
			if (rem == 0) break;
		}
	}
	if (!flow) dis[u] = -1;
	return flow;
}
int dinic() {
	int re = 0;
	while (bfs()) re += dfs(S, INF);
	return re;
}

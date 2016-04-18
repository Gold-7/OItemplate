struct EG {
	int a, b, c, d, e;
} eg[M];
int head[N], en, S, T;
int dis[N], pre[N], rem[N];
bool inq[N];
void SetEdge(int u, int v, int w, int z) {
	eg[++en] = (EG) {v, head[u], w, z, u}; head[u] = en;
	eg[++en] = (EG) {u, head[v], 0, -z, v}; head[v] = en;
}
void Clear() {
	memset(head, 0, sizeof head);
	en = 1;
}
bool Spfa() {
	memset(dis, 0x3f, sizeof dis); dis[S] = 0;
	memset(inq, 0, sizeof inq); inq[S] = 1;
	queue<int> Q; Q.push(S);
	pre[S] = 0, rem[S] = INF;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		inq[u] = 0;
		for (int e = head[u]; e; e = eg[e].b) {
			int v = eg[e].a;
			if (eg[e].c > 0 && dis[u] + eg[e].d < dis[v]) {
				dis[v] = dis[u] + eg[e].d;
				pre[v] = e;
				rem[v] = min(rem[u], eg[e].c);
				if (!inq[v]) {
					inq[v] = 1;
					Q.push(v);
				}
			}
		}
	}
	if (dis[T] == 0x3f3f3f3f) return 0;
	flow += rem[T];
	cost += dis[T] * rem[T];
	int u = T;
	while (u != S) {
		eg[pre[u]].c -= rem[T];
		eg[pre[u] ^ 1].c += rem[T];
		u = eg[pre[u]].e;
	}
	return 1;
}
void MinCost() {
	flow = cost = 0;
	while (Spfa());
}

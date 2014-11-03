struct edge {
   int v, nx;
};
const int MAXN = 1000, MAXE = 2000;
edge graph[MAXE];
int last[MAXN], match[MAXN], px[MAXN], base[MAXN], N, edges;
bool used[MAXN], blossom[MAXN], lused[MAXN];
inline void add_edge(int u, int v) {
   graph[edges] = (edge) {v, last[u]};
   last[u] = edges++;
   graph[edges] = (edge) {u, last[v]};
   last[v] = edges++;
}
void mark_path(int v, int b, int children) {
   while (base[v] != b) {
      blossom[base[v]] = blossom[base[match[v]]] = true;
      px[v] = children;
      children = match[v];
      v = px[match[v]];
   }
}
int lca(int a, int b) {
   memset(lused, 0, N);
   while (1) {
      lused[a = base[a]] = true;
      if (match[a] == -1)
         break;
      a = px[match[a]];
   }
   while (1) {
      b = base[b];
      if (lused[b])
         return b;
      b = px[match[b]];
   }
}
int find_path(int root) {
   memset(used, 0, N);
   memset(px, -1, sizeof(int) * N);
   for (int i = 0; i < N; ++i)
      base[i] = i;
   used[root] = true;
   queue<int> q;
   q.push(root);
   int v, e, to, i;
   while (!q.empty()) {
      v = q.front(); q.pop();
      for (e = last[v]; e >= 0; e = graph[e].nx) {
         to = graph[e].v;
         if (base[v] == base[to] || match[v] == to)
            continue;
         if (to == root || (match[to] != -1 && px[match[to]] != -1)) {
            int curbase = lca(v, to);
            memset(blossom, 0, N);
            mark_path(v, curbase, to);
            mark_path(to, curbase, v);
            for (i = 0; i < N; ++i)
               if (blossom[base[i]]) {
                  base[i] = curbase;
                  if (!used[i]) {
                     used[i] = true;
                     q.push(i);
                  }
               }
         } else if (px[to] == -1) {
            px[to] = v;
            if (match[to] == -1)
               return to;
            to = match[to];
            used[to] = true;
            q.push(to);
         }
      }
   }
   return -1;
}
void build_pre_matching() {
   int u, e, v;
   for (u = 0; u < N; ++u)
      if (match[u] == -1)
         for (e = last[u]; e >= 0; e = graph[e].nx) {
            v = graph[e].v;
            if (match[v] == -1) {
               match[u] = v;
               match[v] = u;
               break;
            }
         }
}
void edmonds() {
   memset(match, 0xff, sizeof(int) * N);
   build_pre_matching();
   int i, v, pv, ppv;
   for (i = 0; i < N; ++i)
      if (match[i] == -1) {
         v = find_path(i);
         while (v != -1) {
            pv = px[v], ppv = match[pv];
            match[v] = pv, match[pv] = v;
            v = ppv;
         }
      }
}
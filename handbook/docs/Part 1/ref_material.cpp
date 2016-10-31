$$Graph Theory

/* Strongly Connected Components
O(V+E)
Partitions the vertices of a directed graph into strongly connected components.
A strongly connected component is a subset of a graph where every vertex is reachable from every other vertex.
Returns V where V[i] is the index of the component of node i.
*/
vi low1, num1, components;
int counter1, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int cv) {
  low1[cv] = num1[cv] = counter1++;
  S.push(cv);
  visited[cv] = true;
  FORC(g.edges[cv], edge) {
    if(num1[edge->to] == -1)
      dfs(g, edge->to);
    if(visited[edge->to])
      low1[cv] = min(low1[cv], low1[edge->to]);        
  }
  if(low1[cv] == num1[cv]) {
    int index = SCCindex++;
    while(true) {
      int v = S.top(); S.pop(); visited[v] = 0;
      components[v] = index;
      if (cv == v)
        break;
    }
  }
}

vi stronglyConnectedComponents(Graph &g) {
  counter1 = 0, SCCindex = 0;
  visited = vector<bool>(g.V, 0);
  num1 = vi(g.V, -1), low1 = vi(g.V, 0), components = vi(g.V, 0);
  S = stack<int>();
  FOR(i, 0, g.V)
    if(num1[i] == -1)
      dfs(g, i);
  return components;
}

/* Articulation Points
O(V+E)
Finds all articulation points and bridges in a graph.
An articulation point is a vertex whose removal would disconnect the graph.
An bridge is a vertex whose removal disconnects the graph.
*/
vi low2, num2, parent, strongPoints;
int counter2, root, rootChildren;
void dfs1(Graph &g, int v) {
  low2[v] = num2[v] = counter2++;
  FORC(g.edges[v], edge) {
    if(num2[edge->to] == -1) {
      parent[edge->to] = v;
      if(v == root) rootChildren++;
      dfs1(g, edge->to);
      if(low2[edge->to] >= num2[v]) strongPoints[v] = true;
      if(low2[edge->to] > num2[v]) edge->strong = g.edges[edge->to][edge->backEdge].strong = true;
      low2[v] = min(low2[v], low2[edge->to]);
    } else if(edge->to != parent[v])
      low2[v] = min(low2[v], num2[edge->to]);
  }
}

vi articulationPointsAndBridges(Graph &g) {
  counter2 = 0;
  num2 = vi(g.V, -1), low2 = vi(g.V, 0), parent = vi(g.V, -1), strongPoints = vi(g.V, 0);
  FOR(i, 0, g.V)
    if(num2[i] == -1) {
      root = i, rootChildren = 0;
      dfs1(g, i);
      strongPoints[root] = rootChildren > 1;
    }
  return strongPoints;
}

/* Eulerian Path
O(V+E)
Partitions the vertices of a directed graph into strongly connected components.
A strongly connected component is a subset of a graph where every vertex is reachable from every other vertex.
Returns V where V[i] is the index of the component of node i.
*/
vi low1, num1, components;
int counter1, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int cv) {
  low1[cv] = num1[cv] = counter1++;
  S.push(cv);
  visited[cv] = true;
  FORC(g.edges[cv], edge) {
    if(num1[edge->to] == -1)
      dfs(g, edge->to);
    if(visited[edge->to])
      low1[cv] = min(low1[cv], low1[edge->to]);        
  }
  if(low1[cv] == num1[cv]) {
    int index = SCCindex++;
    while(true) {
      int v = S.top(); S.pop(); visited[v] = 0;
      components[v] = index;
      if (cv == v)
        break;
    }
  }
}

vi stronglyConnectedComponents(Graph &g) {
  counter1 = 0, SCCindex = 0;
  visited = vector<bool>(g.V, 0);
  num1 = vi(g.V, -1), low1 = vi(g.V, 0), components = vi(g.V, 0);
  S = stack<int>();
  FOR(i, 0, g.V)
    if(num1[i] == -1)
      dfs(g, i);
  return components;
}

/* Max Bipartite Matching
O(VE)
Nodes in the left set must be nodes [0, left)
g must be unweighted directed bipartite graph
match[r] = l, where r belongs to R and l belongs to L
*/
int augment(Graph &g, int cv, vi &match, vi &visited) {
  if(visited[cv]) return 0;
  visited[cv] = 1;
  FORC(g.edges[cv], edge)
    if(match[edge->to] == -1 || augment(g, match[edge->to], match, visited))
      return match[edge->to] = cv, 1;
  return 0;
}

int maxBipartiteMatching(Graph &g, int left) {
  int MCBM = 0;
  vi match(g.V, -1);
  FOR(cv, 0, left) {
    vi visited(left, 0);
    MCBM += augment(g, cv, match, visited);
  }
  return MCBM;
}

/* Edmonds-Karp
O(VE^2)
Finds a the maxflow from source to sink of a directed graph.
The weight of an edge denotes the capacity of the edge.
The negative weight edges are the edges with flow.
*/
int augment(MatrixGraph &g, int flow, vi &parent, int source, int cv, int minEdge) {
  if(cv == source)
    return minEdge;
  if(parent[cv] != -1) {
    flow = augment(g, flow, parent, source, parent[cv], min(minEdge, g.edges[parent[cv]][cv].weight));
    g.edges[parent[cv]][cv].weight -= flow;
    g.edges[cv][parent[cv]].weight += flow;
  }
  return flow;
}

int maxFlow(MatrixGraph &g, int source, int sink) {
  int mf = 0, flow = -1;
  while(flow) {
    vi distanceTo(g.V, INF);
    distanceTo[source] = 0;
    queue<int> q; q.push(source);
    vi parent(g.V, -1);
    while(!q.empty()) {
      int cv = q.front(); q.pop();
      if(cv == sink) break;
      FOR(i, 0, g.V)
        if(g.edges[cv][i].weight > 0 && distanceTo[i] == INF)
          distanceTo[i] = distanceTo[cv] + 1, q.push(i), parent[i] = cv;
    }
    mf += flow = augment(g, 0, parent, source, sink, INF);
  }
  return mf;
}

/* Dinic
O(EV^2)
Adjacency list implementation of Dinic's blocking flow algorithm.
This is very fast in practice, and only loses to push-relabel flow.
Running time:
OUTPUT:
    - maximum flow value
    - To obtain actual flow values, look at edges with capacity > 0 (zero capacity edges are residual edges).
*/
typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
  LL rcap() { return cap - flow; }
};

struct Dinic {
  int N;
  vector<vector<Edge> > G;
  vector<vector<Edge *> > Lf;
  vector<int> layer;
  vector<int> Q;
  
  Dinic(int N) : N(N), G(N), Q(N) {}
  
  void AddEdge(int from, int to, int cap) {
    if (from == to) return;
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  LL BlockingFlow(int s, int t) {
    layer.clear(); layer.resize(N, -1);
    layer[s] = 0;
    Lf.clear(); Lf.resize(N);
    
    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < G[x].size(); i++) {
        Edge &e = G[x][i]; if (e.rcap() <= 0) continue;
        if (layer[e.to] == -1) {
          layer[e.to] = layer[e.from] + 1;
          Q[tail++] = e.to;
        }
        if (layer[e.to] > layer[e.from]) {
          Lf[e.from].push_back(&e);
        }
      }
    }
    if (layer[t] == -1) return 0;

    LL totflow = 0;
    vector<Edge *> P;
    while (!Lf[s].empty()) {
      int curr = P.empty() ? s : P.back()->to;
      if (curr == t) { // Augment
        LL amt = P.front()->rcap();
        for (int i = 0; i < P.size(); ++i) {
          amt = min(amt, P[i]->rcap());
        }
        totflow += amt;
        for (int i = P.size() - 1; i >= 0; --i) {
          P[i]->flow += amt;
          G[P[i]->to][P[i]->index].flow -= amt;
          if (P[i]->rcap() <= 0) {
            Lf[P[i]->from].pop_back();
            P.resize(i);
          }
        }
      } else if (Lf[curr].empty()) { // Retreat
        P.pop_back();
        for (int i = 0; i < N; ++i)
          for (int j = 0; j < Lf[i].size(); ++j)
            if (Lf[i][j]->to == curr)
              Lf[i].erase(Lf[i].begin() + j);
      } else { // Advance
        P.push_back(Lf[curr].back());
      }
    }
    return totflow;
  }

  LL GetMaxFlow(int s, int t) {
    LL totflow = 0;
    while (LL flow = BlockingFlow(s, t))
      totflow += flow;
    return totflow;
  }
};

/* Min Cost Max Flow
Implementation of min cost max flow algorithm using adjacency
matrix (Edmonds and Karp 1972).  This implementation keeps track of
forward and reverse edges separately (so you can set cap[i][j] !=
cap[j][i]).  For a regular max flow, set all edge costs to 0.
Running time, O(|V|^2) cost per augmentation
    max flow:           O(|V|^3) augmentations
    min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
    
INPUT: 
    - graph, constructed using AddEdge()
    - source
    - sink
OUTPUT:
    - (maximum flow value, minimum cost value)
    - To obtain the actual flow, look at positive values only.
*/
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost;
  VI found;
  VL dist, pi, width;
  VPII dad;

  MinCostMaxFlow(int N) : 
    N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)), 
    found(N), dist(N), pi(N), width(N), dad(N) {}
  
  void AddEdge(int from, int to, L cap, L cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }
  
  void Relax(int s, int k, L cap, L cost, int dir) {
    L val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  L Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;
    
    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  pair<L, L> GetMaxFlow(int s, int t) {
    L totflow = 0, totcost = 0;
    while (L amt = Dijkstra(s, t)) {
      totflow += amt;
      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }
    }
    return make_pair(totflow, totcost);
  }
};

/* PushRelabel
O(V^3)
Adjacency list implementation of FIFO push relabel maximum flow
with the gap relabeling heuristic.  This implementation is
significantly faster than straight Ford-Fulkerson.  It solves
random problems with 10000 vertices and 1000000 edges in a few
seconds, though it is possible to construct test cases that
achieve the worst-case.
Running time:
OUTPUT:
    - maximum flow value
    - To obtain the actual flow values, look at all edges with
      capacity > 0 (zero capacity edges are residual edges).
*/
typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(int v) { 
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  
  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++) 
      if (G[v][i].cap - G[v][i].flow > 0)
  dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1) 
  Gap(dist[v]); 
      else
  Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    
    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

/* Min Cost Matching (Hungarian
O(V^3)
Min cost bipartite matching via shortest augmenting paths.
In practice, it solves 1000x1000 problems in around 1 second.
  cost[i][j] = cost for pairing left node i with right node j
  Lmate[i] = index of right node that left node i pairs with
  Rmate[j] = index of left node that right node j pairs with
The values in cost[i][j] may be positive or negative.
To perform maximization, simply negate the cost[][] matrix.
*/
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

double MinCostMatching(const VVD &cost, VI &Lmate, VI &Rmate) {
  int n = int(cost.size());

  // construct dual feasible solution
  VD u(n);
  VD v(n);
  for (int i = 0; i < n; i++) {
    u[i] = cost[i][0];
    for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
  }
  for (int j = 0; j < n; j++) {
    v[j] = cost[0][j] - u[0];
    for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
  }
  
  // construct primal solution satisfying complementary slackness
  Lmate = VI(n, -1);
  Rmate = VI(n, -1);
  int mated = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (Rmate[j] != -1) continue;
      if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
  Lmate[i] = j;
  Rmate[j] = i;
  mated++;
  break;
      }
    }
  }
  
  VD dist(n);
  VI dad(n);
  VI seen(n);
  
  // repeat until primal solution is feasible
  while (mated < n) {
    
    // find an unmatched left node
    int s = 0;
    while (Lmate[s] != -1) s++;
    
    // initialize Dijkstra
    fill(dad.begin(), dad.end(), -1);
    fill(seen.begin(), seen.end(), 0);
    for (int k = 0; k < n; k++) 
      dist[k] = cost[s][k] - u[s] - v[k];
    
    int j = 0;
    while (true) {
      
      // find closest
      j = -1;
      for (int k = 0; k < n; k++) {
  if (seen[k]) continue;
  if (j == -1 || dist[k] < dist[j]) j = k;
      }
      seen[j] = 1;
      
      // termination condition
      if (Rmate[j] == -1) break;
      
      // relax neighbors
      const int i = Rmate[j];
      for (int k = 0; k < n; k++) {
  if (seen[k]) continue;
  const double new_dist = dist[j] + cost[i][k] - u[i] - v[k];
  if (dist[k] > new_dist) {
    dist[k] = new_dist;
    dad[k] = j;
  }
      }
    }
    
    // update dual variables
    for (int k = 0; k < n; k++) {
      if (k == j || !seen[k]) continue;
      const int i = Rmate[k];
      v[k] += dist[k] - dist[j];
      u[i] -= dist[k] - dist[j];
    }
    u[s] += dist[j];
    
    // augment along path
    while (dad[j] >= 0) {
      const int d = dad[j];
      Rmate[j] = Rmate[d];
      Lmate[Rmate[j]] = j;
      j = d;
    }
    Rmate[j] = s;
    Lmate[s] = j;
    
    mated++;
  }
  
  double value = 0;
  for (int i = 0; i < n; i++)
    value += cost[i][Lmate[i]];
  
  return value;
}

/* Min Cut
O(|V|^3)
Adjacency matrix implementation of Stoer-Wagner min cut algorithm.
OUTPUT:
    - (min cut value, nodes in half of min cut)
*/
typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1000000000;

pair<int, VI> GetMinCut(VVI &weights) {
  int N = weights.size();
  VI used(N), cut, best_cut;
  int best_weight = -1;
  
  for (int phase = N-1; phase >= 0; phase--) {
    VI w = weights[0];
    VI added = used;
    int prev, last = 0;
    for (int i = 0; i < phase; i++) {
      prev = last;
      last = -1;
      for (int j = 1; j < N; j++)
  if (!added[j] && (last == -1 || w[j] > w[last])) last = j;
      if (i == phase-1) {
  for (int j = 0; j < N; j++) weights[prev][j] += weights[last][j];
  for (int j = 0; j < N; j++) weights[j][prev] = weights[prev][j];
  used[last] = true;
  cut.push_back(last);
  if (best_weight == -1 || w[last] < best_weight) {
    best_cut = cut;
    best_weight = w[last];
  }
      } else {
  for (int j = 0; j < N; j++)
    w[j] += weights[last][j];
  added[last] = true;
      }
    }
  }
  return make_pair(best_weight, best_cut);
}

/* Edmonds Graph Matching
*/
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

/* Dijkstra
O((V+E)logV)
Finds the shortest path from source to every other vertex.
*/
vi dijkstra(Graph &g, int src) {
  vi dist(g.V, INF);
  dist[src] = 0;
  priority_queue<ii, vii, greater<ii> > pq;
  pq.push(ii(0, src));
  while(!pq.empty()) {
    int cv = pq.top().second;
    int d = pq.top().first;
    pq.pop();
    if(d > dist[cv]) continue;
    FORC(g.edges[cv], edge)
      if(dist[edge->to] > dist[cv] + edge->weight) {
        dist[edge->to] = dist[cv] + edge->weight;
        pq.push(ii(dist[edge->to], edge->to));
      }
  }
  return dist;
}

/* Kruskal
O(ELogV)
Finds a minimum spanning tree of a undirected graph.
Returns the indices of the edges that are int the MST.
*/
int *comparator1;
bool compare(int a, int b) { return comparator1[a] < comparator1[b]; }
vi kruskal(vii &edges, int weight[], int V) {
  vi order(edges.size()), minTree;    
  UnionFindDS ds(V);
  comparator1 = weight;
  FOR(i, 0, order.size()) order[i] = i;
  sort(order.begin(), order.end(), compare);
  for(int i=0; i<int(edges.size()) && int(minTree.size()) < V - 1; i++)
    if(!ds.connected(edges[order[i]].first, edges[order[i]].second)) {
      ds.connect(edges[order[i]].first, edges[order[i]].second);
      minTree.pb(order[i]);
    }
  return minTree;
}

/* Prim
O(ELogV)
Finds a minimum spanning tree of a undirected graph.
Returns a list of edges (node, indexOfEdge).
*/
Graph* comparator2;
struct Compare { bool operator()(ii a, ii b) { return comparator2->edges[a.first][a.second].weight > comparator2->edges[b.first][b.second].weight;} };
vii prim(Graph &g) {
  vi visited(g.V, 0);
  visited[0] = 1;
  vii tree; //list of edges in the MST
  int visitedNodes = 1;
  comparator2 = &g;
  priority_queue<ii, vector<ii>, Compare> pq;
  int cv = 0;
  while(visitedNodes != g.V) {
    FORC(g.edges[cv], edge)
      if(!visited[edge->to])
        pq.push(ii(cv, edge - g.edges[cv].begin()));
    ii nextEdge;
    do {
      nextEdge = pq.top();
      pq.pop();
    } while(visited[g.edges[nextEdge.first][nextEdge.second].to] && !pq.empty());
    tree.pb(nextEdge);
    cv = g.edges[nextEdge.first][nextEdge.second].to;
    visitedNodes++;
    visited[cv] = 1;
  }
  return tree;
}

/* All nodes Longest Path to Leaf in Tree
O(V+E)
return V where V[i].second contains the height of the tree if node i is the root.
V[i].first contains the index of the next node in the longest path towards a leaf.
*/
int getLongestPathDown(Graph &g, int cv, vii &longestPathDown, vii &secondLongestPathDown, vi &parent) {
  FORC(g.edges[cv], edge) {
    if(edge->to != parent[cv]) {
      parent[edge->to] = cv;
      int pathDownLength = 1 + getLongestPathDown(g, edge->to, longestPathDown, secondLongestPathDown, parent);
      if(pathDownLength > longestPathDown[cv].second) {
        secondLongestPathDown[cv] = longestPathDown[cv];
        longestPathDown[cv] = ii(edge->to, pathDownLength);
      } else if(pathDownLength > secondLongestPathDown[cv].second) {
        secondLongestPathDown[cv] = ii(edge->to, pathDownLength);
      }
    }
  }
  return longestPathDown[cv].second;
}

void getLongestPath(Graph &g, vii &longestPath) {
  longestPath.assign(g.V, ii(-1, 0));
  vii longestPathDown(g.V, ii(-1, 1)), secondLongestPathDown(g.V, ii(-1, 1)), secondLongestPath(g.V, ii(-1, 0));
  vi parent(g.V, -1);
  getLongestPathDown(g, 0, longestPathDown, secondLongestPathDown, parent);
  queue<int> q;
  q.push(0);
  while(!q.empty()) {
    int cv = q.front(); q.pop();
    FORC(g.edges[cv], edge)
      if(edge->to != parent[cv]) 
        q.push(edge->to);
    if(parent[cv] == -1) {
      longestPath[cv] = longestPathDown[cv];
      secondLongestPath[cv] = secondLongestPathDown[cv];
    } else {
      ii longestPathThroughParent = ii(parent[cv], (longestPath[parent[cv]].first != cv ? longestPath[parent[cv]].second : secondLongestPath[parent[cv]].second)+1);
      if(longestPathThroughParent.second >= longestPathDown[cv].second) {
        longestPath[cv] = longestPathThroughParent;
        secondLongestPath[cv] = longestPathDown[cv];
      } else if(longestPathThroughParent.second >= secondLongestPathDown[cv].second) {
        longestPath[cv] = longestPathDown[cv];
        secondLongestPath[cv] = longestPathThroughParent;
      } else {
        longestPath[cv] = longestPathDown[cv];
        secondLongestPath[cv] = secondLongestPathDown[cv];
      }
    }
  }
}

$$Number Theory

/* Sieve of Atkin
Obtains primes in the range [1, n]
*/
typedef vector<ll> vll;
vll primes;
void sieve_atkins(ll n) {
   vector<bool> isPrime(n + 1);
   isPrime[2] = isPrime[3] = true;
   for (ll i = 5; i <= n; i++)
      isPrime[i] = false;

   ll lim = ceil(sqrt(n));
   for (ll x = 1; x <= lim; x++) {
      for (ll y = 1; y <= lim; y++) {
         ll num = (4 * x * x + y * y);
         if (num <= n && (num % 12 == 1 || num % 12 == 5))
            isPrime[num] = true;
         num = (3 * x * x + y * y);
         if (num <= n && (num % 12 == 7))
            isPrime[num] = true;
         if (x > y) {
            num = (3 * x * x - y * y);
            if (num <= n && (num % 12 == 11))
               isPrime[num] = true;
         }
      }
   }

   for (ll i = 5; i <= lim; i++)
      if (isPrime[i])
         for (ll j = i * i; j <= n; j += i)
            isPrime[j] = false;

   for (ll i = 2; i <= n; i++)
      if (isPrime[i])
         primes.pb(i);
}

/* Sieve of Eratosthenes
Obtains primes in the range [1, n]
*/
#define SIZE 1000000
bitset<SIZE> sieve;
void buildSieve() {
  sieve.set();
  sieve[0] = sieve[1] = 0;
  int root = sqrt(SIZE);
  FOR(i, 2, root+1)
    if (sieve[i])
      for(int j = i*i; j < SIZE; j+=i)
        sieve[j] = 0;
}

vi primesList;
void buildPrimesList() {
  if(!sieve[2])
    buildSieve();
  primesList.reserve(SIZE/log(SIZE));
  FOR(i, 2, SIZE+1)
    if(sieve[i])
      primesList.pb(i);
}

/* Extended Euclid
Finds x,y such that d = ax + by.
Returns d = gcd(a,b).
*/
int extended_euclid(int a, int b, int &x, int &y) {  
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

/* Modular Linaer Equation Solver
Finds all solutions to ax = b (mod n)
*/
vi modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  vi solutions;
  int d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    FOR(i, 0, d)
      solutions.pb(mod(x + i*(n/d), n));
  }
  return solutions;
}

/* Modular Inverse
Computes b such that ab = 1 (mod n), returns -1 on failure
*/
int mod_inverse(int a, int n) {
  int x, y;
  int d = extended_euclid(a, n, x, y);
  if (d > 1) return -1;
  return mod(x,n);
}

/* Chinese Remainder Theorem
Returns \[x = a_i (mod n_i)\]
n's must be pairwise coprimes
*/
int chinese_remainder(int *n, int *a, int len) {
  int p, i, prod = 1, sum = 0;
  for (i = 0; i < len; i++) prod *= n[i];
  for (i = 0; i < len; i++) {
    p = prod / n[i];
    sum += a[i] * mod_inverse(p, n[i]) * p;
  }
  return sum % prod;
}

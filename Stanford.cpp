$Dinic
// Running time: O(|V|^2 |E|)
// OUTPUT:
//     - maximum flow value
//     - To obtain the actual flow values, look at all edges with
//       capacity > 0 (zero capacity edges are residual edges).

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic {
	int N;
	vector<vector<Edge> > G;
	vector<Edge *> dad;
	vector<int> Q;
	Dinic(int N) : N(N), G(N), dad(N), Q(N) {}
	void AddEdge(int from, int to, int cap) {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}
	long long BlockingFlow(int s, int t) {
		fill(dad.begin(), dad.end(), (Edge *) NULL);
		dad[s] = &G[0][0] - 1;
		
		int head = 0, tail = 0;
		Q[tail++] = s;
		while (head < tail) {
			int x = Q[head++];
			for (int i = 0; i < G[x].size(); i++) {
				Edge &e = G[x][i];
				if (!dad[e.to] && e.cap - e.flow > 0) {
					dad[e.to] = &G[x][i];
					Q[tail++] = e.to;
				}
			}
		}
		if (!dad[t]) return 0;

		long long totflow = 0;
		for (int i = 0; i < G[t].size(); i++) {
			Edge *start = &G[G[t][i].to][G[t][i].index];
			int amt = INF;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
				if (!e) { amt = 0; break; }
				amt = min(amt, e->cap - e->flow);
			}
			if (amt == 0) continue;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
				e->flow += amt;
				G[e->to][e->index].flow -= amt;
			}
			totflow += amt;
		}
		return totflow;
	}

	long long GetMaxFlow(int s, int t) {
		long long totflow = 0;
		while (long long flow = BlockingFlow(s, t))
			totflow += flow;
		return totflow;
	}
};

$MinCostMaxFlow
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//     
// INPUT: 
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.
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

$PushRelabel
// significantly faster than straight Ford-Fulkerson.  It solves
// random problems with 10000 vertices and 1000000 edges in a few
// seconds, though it is possible to construct test cases that
// achieve the worst-case.
// Running time:
//     O(|V|^3)
// INPUT: 
//     - graph, constructed using AddEdge()
//     - source
//     - sink
// OUTPUT:
//     - maximum flow value
//     - To obtain the actual flow values, look at all edges with
//       capacity > 0 (zero capacity edges are residual edges).

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
$MinCostMatching
// In practice, it solves 1000x1000 problems in around 1
// second.
//   cost[i][j] = cost for pairing left node i with right node j
//   Lmate[i] = index of right node that left node i pairs with
//   Rmate[j] = index of left node that right node j pairs with
// The values in cost[i][j] may be positive or negative.  To perform
// maximization, simply negate the cost[][] matrix.
// COST MUST BE SQUARE

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
$MinCut

// Adjacency matrix implementation of Stoer-Wagner min cut algorithm.
// Running time:
//     O(|V|^3)
// INPUT: 
//     - graph, constructed using AddEdge()
// OUTPUT:
//     - (min cut value, nodes in half of min cut)

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

$GraphCutInference

// Special-purpose {0,1} combinatorial optimization solver for
// problems of the following by a reduction to graph cuts:
//
//        minimize         sum_i  psi_i(x[i]) 
//  x[1]...x[n] in {0,1}      + sum_{i < j}  phi_{ij}(x[i], x[j])
//
// where
//      psi_i : {0, 1} --> R
//   phi_{ij} : {0, 1} x {0, 1} --> R
//
// such that
//   phi_{ij}(0,0) + phi_{ij}(1,1) <= phi_{ij}(0,1) + phi_{ij}(1,0)  (*)
//
// This can also be used to solve maximization problems where the
// direction of the inequality in (*) is reversed.
//
// INPUT: phi -- a matrix such that phi[i][j][u][v] = phi_{ij}(u, v)
//        psi -- a matrix such that psi[i][u] = psi_i(u)
//        x -- a vector where the optimal solution will be stored
//
// OUTPUT: value of the optimal solution
//
// To use this code, create a GraphCutInference object, and call the
// DoInference() method.  To perform maximization instead of minimization,
// ensure that #define MAXIMIZATION is enabled.
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;
typedef vector<VVVI> VVVVI;

const int INF = 1000000000;

// comment out following line for minimization
#define MAXIMIZATION

struct GraphCutInference {
	int N;
	VVI cap, flow;
	VI reached;
	
	int Augment(int s, int t, int a) {
		reached[s] = 1;
		if (s == t) return a; 
		for (int k = 0; k < N; k++) {
			if (reached[k]) continue;
			if (int aa = min(a, cap[s][k] - flow[s][k])) {
		if (int b = Augment(k, t, aa)) {
			flow[s][k] += b;
			flow[k][s] -= b;
			return b;
		}
			}
		}
		return 0;
	}
	
	int GetMaxFlow(int s, int t) {
		N = cap.size();
		flow = VVI(N, VI(N));
		reached = VI(N);
		
		int totflow = 0;
		while (int amt = Augment(s, t, INF)) {
			totflow += amt;
			fill(reached.begin(), reached.end(), 0);
		}
		return totflow;
	}
	
	int DoInference(const VVVVI &phi, const VVI &psi, VI &x) {
		int M = phi.size();
		cap = VVI(M+2, VI(M+2));
		VI b(M);
		int c = 0;

		for (int i = 0; i < M; i++) {
			b[i] += psi[i][1] - psi[i][0];
			c += psi[i][0];
			for (int j = 0; j < i; j++)
		b[i] += phi[i][j][1][1] - phi[i][j][0][1];
			for (int j = i+1; j < M; j++) {
		cap[i][j] = phi[i][j][0][1] + phi[i][j][1][0] - phi[i][j][0][0] - phi[i][j][1][1];
		b[i] += phi[i][j][1][0] - phi[i][j][0][0];
		c += phi[i][j][0][0];
			}
		}
		
#ifdef MAXIMIZATION
		for (int i = 0; i < M; i++) {
			for (int j = i+1; j < M; j++) 
		cap[i][j] *= -1;
			b[i] *= -1;
		}
		c *= -1;
#endif

		for (int i = 0; i < M; i++) {
			if (b[i] >= 0) {
		cap[M][i] = b[i];
			} else {
		cap[i][M+1] = -b[i];
		c += b[i];
			}
		}

		int score = GetMaxFlow(M, M+1);
		fill(reached.begin(), reached.end(), 0);
		Augment(M, M+1, INF);
		x = VI(M);
		for (int i = 0; i < M; i++) x[i] = reached[i] ? 0 : 1;
		score += c;
#ifdef MAXIMIZATION
		score *= -1;
#endif

		return score;
	}

};

int main() {
	// solver for "Cat vs. Dog" from NWERC 2008
	int numcases;
	cin >> numcases;
	for (int caseno = 0; caseno < numcases; caseno++) {
		int c, d, v;
		cin >> c >> d >> v;

		VVVVI phi(c+d, VVVI(c+d, VVI(2, VI(2))));
		VVI psi(c+d, VI(2));
		for (int i = 0; i < v; i++) {
			char p, q;
			int u, v;
			cin >> p >> u >> q >> v;
			u--; v--;
			if (p == 'C') {
		phi[u][c+v][0][0]++;
		phi[c+v][u][0][0]++;
			} else {
		phi[v][c+u][1][1]++;
		phi[c+u][v][1][1]++;
			}
		}
		
		GraphCutInference graph;
		VI x;
		cout << graph.DoInference(phi, psi, x) << endl;
	}

	return 0;
}
$Geometry
#include <cassert>

double INF = 1e100;
double EPS = 1e-12;

struct PT { 
	double x, y; 
	PT() {}
	PT(double x, double y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y)    {}
	PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
	PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
	PT operator * (double c)     const { return PT(x*c,   y*c  ); }
	PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
	os << "(" << p.x << "," << p.y << ")"; 
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) { 
	return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
	return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
	double r = dot(b-a,b-a);
	if (fabs(r) < EPS) return a;
	r = dot(c-a, b-a)/r;
	if (r < 0) return a;
	if (r > 1) return b;
	return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
	return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z, double a, double b, double c, double d) {
	return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) { 
	return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(PT a, PT b, PT c, PT d) { 
	return LinesParallel(a, b, c, d)
			&& fabs(cross(a-b, a-c)) < EPS
			&& fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
			dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
		if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
			return false;
		return true;
	}
	if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
	if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
	return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
	b=b-a; d=c-d; c=c-a;
	assert(dot(b, b) > EPS && dot(d, d) > EPS);
	return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
	b=(a+b)/2;
	c=(a+c)/2;
	return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i+1)%p.size();
		if ((p[i].y <= q.y && q.y < p[j].y || 
			p[j].y <= q.y && q.y < p[i].y) &&
			q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
			c = !c;
	}
	return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
	for (int i = 0; i < p.size(); i++)
		if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
			return true;
		return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, double r) {
	vector<PT> ret;
	b = b-a;
	a = a-c;
	double A = dot(b, b);
	double B = dot(a, b);
	double C = dot(a, a) - r*r;
	double D = B*B - A*C;
	if (D < -EPS) return ret;
	ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
	if (D > EPS)
		ret.push_back(c+a+b*(-B-sqrt(D))/A);
	return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
	vector<PT> ret;
	double d = sqrt(dist2(a, b));
	if (d > r+R || d+min(r, R) < max(r, R)) return ret;
	double x = (d*d-R*R+r*r)/(2*d);
	double y = sqrt(r*r-x*x);
	PT v = (b-a)/d;
	ret.push_back(a+v*x + RotateCCW90(v)*y);
	if (y > 0)
		ret.push_back(a+v*x - RotateCCW90(v)*y);
	return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<PT> &p) {
	double area = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i+1) % p.size();
		area += p[i].x*p[j].y - p[j].x*p[i].y;
	}
	return area / 2.0;
}

double ComputeArea(const vector<PT> &p) {
	return fabs(ComputeSignedArea(p));
}

PT ComputeCentroid(const vector<PT> &p) {
	PT c(0,0);
	double scale = 6.0 * ComputeSignedArea(p);
	for (int i = 0; i < p.size(); i++) {
		int j = (i+1) % p.size();
		c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
	}
	return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<PT> &p) {
	for (int i = 0; i < p.size(); i++) {
		for (int k = i+1; k < p.size(); k++) {
			int j = (i+1) % p.size();
			int l = (k+1) % p.size();
			if (i == l || j == k) continue;
			if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
				return false;
		}
	}
	return true;
}

int main() {
	// expected: (-5,2)
	cerr << RotateCCW90(PT(2,5)) << endl;
	
	// expected: (5,-2)
	cerr << RotateCW90(PT(2,5)) << endl;
	
	// expected: (-5,2)
	cerr << RotateCCW(PT(2,5),M_PI/2) << endl;
	
	// expected: (5,2)
	cerr << ProjectPointLine(PT(-5,-2), PT(10,4), PT(3,7)) << endl;
	
	// expected: (5,2) (7.5,3) (2.5,1)
	cerr << ProjectPointSegment(PT(-5,-2), PT(10,4), PT(3,7)) << " "
			 << ProjectPointSegment(PT(7.5,3), PT(10,4), PT(3,7)) << " "
			 << ProjectPointSegment(PT(-5,-2), PT(2.5,1), PT(3,7)) << endl;
	
	// expected: 6.78903
	cerr << DistancePointPlane(4,-4,3,2,-2,5,-8) << endl;
	
	// expected: 1 0 1
	cerr << LinesParallel(PT(1,1), PT(3,5), PT(2,1), PT(4,5)) << " "
			 << LinesParallel(PT(1,1), PT(3,5), PT(2,0), PT(4,5)) << " "
			 << LinesParallel(PT(1,1), PT(3,5), PT(5,9), PT(7,13)) << endl;
	
	// expected: 0 0 1
	cerr << LinesCollinear(PT(1,1), PT(3,5), PT(2,1), PT(4,5)) << " "
			 << LinesCollinear(PT(1,1), PT(3,5), PT(2,0), PT(4,5)) << " "
			 << LinesCollinear(PT(1,1), PT(3,5), PT(5,9), PT(7,13)) << endl;
	
	// expected: 1 1 1 0
	cerr << SegmentsIntersect(PT(0,0), PT(2,4), PT(3,1), PT(-1,3)) << " "
			 << SegmentsIntersect(PT(0,0), PT(2,4), PT(4,3), PT(0,5)) << " "
			 << SegmentsIntersect(PT(0,0), PT(2,4), PT(2,-1), PT(-2,1)) << " "
			 << SegmentsIntersect(PT(0,0), PT(2,4), PT(5,5), PT(1,7)) << endl;
	
	// expected: (1,2)
	cerr << ComputeLineIntersection(PT(0,0), PT(2,4), PT(3,1), PT(-1,3)) << endl;
	
	// expected: (1,1)
	cerr << ComputeCircleCenter(PT(-3,4), PT(6,1), PT(4,5)) << endl;
	
	vector<PT> v; 
	v.push_back(PT(0,0));
	v.push_back(PT(5,0));
	v.push_back(PT(5,5));
	v.push_back(PT(0,5));
	
	// expected: 1 1 1 0 0
	cerr << PointInPolygon(v, PT(2,2)) << " "
			 << PointInPolygon(v, PT(2,0)) << " "
			 << PointInPolygon(v, PT(0,2)) << " "
			 << PointInPolygon(v, PT(5,2)) << " "
			 << PointInPolygon(v, PT(2,5)) << endl;
	
	// expected: 0 1 1 1 1
	cerr << PointOnPolygon(v, PT(2,2)) << " "
			 << PointOnPolygon(v, PT(2,0)) << " "
			 << PointOnPolygon(v, PT(0,2)) << " "
			 << PointOnPolygon(v, PT(5,2)) << " "
			 << PointOnPolygon(v, PT(2,5)) << endl;
	
	// expected: (1,6)
	//           (5,4) (4,5)
	//           blank line
	//           (4,5) (5,4)
	//           blank line
	//           (4,5) (5,4)
	vector<PT> u = CircleLineIntersection(PT(0,6), PT(2,6), PT(1,1), 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleLineIntersection(PT(0,9), PT(9,0), PT(1,1), 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(PT(1,1), PT(10,10), 5, 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(PT(1,1), PT(8,8), 5, 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(PT(1,1), PT(4.5,4.5), 10, sqrt(2.0)/2.0);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(PT(1,1), PT(4.5,4.5), 5, sqrt(2.0)/2.0);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	
	// area should be 5.0
	// centroid should be (1.1666666, 1.166666)
	PT pa[] = { PT(0,0), PT(5,0), PT(1,1), PT(0,5) };
	vector<PT> p(pa, pa+4);
	PT c = ComputeCentroid(p);
	cerr << "Area: " << ComputeArea(p) << endl;
	cerr << "Centroid: " << c << endl;
	
	return 0;
}
$JavaGeometry

// In this example, we read an input file containing three lines, each
// containing an even number of doubles, separated by commas.  The first two
// lines represent the coordinates of two polygons, given in counterclockwise 
// (or clockwise) order, which we will call "A" and "B".  The last line 
// contains a list of points, p[1], p[2], ...
//
// Our goal is to determine:
//   (1) whether B - A is a single closed shape (as opposed to multiple shapes)
//   (2) the area of B - A
//   (3) whether each p[i] is in the interior of B - A
//
// INPUT:
//   0 0 10 0 0 10
//   0 0 10 10 10 0
//   8 6
//   5 1
//
// OUTPUT:
//   The area is singular.
//   The area is 25.0
//   Point belongs to the area.
//   Point does not belong to the area.

import java.util.*;
import java.awt.geom.*;
import java.io.*;

public class JavaGeometry {

		// make an array of doubles from a string
		static double[] readPoints(String s) {
				String[] arr = s.trim().split("\\s++");
				double[] ret = new double[arr.length];
				for (int i = 0; i < arr.length; i++) ret[i] = Double.parseDouble(arr[i]);
				return ret;
		}

		// make an Area object from the coordinates of a polygon
		static Area makeArea(double[] pts) {
				Path2D.Double p = new Path2D.Double();
				p.moveTo(pts[0], pts[1]);
				for (int i = 2; i < pts.length; i += 2) p.lineTo(pts[i], pts[i+1]);
				p.closePath();
				return new Area(p);        
		}

		// compute area of polygon
		static double computePolygonArea(ArrayList<Point2D.Double> points) {
				Point2D.Double[] pts = points.toArray(new Point2D.Double[points.size()]);  
				double area = 0;
				for (int i = 0; i < pts.length; i++) {
						int j = (i+1) % pts.length;
						area += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
				}        
				return Math.abs(area)/2;
		}

		// compute the area of an Area object containing several disjoint polygons
		static double computeArea(Area area) {
				double totArea = 0;
				PathIterator iter = area.getPathIterator(null);
				ArrayList<Point2D.Double> points = new ArrayList<Point2D.Double>();

				while (!iter.isDone()) {
						double[] buffer = new double[6];
						switch (iter.currentSegment(buffer)) {
						case PathIterator.SEG_MOVETO:
						case PathIterator.SEG_LINETO:
								points.add(new Point2D.Double(buffer[0], buffer[1]));
								break;
						case PathIterator.SEG_CLOSE:
								totArea += computePolygonArea(points);
								points.clear();
								break;
						}
						iter.next();
				}
				return totArea;
		}

		// notice that the main() throws an Exception -- necessary to
		// avoid wrapping the Scanner object for file reading in a 
		// try { ... } catch block.
		public static void main(String args[]) throws Exception {

				Scanner scanner = new Scanner(new File("input.txt"));
				// also,
				//   Scanner scanner = new Scanner (System.in);

				double[] pointsA = readPoints(scanner.nextLine());
				double[] pointsB = readPoints(scanner.nextLine());
				Area areaA = makeArea(pointsA);
				Area areaB = makeArea(pointsB);
				areaB.subtract(areaA);
				// also,
				//   areaB.exclusiveOr (areaA);
				//   areaB.add (areaA);
				//   areaB.intersect (areaA);
				
				// (1) determine whether B - A is a single closed shape (as 
				//     opposed to multiple shapes)
				boolean isSingle = areaB.isSingular();
				// also,
				//   areaB.isEmpty();

				if (isSingle)
						System.out.println("The area is singular.");
				else
						System.out.println("The area is not singular.");
				
				// (2) compute the area of B - A
				System.out.println("The area is " + computeArea(areaB) + ".");
				
				// (3) determine whether each p[i] is in the interior of B - A
				while (scanner.hasNextDouble()) {
						double x = scanner.nextDouble();
						assert(scanner.hasNextDouble());
						double y = scanner.nextDouble();

						if (areaB.contains(x,y)) {
								System.out.println ("Point belongs to the area.");
						} else {
								System.out.println ("Point does not belong to the area.");
						}
				}

				// Finally, some useful things we didn't use in this example:
				//
				//   Ellipse2D.Double ellipse = new Ellipse2D.Double (double x, double y, 
				//                                                    double w, double h);
				//
				//     creates an ellipse inscribed in box with bottom-left corner (x,y)
				//     and upper-right corner (x+y,w+h)
				// 
				//   Rectangle2D.Double rect = new Rectangle2D.Double (double x, double y, 
				//                                                     double w, double h);
				//
				//     creates a box with bottom-left corner (x,y) and upper-right 
				//     corner (x+y,w+h)
				//
				// Each of these can be embedded in an Area object (e.g., new Area (rect)).

		}
}
$Geom3D

public class Geom3D {
	// distance from point (x, y, z) to plane aX + bY + cZ + d = 0
	public static double ptPlaneDist(double x, double y, double z,
			double a, double b, double c, double d) {
		return Math.abs(a*x + b*y + c*z + d) / Math.sqrt(a*a + b*b + c*c);
	}
	
	// distance between parallel planes aX + bY + cZ + d1 = 0 and
	// aX + bY + cZ + d2 = 0
	public static double planePlaneDist(double a, double b, double c,
			double d1, double d2) {
		return Math.abs(d1 - d2) / Math.sqrt(a*a + b*b + c*c);
	}
	
	// distance from point (px, py, pz) to line (x1, y1, z1)-(x2, y2, z2)
	// (or ray, or segment; in the case of the ray, the endpoint is the
	// first point)
	public static final int LINE = 0;
	public static final int SEGMENT = 1;
	public static final int RAY = 2;
	public static double ptLineDistSq(double x1, double y1, double z1,
			double x2, double y2, double z2, double px, double py, double pz,
			int type) {
		double pd2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
		
		double x, y, z;
		if (pd2 == 0) {
			x = x1;
			y = y1;
			z = z1;
		} else {
			double u = ((px-x1)*(x2-x1) + (py-y1)*(y2-y1) + (pz-z1)*(z2-z1)) / pd2;
			x = x1 + u * (x2 - x1);
			y = y1 + u * (y2 - y1);
			z = z1 + u * (z2 - z1);
			if (type != LINE && u < 0) {
				x = x1;
				y = y1;
				z = z1;
			}
			if (type == SEGMENT && u > 1.0) {
				x = x2;
				y = y2;
				z = z2;
			}
		}
		
		return (x-px)*(x-px) + (y-py)*(y-py) + (z-pz)*(z-pz);
	}
	
	public static double ptLineDist(double x1, double y1, double z1,
			double x2, double y2, double z2, double px, double py, double pz,
			int type) {
		return Math.sqrt(ptLineDistSq(x1, y1, z1, x2, y2, z2, px, py, pz, type));
	}
}
$Delaunay

// Slow but simple Delaunay triangulation. Does not handle
// degenerate cases (from O'Rourke, Computational Geometry in C)
//
// Running time: O(n^4)
//
// INPUT:    x[] = x-coordinates
//           y[] = y-coordinates
//
// OUTPUT:   triples = a vector containing m triples of indices
//                     corresponding to triangle vertices

#include<vector>
using namespace std;

typedef double T;

struct triple {
	int i, j, k;
	triple() {}
	triple(int i, int j, int k) : i(i), j(j), k(k) {}
};

vector<triple> delaunayTriangulation(vector<T>& x, vector<T>& y) {
	int n = x.size();
	vector<T> z(n);
	vector<triple> ret;

	for (int i = 0; i < n; i++)
			z[i] = x[i] * x[i] + y[i] * y[i];

	for (int i = 0; i < n-2; i++) {
			for (int j = i+1; j < n; j++) {
				for (int k = i+1; k < n; k++) {
						if (j == k) continue;
						double xn = (y[j]-y[i])*(z[k]-z[i]) - (y[k]-y[i])*(z[j]-z[i]);
						double yn = (x[k]-x[i])*(z[j]-z[i]) - (x[j]-x[i])*(z[k]-z[i]);
						double zn = (x[j]-x[i])*(y[k]-y[i]) - (x[k]-x[i])*(y[j]-y[i]);
						bool flag = zn < 0;
						for (int m = 0; flag && m < n; m++)
						flag = flag && ((x[m]-x[i])*xn + (y[m]-y[i])*yn + (z[m]-z[i])*zn <= 0);
						if (flag) ret.push_back(triple(i, j, k));
				}
			}
	}
	return ret;
}

int main() {
	T xs[]={0, 0, 1, 0.9};
	T ys[]={0, 1, 0, 0.9};
	vector<T> x(&xs[0], &xs[4]), y(&ys[0], &ys[4]);
	vector<triple> tri = delaunayTriangulation(x, y);
	
	//expected: 0 1 3
	//          0 3 2
	
	int i;
	for(i = 0; i < tri.size(); i++)
		printf("%d %d %d\n", tri[i].i, tri[i].j, tri[i].k);
	return 0;
}

$Simplex

// Two-phase simplex algorithm for solving linear programs of the form
//
//     maximize     c^T x
//     subject to   Ax <= b
//                  x >= 0
//
// INPUT: A -- an m x n matrix
//        b -- an m-dimensional vector
//        c -- an n-dimensional vector
//        x -- a vector where the optimal solution will be stored
//
// OUTPUT: value of the optimal solution (infinity if unbounded
//         above, nan if infeasible)
//
// To use this code, create an LPSolver object with A, b, and c as
// arguments.  Then, call Solve(x).

#include <limits>

typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct LPSolver {
	int m, n;
	VI B, N;
	VVD D;

	LPSolver(const VVD &A, const VD &b, const VD &c) : 
		m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, VD(n+2)) {
		for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
		for (int i = 0; i < m; i++) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i]; }
		for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1; D[m+1][n] = 1;
	}
			 
	void Pivot(int r, int s) {
		for (int i = 0; i < m+2; i++) if (i != r)
			for (int j = 0; j < n+2; j++) if (j != s)
		D[i][j] -= D[r][j] * D[i][s] / D[r][s];
		for (int j = 0; j < n+2; j++) if (j != s) D[r][j] /= D[r][s];
		for (int i = 0; i < m+2; i++) if (i != r) D[i][s] /= -D[r][s];
		D[r][s] = 1.0 / D[r][s];
		swap(B[r], N[s]);
	}

	bool Simplex(int phase) {
		int x = phase == 1 ? m+1 : m;
		while (true) {
			int s = -1;
			for (int j = 0; j <= n; j++) {
		if (phase == 2 && N[j] == -1) continue;
		if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
			}
			if (D[x][s] >= -EPS) return true;
			int r = -1;
			for (int i = 0; i < m; i++) {
		if (D[i][s] <= 0) continue;
		if (r == -1 || D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s] ||
				D[i][n+1] / D[i][s] == D[r][n+1] / D[r][s] && B[i] < B[r]) r = i;
			}
			if (r == -1) return false;
			Pivot(r, s);
		}
	}

	DOUBLE Solve(VD &x) {
		int r = 0;
		for (int i = 1; i < m; i++) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] <= -EPS) {
			Pivot(r, n);
			if (!Simplex(1) || D[m+1][n+1] < -EPS) return -numeric_limits<DOUBLE>::infinity();
			for (int i = 0; i < m; i++) if (B[i] == -1) {
		int s = -1;
		for (int j = 0; j <= n; j++) 
			if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
		Pivot(i, s);
			}
		}
		if (!Simplex(2)) return numeric_limits<DOUBLE>::infinity();
		x = VD(n);
		for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n+1];
		return D[m][n+1];
	}
};

int main() {
	const int m = 4;
	const int n = 3;  
	DOUBLE _A[m][n] = {
		{ 6, -1, 0 },
		{ -1, -5, 0 },
		{ 1, 5, 1 },
		{ -1, -5, -1 }
	};
	DOUBLE _b[m] = { 10, -4, 5, -5 };
	DOUBLE _c[n] = { 1, -1, 0 };
	
	VVD A(m);
	VD b(_b, _b + m);
	VD c(_c, _c + n);
	for (int i = 0; i < m; i++) A[i] = VD(_A[i], _A[i] + n);

	LPSolver solver(A, b, c);
	VD x;
	DOUBLE value = solver.Solve(x);
	
	cerr << "VALUE: "<< value << endl;
	cerr << "SOLUTION:";
	for (size_t i = 0; i < x.size(); i++) cerr << " " << x[i];
	cerr << endl;
	return 0;
}

$KDTree
//  - constructs from n points in O(n lg^2 n) time
//  - handles nearest-neighbor query in O(lg n) if points are well distributed
//  - worst case for nearest-neighbor may be linear in pathological case
// --------------------------------------------------------------------------

#include <limits>

// number type for coordinates, and its maximum value
typedef long long ntype;
const ntype sentry = numeric_limits<ntype>::max();

// point structure for 2D-tree, can be extended to 3D
struct point {
	ntype x, y;
	point(ntype xx = 0, ntype yy = 0) : x(xx), y(yy) {}
};

bool operator==(const point &a, const point &b) {
	return a.x == b.x && a.y == b.y;
}

// sorts points on x-coordinate
bool on_x(const point &a, const point &b) {
	return a.x < b.x;
}

// sorts points on y-coordinate
bool on_y(const point &a, const point &b) {
	return a.y < b.y;
}

// squared distance between points
ntype pdist2(const point &a, const point &b) {
	ntype dx = a.x-b.x, dy = a.y-b.y;
	return dx*dx + dy*dy;
}

// bounding box for a set of points
struct bbox{
	ntype x0, x1, y0, y1;
	
	bbox() : x0(sentry), x1(-sentry), y0(sentry), y1(-sentry) {}
	
	// computes bounding box from a bunch of points
	void compute(const vector<point> &v) {
		for (int i = 0; i < v.size(); ++i) {
			x0 = min(x0, v[i].x);   x1 = max(x1, v[i].x);
			y0 = min(y0, v[i].y);   y1 = max(y1, v[i].y);
		}
	}
	
	// squared distance between a point and this bbox, 0 if inside
	ntype distance(const point &p) {
		if (p.x < x0) {
			if (p.y < y0)       return pdist2(point(x0, y0), p);
			else if (p.y > y1)  return pdist2(point(x0, y1), p);
			else                return pdist2(point(x0, p.y), p);
		}
		else if (p.x > x1) {
			if (p.y < y0)       return pdist2(point(x1, y0), p);
			else if (p.y > y1)  return pdist2(point(x1, y1), p);
			else                return pdist2(point(x1, p.y), p);
		}
		else {
			if (p.y < y0)       return pdist2(point(p.x, y0), p);
			else if (p.y > y1)  return pdist2(point(p.x, y1), p);
			else                return 0;
		}
	}
};

// stores a single node of the kd-tree, either internal or leaf
struct kdnode {
	bool leaf;      // true if this is a leaf node (has one point)
	point pt;       // the single point of this is a leaf
	bbox bound;     // bounding box for set of points in children
	
	kdnode *first, *second; // two children of this kd-node
	
	kdnode() : leaf(false), first(0), second(0) {}
	~kdnode() { if (first) delete first; if (second) delete second; }
	
	// intersect a point with this node (returns squared distance)
	ntype intersect(const point &p) {
		return bound.distance(p);
	}
	
	// recursively builds a kd-tree from a given cloud of points
	void construct(vector<point> &vp)
	{
		// compute bounding box for points at this node
		bound.compute(vp);
		
		// if we're down to one point, then we're a leaf node
		if (vp.size() == 1) {
				leaf = true;
				pt = vp[0];
		}
		else {
			// split on x if the bbox is wider than high (not best heuristic...)
			if (bound.x1-bound.x0 >= bound.y1-bound.y0)
				sort(vp.begin(), vp.end(), on_x);
			// otherwise split on y-coordinate
			else
				sort(vp.begin(), vp.end(), on_y);
			// divide by taking half the array for each child
			// (not best performance if many duplicates in the middle)
			int half = vp.size()/2;
			vector<point> vl(vp.begin(), vp.begin()+half);
			vector<point> vr(vp.begin()+half, vp.end());
			first = new kdnode();   first->construct(vl);
			second = new kdnode();  second->construct(vr);            
		}
	}
};

// simple kd-tree class to hold the tree and handle queries
struct kdtree{
	kdnode *root;
	
	// constructs a kd-tree from a points (copied here, as it sorts them)
	kdtree(const vector<point> &vp) {
		vector<point> v(vp.begin(), vp.end());
		root = new kdnode();
		root->construct(v);
	}
	~kdtree() { delete root; }
	
	// recursive search method returns squared distance to nearest point
	ntype search(kdnode *node, const point &p)
	{
		if (node->leaf) {
			// commented special case tells a point not to find itself
//            if (p == node->pt) return sentry;
//            else               
				return pdist2(p, node->pt);
		}
		
		ntype bfirst = node->first->intersect(p);
		ntype bsecond = node->second->intersect(p);
		
		// choose the side with the closest bounding box to search first
		// (note that the other side is also searched if needed)
		if (bfirst < bsecond) {
			ntype best = search(node->first, p);
			if (bsecond < best)
				best = min(best, search(node->second, p));
			return best;
		}
		else {
			ntype best = search(node->second, p);
			if (bfirst < best)
				best = min(best, search(node->first, p));
			return best;
		}
	}
	
	// squared distance to the nearest 
	ntype nearest(const point &p) {
		return search(root, p);
	}
};

// --------------------------------------------------------------------------
// some basic test code here

int main() {
		// generate some random points for a kd-tree
		vector<point> vp;
		for (int i = 0; i < 100000; ++i) {
				vp.push_back(point(rand()%100000, rand()%100000));
		}
		kdtree tree(vp);
		
		// query some points
		for (int i = 0; i < 10; ++i) {
				point q(rand()%100000, rand()%100000);
				cout << "Closest squared distance to (" << q.x << ", " << q.y << ")"
						 << " is " << tree.nearest(q) << endl;
		}    

		return 0;
}

// --------------------------------------------------------------------------
$LogLan

// Code which demonstrates the use of Java's regular expression libraries.
// This is a solution for 
//
//   Loglan: a logical language
//   http://acm.uva.es/p/v1/134.html
//
// In this problem, we are given a regular language, whose rules can be
// inferred directly from the code.  For each sentence in the input, we must
// determine whether the sentence matches the regular expression or not.  The
// code consists of (1) building the regular expression (which is fairly
// complex) and (2) using the regex to match sentences.

import java.util.*;
import java.util.regex.*;

public class LogLan {

	public static String BuildRegex () {
		String space = " +";

		String A = "([aeiou])";
		String C = "([a-z&&[^aeiou]])";
		String MOD = "(g" + A + ")";
		String BA = "(b" + A + ")";
		String DA = "(d" + A + ")";
		String LA = "(l" + A + ")";
		String NAM = "([a-z]*" + C + ")";
		String PREDA = "(" + C + C + A + C + A + "|" + C + A + C + C + A + ")";

		String predstring = "(" + PREDA + "(" + space + PREDA + ")*)";
		String predname = "(" + LA + space + predstring + "|" + NAM + ")";
		String preds = "(" + predstring + "(" + space + A + space + predstring + ")*)";
		String predclaim = "(" + predname + space + BA + space + preds + "|" + DA + space +
						preds + ")";
		String verbpred = "(" + MOD + space + predstring + ")";
		String statement = "(" + predname + space + verbpred + space + predname + "|" + 
						predname + space + verbpred + ")";
		String sentence = "(" + statement + "|" + predclaim + ")";

		return "^" + sentence + "$";
		}

		public static void main (String args[]) {

		String regex = BuildRegex();
		Pattern pattern = Pattern.compile (regex);
		
		Scanner s = new Scanner(System.in);
		while (true) {

			// In this problem, each sentence consists of multiple lines, where the last 
			// line is terminated by a period.  The code below reads lines until
			// encountering a line whose final character is a '.'.  Note the use of
			//
			//    s.length() to get length of string
			//    s.charAt() to extract characters from a Java string
			//    s.trim() to remove whitespace from the beginning and end of Java string
			//
			// Other useful String manipulation methods include
			//
			//    s.compareTo(t) < 0 if s < t, lexicographically
			//    s.indexOf("apple") returns index of first occurrence of "apple" in s
			//    s.lastIndexOf("apple") returns index of last occurrence of "apple" in s
			//    s.replace(c,d) replaces occurrences of character c with d
			//    s.startsWith("apple) returns (s.indexOf("apple") == 0)
			//    s.toLowerCase() / s.toUpperCase() returns a new lower/uppercased string
			//
			//    Integer.parseInt(s) converts s to an integer (32-bit)
			//    Long.parseLong(s) converts s to a long (64-bit)
			//    Double.parseDouble(s) converts s to a double
					
			String sentence = "";
			while (true) {
				sentence = (sentence + " " + s.nextLine()).trim();
				if (sentence.equals("#")) return;
				if (sentence.charAt(sentence.length()-1) == '.') break;     
			}

			// now, we remove the period, and match the regular expression
			String removed_period = sentence.substring(0, sentence.length()-1).trim();
			if (pattern.matcher (removed_period).find()) {
				System.out.println ("Good");
			} else {
				System.out.println ("Bad!");
			}
		}
	}
}
$IO

int main() {
	// Ouput a specific number of digits past the decimal point,
	// in this case 5    
	cout.setf(ios::fixed); cout << setprecision(5);
	cout << 100.0/7.0 << endl;
	cout.unsetf(ios::fixed);
	
	// Output the decimal point and trailing zeros
	cout.setf(ios::showpoint);
	cout << 100.0 << endl;
	cout.unsetf(ios::showpoint);
	
	// Output a '+' before positive values
	cout.setf(ios::showpos);
	cout << 100 << " " << -100 << endl;
	cout.unsetf(ios::showpos);
	
	// Output numerical values in hexadecimal
	cout << hex << 100 << " " << 1000 << " " << 10000 << dec << endl;
}
$LatLong

/*
Converts from rectangular coordinates to latitude/longitude and vice
versa. Uses degrees (not radians).
*/

#include <iostream>
#include <cmath>

using namespace std;

struct ll{
	double r, lat, lon;
};

struct rect{
	double x, y, z;
};

ll convert(rect& P) {
	ll Q;
	Q.r = sqrt(P.x*P.x+P.y*P.y+P.z*P.z);
	Q.lat = 180/M_PI*asin(P.z/Q.r);
	Q.lon = 180/M_PI*acos(P.x/sqrt(P.x*P.x+P.y*P.y));
	
	return Q;
}

rect convert(ll& Q) {
	rect P;
	P.x = Q.r*cos(Q.lon*M_PI/180)*cos(Q.lat*M_PI/180);
	P.y = Q.r*sin(Q.lon*M_PI/180)*cos(Q.lat*M_PI/180);
	P.z = Q.r*sin(Q.lat*M_PI/180);
	
	return P;
}

int main() {
	rect A;
	ll B;
	
	A.x = -1.0; A.y = 2.0; A.z = -3.0;
	
	B = convert(A);
	cout << B.r << " " << B.lat << " " << B.lon << endl;
	
	A = convert(B);
	cout << A.x << " " << A.y << " " << A.z << endl;
}

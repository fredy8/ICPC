/*
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct MaxSparseTable {
	vi A; vvi M;
	int log2(int n) { int i=0; while(n >>= 1) i++; return i; }
	MaxSparseTable(vi arr) { //O(NlogN)
		int N = arr.size();
		A.assign(N, 0);
		M.assign(N, vi(log2(N)+1));
		int i, j;
		for(i=0; i<N; i++)
			M[i][0] = i, A[i] = arr[i];

		for(j=1; 1<<j <= N; j++)
			for(i=0; i + (1<<j) - 1 < N; i++)
				if(A[M[i][j - 1]] > A[M[i + (1 << (j - 1))][j - 1]])
					M[i][j] = M[i][j - 1];
				else
					M[i][j] = M[i + (1 << (j - 1))][j - 1];
	}
	//returns the index of the minimum value
	int query(int i, int j) {
		if(i > j) swap(i, j);
		int k = log2(j-i+1);
		if(A[M[i][k]] > A[M[j-(1 << k)+1][k]])
			return M[i][k];
		return M[j-(1 << k)+1][k];
	}
};

struct SparseTable {
	vi A; vvi M;
	int log2(int n) { int i=0; while(n >>= 1) i++; return i; }
	SparseTable(vi arr) { //O(NlogN)
		int N = arr.size();
		A.assign(N, 0);
		M.assign(N, vi(log2(N)+1));
		int i, j;
		for(i=0; i<N; i++)
			M[i][0] = i, A[i] = arr[i];

		for(j=1; 1<<j <= N; j++)
			for(i=0; i + (1<<j) - 1 < N; i++)
				if(A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
					M[i][j] = M[i][j - 1];
				else
					M[i][j] = M[i + (1 << (j - 1))][j - 1];
	}
	//returns the index of the minimum value
	int query(int i, int j) {
		if(i > j) swap(i, j);
		int k = log2(j-i+1);
		if(A[M[i][k]] < A[M[j-(1 << k)+1][k]])
			return M[i][k];
		return M[j-(1 << k)+1][k];
	}
};

struct Edge {
	int to, weight;
	int backEdge, strong, type, visited; //optional
	Edge(int to, int weight = 1) : to(to), weight(weight), strong(0), visited(0) {}
};
struct Graph {
	int V; bool undirected;
	vector<vector<Edge> > edges;
	Graph(int v, bool undirected) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
	void connect(int from, Edge edge) {
		edges[from].pb(edge);
		if(undirected) {
			int aux = edge.to;
			edge.to = from;
			edges[aux].pb(edge);
			edges[from].back().backEdge = edges[aux].size() - 1; //optional
			edges[aux].back().backEdge = edges[from].size() - 1; //optional
		}
	}
};

struct LCA {
	vi order, height, index;
	SparseTable *st;
	LCA(Graph &g, int root) {
		index.assign(g.V, -1);
		dfs(g, root, 0, index);
		st = new SparseTable(height);
	}
	~LCA() { delete st; }
	void dfs(Graph &g, int cv, int h, vi &index) {
		index[cv] = order.size();
		order.pb(cv), height.pb(h);
		FORC(g.edges[cv], edge)
			if(index[edge->to] == -1) {
				dfs(g, edge->to, height.back() + edge->weight, index);
				order.pb(cv), height.pb(h);
			}
	}
	int query(int i, int j) { return order[st->query(index[i], index[j])]; }
	int distance(int i, int j) { return height[index[i]] + height[index[j]] - 2*(height[index[query(i, j)]]); }
};

struct HeavyLightDecomposition {
	vector<vi> lists;
	vi values, listIndex, posIndex, parent, treeSizes;
	vector<SparseTable> sts;
	LCA *lca;
	HeavyLightDecomposition(Graph &g/*undirected connected acyclic*/, vi values) : values(values) {
		lca = new LCA(g, 0);
		listIndex = posIndex = parent = treeSizes = vi(g.V, -1);
		getTreeSizes(g, 0);
		makeLists(g, 0, -1);
		FORC(lists, list) {
			vi v;
			FORC(*list, it) v.pb(values[*it]);
			sts.pb(SparseTable(v));
		}
	}
	~HeavyLightDecomposition() { delete lca; }
	int getTreeSizes(Graph &g, int cv) {
		treeSizes[cv] = 1;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
				parent[edge->to] = cv, treeSizes[cv] += getTreeSizes(g, edge->to);  
		return treeSizes[cv];
	}
	void makeLists(Graph &g, int cv, int listNum) {
		if(listNum == -1)
			listNum = lists.size(), lists.pb(vi());
		listIndex[cv] = listNum;
		posIndex[cv] = lists[listNum].size();
		lists[listNum].pb(cv);
		int MAX = -1;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
			if(MAX == -1 || treeSizes[edge->to] > treeSizes[MAX]) MAX = edge->to;
		FORC(g.edges[cv], edge) if(edge->to != parent[cv])
			makeLists(g, edge->to, edge->to == MAX ? listNum : -1);	
	}
	int query(int from, int to) {
		int anc = lca->query(from, to), posLeft, posRight;
		int result = min(queryToAncestor(from, anc, posLeft), queryToAncestor(to, anc, posRight));
		if(posLeft < posRight) swap(posLeft, posRight);
		result = min(result, values[lists[listIndex[anc]][sts[listIndex[anc]].query(posIndex[anc], posRight)]]);
		if(posRight != posLeft)
			result = min(result, values[lists[listIndex[anc]][sts[listIndex[anc]].query(posRight+1, posLeft)]]);
		return result;
	}
	int queryToAncestor(int from, int anc, int &posInAncestorList) {
		int result = INF, left = from;
		while(listIndex[left] != listIndex[anc]) {
			result = min(result, values[lists[listIndex[left]][sts[listIndex[left]].query(0, posIndex[left])]]);
			int head = lists[listIndex[left]][0];
			left = parent[lists[listIndex[left]][0]];
		}
		posInAncestorList = posIndex[left];
		return result;
	}
};


mint main() {
	Graph g(23, true);
	g.connect(0, Edge(1));
	g.connect(0, Edge(2));
	g.connect(0, Edge(3));
	g.connect(0, Edge(4));
	g.connect(1, Edge(5));
	g.connect(1, Edge(6));
	g.connect(1, Edge(7));
	g.connect(1, Edge(8));
	g.connect(2, Edge(9));
	g.connect(3, Edge(10));
	g.connect(5, Edge(11));
	g.connect(7, Edge(12));
	g.connect(7, Edge(13));
	g.connect(8, Edge(14));
	g.connect(8, Edge(15));
	g.connect(12, Edge(16));
	g.connect(13, Edge(17));
	g.connect(13, Edge(18));
	g.connect(14, Edge(19));
	g.connect(15, Edge(20));
	g.connect(15, Edge(21));
	g.connect(20, Edge(22));
	
	int values[] = { 23, 17, 2, 2, 1 , 2, 1, 6, 7, 1, 1, 1, 2, 3, 2, 4, 1, 1, 1, 1, 2, 1, 2 };
	HeavyLightDecomposition HLD(g, vi(values, values+23));
	cout << HLD.query(0, 8) << endl;
}

#include <iostream>
#include <vector>

using namespace std;

struct UnionFindDS {
	vector<int> tree;
	UnionFindDS(int n) { for(int i = 0; i < n; i++) tree.push_back(i); }
	int root(int i) { return tree[i] == i ? i : tree[i] = root(tree[i]); }
	bool connected(int i, int j) {return root(i) == root(j);}
	void connect(int i, int j) { tree[root(i)] = tree[root(j)]; }
};

class Edge {
	public:
	int from, to, weight;
	Edge(int from, int to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}
};

vector<Edge> Boruvka(int N, vector<Edge> graph) {
	UnionFindDS ds(N);
	vector<Edge> minSpanningTree;
	int connections = 0;

	// Todo arbol tiene N-1 edges
	while(connections != N-1) {
		int cheapestEdgeOfComponent[N];
		for (int i = 0; i < N; i++)
			cheapestEdgeOfComponent[i] = -1;

		for (int i = 0; i < graph.size(); i++) {
			int from = graph[i].from;
			int to = graph[i].to;
			int weight = graph[i].weight;

			if (!ds.connected(from, to)) {
				int componentIndex1 = ds.root(from);
				int cheapestEdgeIndex1 = cheapestEdgeOfComponent[componentIndex1];
				if (cheapestEdgeIndex1 == -1 || weight < graph[cheapestEdgeIndex1].weight)
					cheapestEdgeOfComponent[componentIndex1] = i;
				
				int componentIndex2 = ds.root(to);
				int cheapestEdgeIndex2 = cheapestEdgeOfComponent[componentIndex2];
				if (cheapestEdgeIndex2 == -1 || weight < graph[cheapestEdgeIndex2].weight)
					cheapestEdgeOfComponent[componentIndex2] = i;
			}
		}

		for (int i = 0; i < N; i++)
			if (cheapestEdgeOfComponent[i] != -1) {
				int edgeIndex = cheapestEdgeOfComponent[i];
				if (!ds.connected(graph[edgeIndex].from, graph[edgeIndex].to)) {
					connections++;
					ds.connect(graph[edgeIndex].from, graph[edgeIndex].to);
					minSpanningTree.push_back(graph[edgeIndex]);
				}
			}
	}

	return minSpanningTree;
}

int main() {
	int N = 7;
	Edge graph[] = {
		Edge(0, 1, 7),
		Edge(0, 3, 4),
		Edge(1, 2, 11),
		Edge(1, 3, 9),
		Edge(1, 4, 10),
		Edge(2, 4, 5),
		Edge(3, 4, 15),
		Edge(3, 5, 6),
		Edge(4, 5, 12),
		Edge(4, 6, 8),
		Edge(5, 6, 13)
	};

	vector<Edge> minSpanningTree = Boruvka(7, vector<Edge>(graph, graph+11));
	for(int i = 0; i < minSpanningTree.size(); i++) {
		cout << minSpanningTree[i].from << " " << minSpanningTree[i].to << endl;
	}
}
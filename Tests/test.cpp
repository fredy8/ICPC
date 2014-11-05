#define CATCH_CONFIG_MAIN
#include "catch.h"

#include "Utility/header.h"

#include "Data_Structures/interval_tree_sb.h"
TEST_CASE("Balanced Interval Tree") {
	IntervalSplayTree<int> st;
	REQUIRE(!st.contains(ii(4,5)));
	st.insert(ii(4,5));
	REQUIRE(st.contains(ii(4,5)));
	st.insert(ii(2,2));
	st.insert(ii(8,15));
	st.insert(ii(1,4));
	st.insert(ii(14,20));
	REQUIRE(!st.overlaps(ii(6,7)));
	REQUIRE(st.overlaps(ii(6,8)));
	REQUIRE(st.overlaps(ii(15,15)));
	st.erase(ii(1,4));
	REQUIRE(!st.overlaps(ii(3,3)));
    REQUIRE(st.overlaps(ii(-90, 90)));
}

#include "Algorithms/Sorting/quicksort.h"
TEST_CASE("quicksort") {
	int arr[10] = { 4, -2, 3, 0, 5, 2, 8, -9, 3, 7 };
	int sorted[10] = { -9, -2, 0, 2, 3, 3, 4, 5, 7, 8 };
	quickSort(arr, 0, 9);
	for(int i = 0; i < 10; i++)
		REQUIRE(arr[i] == sorted[i]);
}

#include "Algorithms/Sorting/mergesort.h"
TEST_CASE("mergesort") {
	int arr[10] = { 4, -2, 3, 0, 5, 2, 8, -9, 3, 7 };
	int sorted[10] = { -9, -2, 0, 2, 3, 3, 4, 5, 7, 8 };
	int inversions = mergeSort(arr, 0, 9);
	FOR(i, 0, 10)
		REQUIRE(arr[i] == sorted[i]);
	REQUIRE(inversions == 18);
}

#include "Algorithms/Search/binary_search.h"
TEST_CASE("binarySearch") {
	int sorted[10] = { -9, -2, 0, 2, 3, 3, 4, 5, 7, 8 };
	REQUIRE(binarySearch(sorted, 4, 0, 9) == 6);
	REQUIRE(binarySearch(sorted, -1, 0, 9) == -1);
	REQUIRE(binarySearch(sorted, 3, 0, 9, UPPERBOUND) == 5);
	REQUIRE(binarySearch(sorted, 3, 0, 9, LOWERBOUND) == 4);
}

#include "Algorithms/Ad_hoc/maximum_subarray.h"
TEST_CASE("maximumSubarray") {
	int arr[10] = { 4, -2, 3, 0, 5, 2, 8, -9, 3, -7 };
	REQUIRE(maximumSubarray(arr, 10) == 20);
	REQUIRE(maximumSubarray(arr+1, 1) == -2);
}

#include "Algorithms/Ad_hoc/range_or.h"
TEST_CASE("rangeOr") {
	REQUIRE(rangeOR(2, 6) == (2 | 3 | 4 | 5 | 6));
}

#include "Algorithms/Ad_hoc/dates.h"
TEST_CASE("dates") {
	int dayDif = toJulian(21, 10, 2014) - toJulian(5, 2, 1994);
	REQUIRE(dayDif == 7563);
	int dayOfWeek = toJulian(5, 2, 1994)%7;
	REQUIRE(dayOfWeek == 5);
	REQUIRE(isLeap(2000) == true);
	REQUIRE(isLeap(1900) == false);
	REQUIRE(isLeap(1996) == true);
	REQUIRE(isLeap(1995) == false);
	int d, m, y;
	toGregorian(toJulian(5, 2, 1994) + 7563, d, m, y);
	REQUIRE(d == 21);
	REQUIRE(m == 10);
	REQUIRE(y == 2014);
}

#include "Algorithms/Ad_hoc/bit_manipulation.h"
TEST_CASE("bitManipulation") {
	REQUIRE(turnOffLastBit(6) == 4);
	REQUIRE(turnOnLastZero(6) == 7);
	REQUIRE(turnOffLastConsecutiveBits(7) == 0);
	REQUIRE(turnOnLastConsecutiveZeroes(8) == 15);
	REQUIRE(MSB(39) == 32);
}

#include "Algorithms/Ad_hoc/base_conversions.h"
TEST_CASE("baseConversions") {
	REQUIRE(toBaseN(12, 8) == "14");
	REQUIRE(toBaseN(0, 8) == "0");
	REQUIRE(toBaseN(254, 16) == "FE");
}

#include "Data_Structures/lists_graph.h"
TEST_CASE("lists graph") {
	Graph g(4, true);
	g.connect(1, Edge(3, 2));
	g.connect(1, Edge(2, 5));
	ii expected[2] = { ii(3, 2), ii(2, 5) };
	int i = 0;
	REQUIRE(g.edges[1].size() == 2);
	FORC(g.edges[1], edge) {
		REQUIRE(edge->to == expected[i].first);
		REQUIRE(edge->weight == expected[i++].second);
	}

	REQUIRE(g.edges[expected[0].first].size() == 1);
	REQUIRE(g.edges[expected[0].first][0].to == 1);
	REQUIRE(g.edges[expected[0].first][0].weight == expected[0].second);

	Graph g2(4, false);
	g2.connect(1, Edge(3, 2));
	g2.connect(1, Edge(2, 5));
	i = 0;
	REQUIRE(g2.edges[1].size() == 2);
	FORC(g2.edges[1], edge) {
		REQUIRE(edge->to == expected[i].first);
		REQUIRE(edge->weight == expected[i++].second);
	}

	REQUIRE(g2.edges[expected[0].first].size() == 0);
	REQUIRE(g2.edges[expected[1].first].size() == 0);
}

#include "Algorithms/Graphs/articulation_points_and_bridges.h"
TEST_CASE("Articulation Points and Bridges") {
	Graph g(5, true);
	g.connect(0, Edge(1));
	g.connect(1, Edge(2));
	g.connect(2, Edge(3));
	g.connect(0, Edge(2));
	g.connect(3, Edge(4));
	vi strongPoints = articulationPointsAndBridges(g);
	REQUIRE(strongPoints[0] == false);
	REQUIRE(strongPoints[1] == false);
	REQUIRE(strongPoints[2] == true);
	REQUIRE(strongPoints[3] == true);
	REQUIRE(strongPoints[4] == false);

	REQUIRE(g.edges[0][0].strong == false);
	REQUIRE(g.edges[0][1].strong == false);
	REQUIRE(g.edges[1][0].strong == false);
	REQUIRE(g.edges[1][1].strong == false);
	REQUIRE(g.edges[2][0].strong == false);
	REQUIRE(g.edges[2][1].strong == true);
	REQUIRE(g.edges[2][2].strong == false);
	REQUIRE(g.edges[3][0].strong == true);
	REQUIRE(g.edges[3][1].strong == true);
	REQUIRE(g.edges[4][0].strong == true);
}

#include "Data_Structures/union_find_disjoint_sets.h"
TEST_CASE("Union Find Disjoint Sets") {
	UnionFindDS ds(4);
	REQUIRE(ds.connected(0, 1) == false);
	ds.connect(0, 2);
	REQUIRE(ds.connected(0, 2) == true);
	ds.connect(2, 1);
	REQUIRE(ds.connected(0, 1) == true);
	REQUIRE(ds.connected(2, 1) == true);
	REQUIRE(ds.connected(0, 3) == false);

	UnionFindDS2 ds2(4);
	ds2.connect(0, 2);
	ds2.connect(2, 1);
	REQUIRE(ds2.countSets() == 2);
	REQUIRE(ds2.getSize(0) == 3);
	REQUIRE(ds2.getSize(2) == 3);
	REQUIRE(ds2.getSize(3) == 1);
}

#include "Algorithms/Graphs/bellman_ford.h"
TEST_CASE("Bellman Ford") {
	Graph g(5, false);
	g.connect(0, Edge(1, 5));
	g.connect(1, Edge(4, 1));
	g.connect(0, Edge(2, 1));
	g.connect(2, Edge(3, 8));
	g.connect(3, Edge(4, -4));

	bool negCycle;
	vi dist = bellmanFord(g, 0, negCycle);
	REQUIRE(dist[0] == 0);
	REQUIRE(dist[1] == 5);
	REQUIRE(dist[2] == 1);
	REQUIRE(dist[3] == 9);
	REQUIRE(dist[4] == 5);

	Graph g2(5, true);
	g2.connect(0, Edge(1, -5));
	g2.connect(1, Edge(4, -1));
	g2.connect(0, Edge(2, -1));
	g2.connect(2, Edge(3, -8));
	g2.connect(3, Edge(4, -4));

	dist = bellmanFord(g2, 0, negCycle);
	REQUIRE(negCycle == true);
}

#include "Algorithms/Graphs/Dijkstra.h"
TEST_CASE("Dijkstra") {
	Graph g(5, true);
	g.connect(0, Edge(1, 5));
	g.connect(1, Edge(4, 2));
	g.connect(0, Edge(2, 1));
	g.connect(2, Edge(3, 1));
	g.connect(3, Edge(4, 4));

	vi dist = dijkstra(g, 0);
	REQUIRE(dist[0] == 0);
	REQUIRE(dist[1] == 5);
	REQUIRE(dist[2] == 1);
	REQUIRE(dist[3] == 2);
	REQUIRE(dist[4] == 6);
}

#include "Algorithms/Graphs/DAGs/topological_sort.h"
TEST_CASE("Topological Sort") {
	Graph g(8, false);
	g.connect(0, Edge(1));
	g.connect(0, Edge(4));
	g.connect(3, Edge(1));
	g.connect(6, Edge(4));
	g.connect(6, Edge(7));
	g.connect(1, Edge(2));
	g.connect(1, Edge(5));
	g.connect(4, Edge(5));
	vi ts = topologicalSort(g);
	#define find(a) (find(ts.begin(), ts.end(), (a)))
	REQUIRE(find(0) < find(1));
	REQUIRE(find(0) < find(4));
	REQUIRE(find(3) < find(1));
	REQUIRE(find(6) < find(1));
	REQUIRE(find(6) < find(7));
	REQUIRE(find(1) < find(2));
	REQUIRE(find(1) < find(7));
	REQUIRE(find(4) < find(5));
	#undef find
}

#include "Algorithms/Graphs/DAGs/shortest-longest_path.h"
TEST_CASE("Shortest Path in a DAG") {
	Graph g(8, false);
	g.connect(0, Edge(1));
	g.connect(0, Edge(4));
	g.connect(3, Edge(1));
	g.connect(6, Edge(4));
	g.connect(6, Edge(7));
	g.connect(1, Edge(2));
	g.connect(1, Edge(5));
	g.connect(4, Edge(5));
	vi distance = shortestPath(g);
	REQUIRE(distance[0] == 0);
	REQUIRE(distance[1] == 1);
	REQUIRE(distance[2] == 2);
	REQUIRE(distance[3] == 0);
	REQUIRE(distance[4] == 1);
	REQUIRE(distance[5] == 2);
	REQUIRE(distance[6] == 0);
	REQUIRE(distance[7] == 1);
}

#include "Algorithms/Graphs/eulerian_path.h"
TEST_CASE("Eulerian Path") {
	Graph g(6, true);
	g.connect(0, Edge(2));
	g.connect(0, Edge(3));
	g.connect(1, Edge(2));
	g.connect(1, Edge(3));
	g.connect(1, Edge(4));
	g.connect(1, Edge(5));
	g.connect(2, Edge(4));
	g.connect(2, Edge(5));
	g.connect(3, Edge(4));
	g.connect(3, Edge(5));
	g.connect(4, Edge(5));
	vi path = getEulerianPath(g, 0);
	map<set<int>, int> m;
	FOR(i, 1, path.size()) {
		set<int> s;
		s.insert(path[i-1]);
		s.insert(path[i]);
		m[s]++;
		REQUIRE(m[s] == 1);
	}
	FOR(i, 0, g.V)
		FORC(g.edges[i], edge) {
			set<int> s;
			s.insert(i);
			s.insert(edge->to);
			REQUIRE(m[s] == 1);
		}
}

#include "Algorithms/Graphs/floyd_warshall.h"
TEST_CASE("Floyd Warshall") {
	Graph g(4, false);
	g.connect(0, Edge(2, -2));
	g.connect(1, Edge(2, 3));
	g.connect(1, Edge(0, 4));
	g.connect(2, Edge(3, 2));
	g.connect(3, Edge(1, -1));

	int dist[MAX_V][MAX_V];
	floydWarshall(g, dist);

	int expected[4][4] = { {0, -1, -2, 0 }, {4, 0, 2, 4}, {5, 1, 0, 2}, {3, -1, 1, 0}};

	FOR(i, 0, g.V)
		FOR(j, 0, g.V)
			REQUIRE(dist[i][j] == expected[i][j]);
}

#include "Data_Structures/sparse_table.h"
TEST_CASE("Sparse Table") {
	int arr[10] = { 4, -2, 3, 0, 5, 2, 8, -9, 3, 7 };
	vi nums(arr, arr+10);
	SparseTable st(nums);
	REQUIRE(st.query(0, 9) == 7);
	REQUIRE(st.query(9, 0) == 7);
	REQUIRE(st.query(0, 5) == 1);
	REQUIRE(st.query(2, 6) == 3);
	REQUIRE(st.query(2, 2) == 2);
}

#include "Algorithms/Graphs/lowest_common_ancestor.h"
TEST_CASE("Lowest Common Ancestor") {
	Graph g(7, true);
	g.connect(0, Edge(1));
	g.connect(0, Edge(2));
	g.connect(1, Edge(3));
	g.connect(1, Edge(4));
	g.connect(2, Edge(5));
	g.connect(2, Edge(6));
	LCA lca(g, 0);
	REQUIRE(lca.query(0, 2) == 0);
	REQUIRE(lca.query(0, 6) == 0);
	REQUIRE(lca.query(1, 2) == 0);
	REQUIRE(lca.query(2, 5) == 2);
	REQUIRE(lca.query(5, 6) == 2);
	REQUIRE(lca.query(3, 6) == 0);
	REQUIRE(lca.query(1, 3) == 1);
}

#include "Algorithms/Graphs/maximum_bipartite_matching.h"
TEST_CASE("Maximum Bipartite Matching") {
	Graph g(10, false);
	g.connect(0, Edge(5));
	g.connect(0, Edge(6));
	g.connect(1, Edge(5));
	g.connect(2, Edge(6));
	g.connect(3, Edge(7));
	g.connect(3, Edge(8));
	g.connect(3, Edge(9));
	g.connect(4, Edge(9));

	REQUIRE(maxBipartiteMatching(g, 5) == 4);
}

#include "Algorithms/Graphs/minimum_spanning_tree.h"
TEST_CASE("Minimum Spanning Tree") {
	vii edges;
	int weight[9];
	edges.pb(ii(0, 1)); weight[0] = 1;
	edges.pb(ii(0, 3)); weight[1] = 5;
	edges.pb(ii(0, 4)); weight[2] = 3;
	edges.pb(ii(1, 3)); weight[3] = 5;
	edges.pb(ii(1, 4)); weight[4] = 2;
	edges.pb(ii(2, 4)); weight[5] = 4;
	edges.pb(ii(2, 5)); weight[6] = 5;
	edges.pb(ii(3, 4)); weight[7] = 4;
	edges.pb(ii(4, 5)); weight[8] = 7;

	vi mst = kruskal(edges, weight, 6);
	REQUIRE(find(mst.begin(), mst.end(), 0) != mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 1) == mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 2) == mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 3) == mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 4) != mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 5) != mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 6) != mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 7) != mst.end());
	REQUIRE(find(mst.begin(), mst.end(), 8) == mst.end());

	Graph g(6, true);
	g.connect(0, Edge(1, 1));
	g.connect(0, Edge(3, 5));
	g.connect(0, Edge(4, 3));
	g.connect(1, Edge(3, 5));
	g.connect(1, Edge(4, 2));
	g.connect(2, Edge(4, 4));
	g.connect(2, Edge(5, 5));
	g.connect(3, Edge(4, 4));
	g.connect(4, Edge(5, 7));

	vii mst2 = prim(g);
	#define IN_MST(a, b) ((find(mst2.begin(), mst2.end(), ii(a, b)) != mst2.end()) ^ (find(mst2.begin(), mst2.end(), ii(g.edges[a][b].to, g.edges[a][b].backEdge)) != mst2.end()))
	REQUIRE(IN_MST(0, 0));
	REQUIRE(!IN_MST(0, 1));
	REQUIRE(!IN_MST(0, 2));
	REQUIRE(!IN_MST(1, 1));
	REQUIRE(IN_MST(1, 2));
	REQUIRE(IN_MST(2, 0));
	REQUIRE(IN_MST(2, 1));
	REQUIRE(IN_MST(3, 2));
	REQUIRE(!IN_MST(4, 4));
}

#include "Data_Structures/matrix_graph.h"
TEST_CASE("Matrix Graph") {
	MatrixGraph g(4, true);
	g.connect(1, 3, Edge(2));
	g.connect(1, 2, Edge(5));
	Edge expected[4][4] = { { Edge(0), Edge(0), Edge(0), Edge(0)},  { Edge(0), Edge(0), Edge(5), Edge(2)},  { Edge(0), Edge(5), Edge(0), Edge(0)},  { Edge(2), Edge(0), Edge(0), Edge(0)} };
	REQUIRE(g.edges.size() == 4);
	FOR(cv, 0, g.V) {
		REQUIRE(g.edges[cv].size() == 4);
		FOR(to, 0, g.V)
			REQUIRE(g.edges[cv][to].weight == expected[cv][to].weight);
	}

	MatrixGraph g2(4, false);
	g.connect(1, 3, Edge(2));
	g.connect(1, 2, Edge(5));
	Edge expected2[4][4] = { { Edge(0), Edge(0), Edge(0), Edge(0)},  { Edge(0), Edge(0), Edge(5), Edge(2)},  { Edge(0), Edge(0), Edge(0), Edge(0)},  { Edge(0), Edge(0), Edge(0), Edge(0)} };
	REQUIRE(g2.edges.size() == 4);
	FOR(cv, 0, g2.V) {
		REQUIRE(g2.edges[cv].size() == 4);
		FOR(to, 0, g2.V)
			REQUIRE(g2.edges[cv][to].weight == expected2[cv][to].weight);
	}
}

#include "Algorithms/Graphs/edmonds_karp.h"
TEST_CASE("Edmonds Karp") {
	MatrixGraph g(6, false);
	g.connect(0, 1, Edge(3));
	g.connect(0, 2, Edge(3));
	g.connect(1, 2, Edge(2));
	g.connect(1, 3, Edge(3));
	g.connect(2, 4, Edge(2));
	g.connect(3, 4, Edge(4));
	g.connect(3, 5, Edge(2));
	g.connect(4, 5, Edge(3));
	REQUIRE(maxFlow(g, 0, 5) == 5);
}

#include "Algorithms/Graphs/strongly_connected_components.h"
TEST_CASE("Strongly Connected Components") {
	Graph g(8, false);
	g.connect(0, Edge(1));
	g.connect(1, Edge(2));
	g.connect(2, Edge(3));
	g.connect(3, Edge(4));
	g.connect(4, Edge(5));
	g.connect(5, Edge(6));
	g.connect(7, Edge(0));
	g.connect(1, Edge(7));
	g.connect(1, Edge(6));
	g.connect(2, Edge(5));
	g.connect(3, Edge(2));
	g.connect(4, Edge(3));
	g.connect(6, Edge(5));
	g.connect(7, Edge(6));

	vi components = stronglyConnectedComponents(g);
	REQUIRE(components[0] == components[1]);
	REQUIRE(components[1] == components[7]);
	REQUIRE(components[2] == components[3]);
	REQUIRE(components[3] == components[4]);
	REQUIRE(components[5] == components[6]);
	REQUIRE(components[1] != components[2]);
	REQUIRE(components[4] != components[5]);
}

#include "Algorithms/Graphs/tree_hash.h"
TEST_CASE("Tree Hash") {
	int arr1[] = { 2, 3, 4 };
	int arr2[] = { 5 };
	int arr3[] = { 6, 7 };
	int arr4[] = { };
	vi tree[] = { vi(), vi(arr1, arr1+3), vi(arr2, arr2+1), vi(arr3, arr3+2), vi(), vi(), vi(), vi() };
	vector<vi> t1(tree, tree+8);

	int arr12[] = { 2, 3, 4 };
	int arr22[] = { 5 };
	int arr32[] = { 6 };
	int arr42[] = { 7 };
	vi tree2[] = { vi(), vi(arr12, arr12+3), vi(arr22, arr22+1), vi(arr32, arr32+1), vi(arr42, arr42+1), vi(), vi(), vi() };
	vector<vi> t2(tree2, tree2+8);

	int arr13[] = { 4, 2, 3 };
	int arr23[] = { };
	int arr33[] = { 5 };
	int arr43[] = { 7, 6 };
	vi tree3[] = { vi(), vi(arr13, arr13+3), vi(arr23, arr23+0), vi(arr33, arr33+1), vi(arr43, arr43+2), vi(), vi(), vi() };
	vector<vi> t3(tree3, tree3+8);

	REQUIRE(hs(t1, 1) == hs(t3, 1));
	REQUIRE(hs(t1, 1) != hs(t2, 1));
}

#include "Algorithms/Graphs/tree_height_for_each_root.h"
TEST_CASE("Tree Height for Each Root") {
	Graph g(7, true);
	g.connect(0, Edge(1));
	g.connect(0, Edge(2));
	g.connect(1, Edge(3));
	g.connect(1, Edge(4));
	g.connect(2, Edge(5));
	g.connect(2, Edge(6));

	vii heights;
	getLongestPath(g, heights);
	int expected[] = { 3, 4, 4, 5, 5, 5, 5 };
	FOR(i, 0, g.V)
		REQUIRE(heights[i].second == expected[i]);
}

#include "Algorithms/Mathematics/binomial_coefficients.h"
TEST_CASE("Binomial Coefficients") {
	REQUIRE(nCr(20, 5) == 15504);
	REQUIRE(nCr(61, 30) == 232714176627630544);
	REQUIRE(nCr(1, 1) == 1);
	REQUIRE(nCr(43, 2) == 903);

	buildPascal();

	REQUIRE(pascal[20][5] == 15504);
	REQUIRE(pascal[61][30] == 232714176627630544);
	REQUIRE(pascal[1][1] == 1);
	REQUIRE(pascal[43][2] == 903);
}

#include "Algorithms/Mathematics/catalan_numbers.h"
TEST_CASE("Catalan Numbers") {
    int catNum10 = 16796;
    int catNum30 = 3814986502092304;
    int catNum31 = 14544636039226909;
    REQUIRE(nthCatalan(10) == catNum10);
    REQUIRE(nextCatalan(30, catNum30) == catNum31);
}

#include "Algorithms/Mathematics/cycle_finding.h"
TEST_CASE("Cycle Finding") {
    ii ml = floydCycleFinding(4);
    REQUIRE(ml == mp(int(0), int(6)));
}

#include "Algorithms/Mathematics/ModPow.h"
TEST_CASE("ModPow") {
	REQUIRE(modpow(17, 23, 1000007) == 373271);
	REQUIRE(modpow(23, 32, 423412) == 134905);
	REQUIRE(modpow(25, 14, 1000000009) == 343016784);
	REQUIRE(modpow(13, 6, 293847) == 125257);
}

#include "Algorithms/Mathematics/Euclid.h"
TEST_CASE("Euclid") {
    REQUIRE(gcd(234, 45352) == __gcd(234, 45352));
	int left = 34*mod_inverse(34, 98723)%98723;
    REQUIRE(left == 1);
	left = 2342*mod_inverse(2342, 123973425)%123973425;
    REQUIRE(left == 1);
}

#include "Algorithms/Mathematics/Euclid_chinese_remainder.h"
TEST_CASE("Chinese Remainder Theorem") {
    int n[] = {3, 5, 7};
    int a[] = {2, 3, 2};
    REQUIRE(chinese_remainder(n, a, 3) == 23);
}

#include "Algorithms/Mathematics/factmod.h"
TEST_CASE("FactMod") {
	REQUIRE(factmod(20, 21039) == 11976);
	REQUIRE(factmod(30, 230847902) == 5212186);
	REQUIRE(factmod(45, 826341) == 765387);
}

#include "Algorithms/Mathematics/fast_exponentiation.h"
TEST_CASE("Fast Exponentiation") {
	REQUIRE(fastPow(12, 4) == (int)(round(pow(12.0, 4.0))));
	REQUIRE(fastPow(4, 9) == (int)(round(pow(4.0, 9.0))));
	REQUIRE(fastPow(6, 6) == (int)(round(pow(6.0, 6.0))));
	REQUIRE(fastPow(3, 17) == (int)(round(pow(3.0, 17.0))));
}

bool EQ(double a, double b) {
	return fabs(a-b) < 1e-7;
}

#include "Algorithms/Mathematics/Matrices.h"
TEST_CASE("Matrices") {
	Matrix id = identity(3);
	FOR(i, 0, 3)
		FOR(j, 0, 3)
			REQUIRE(EQ(id[i][j], (i == j)));

	Matrix mult = multiply(id, 4);
	FOR(i, 0, 3)
		FOR(j, 0, 3) {
			REQUIRE(EQ(mult[i][j], 4*(i == j)));
		}

	Matrix a = CREATE(3, 2);
	Matrix b = CREATE(2, 3);
	a[0][0] = 3;
	a[1][0] = 2;
	a[2][0] = 5;
	a[0][1] = 0;
	a[1][1] = 2;
	a[2][1] = 7;

	b[0][0] = 2;
	b[1][0] = 6;
	b[0][1] = 3;
	b[1][1] = -1;
	b[0][2] = 1;
	b[1][2] = 8;

	Matrix c = CREATE(3, 3);
	c[0][0] = 6;
	c[1][0] = 16;
	c[2][0] = 52;
	c[0][1] = 9;
	c[1][1] = 4;
	c[2][1] = 8;
	c[0][2] = 3;
	c[1][2] = 18;
	c[2][2] = 61;

	Matrix d = multiply(a, b);
	FOR(i, 0, 3)
		FOR(j, 0, 3)
			REQUIRE(EQ(c[i][j], d[i][j]));

	Matrix e = CREATE(2, 2);
	e[0][0] = 3;
	e[0][1] = 0;
	e[1][0] = 2;
	e[1][1] = 2;

	Matrix p = pow(e, 3);
	Matrix r = CREATE(2, 2);
	r[0][0] = 27;
	r[0][1] = 0;
	r[1][0] = 38;
	r[1][1] = 8;

	FOR(i, 0, 2)
		FOR(j, 0, 2)
			REQUIRE(EQ(r[i][j], p[i][j]));

	//TODO gauss jordan and rref
}

#include "Algorithms/Mathematics/Fibonacci.h"
TEST_CASE("Fibonacci") {
	REQUIRE(EQ(fibn(0), 1));
	REQUIRE(EQ(fibn(1), 1));
	REQUIRE(EQ(fibn(2), 2));
	REQUIRE(EQ(fibn(6), 13));
	REQUIRE(EQ(fibn(9), 55));
	REQUIRE(EQ(fibn(35), 14930352));

	REQUIRE(EQ(fibonacci(0), 1));
	REQUIRE(EQ(fibonacci(1), 1));
	REQUIRE(EQ(fibonacci(2), 2));
	REQUIRE(EQ(fibonacci(6), 13));
	REQUIRE(EQ(fibonacci(9), 55));
	REQUIRE(EQ(fibonacci(35), 14930352));
}

#include "Algorithms/Mathematics/nth_permutation.h"
TEST_CASE("Nth Permutation") {
	string seq = "013489";
	string perm = seq;
	int i = 0;
	do {
		REQUIRE(nthPermutation(seq, i++) == perm);
	} while(next_permutation(perm.begin(), perm.end()));
}

#include "Algorithms/Mathematics/Primes.h"
TEST_CASE("Primes") {
	buildPrimesList();
	REQUIRE(primesList.size() == 78498);
	REQUIRE(primesList[1000] == 7927);
	REQUIRE(primesList[50000] == 611957);
	vii pf = primeFactorization(871177109);
	REQUIRE(pf.size() == 4);
	REQUIRE(pf[3].first == 7919);
	vi div = divisors(871177109);
	REQUIRE(div[13] == 11933933);
}

#include "Algorithms/Ad_hoc/longest_increasing_subsequence.h"
TEST_CASE("Longest Increasing Subsequence") {
	int arr[10] = { 4, -2, -2, 0, 5, 2, 8, -9, 3, 7 };
	vi lis = longestIncreasingSubsequence(vi(arr, arr+10));
	REQUIRE(lis.size() == 6);
	int expected[6] = { -2, -2, 0, 2, 3, 7 };
	REQUIRE(lis == vi(expected, expected+6));
}

#include "Algorithms/Ad_hoc/shunting_yard.h"
TEST_CASE("Shunting Yard") {

}

#include "Algorithms/Strings/edit_distance.h"
TEST_CASE("Edit Distance") {
	string a = "edit_distance", b = "e.ditdisTancE";
	REQUIRE(editDistance(a, b) == 4);
}

#include "Algorithms/Strings/longest_common_subsequence.h"
TEST_CASE("Longest Common Subsequence") {
	string a = "XMJYAUZ";
	string b = "MZJAWXU";
	REQUIRE("MJAU" == LCS(a, b));
}

#include "Algorithms/Strings/string_matching.h"
TEST_CASE("String Matching") {
	string text = "ABC ABCDAB ABCDABCDABDE ABCDABD";
	string pattern = "ABCDABD";
	vi matches = find(text, pattern);
	REQUIRE(matches.size() == 2);
	REQUIRE(matches[0] == 15);
	REQUIRE(matches[1] == 24);
}

#include "Algorithms/Strings/subsequence_counter.h"
TEST_CASE("Subsequence Counter") {
    REQUIRE(subseqCounter("00000000001111111111222222222233333333334444444444", "0000011111222223333344444") == 1016255020032);
}

//#include "Data_Structures/balanced_binary_search_tree.h"
#include "Data_Structures/splay_tree.h"
TEST_CASE("Balanced Binary Search Tree") {
	SplayTree<int> st;
	REQUIRE(!st.contains(5));
	st.insert(5);
	REQUIRE(st.contains(5));
	st.insert(3);
	st.insert(8);
	st.insert(4);
	st.insert(1);
	REQUIRE(!st.contains(0));
	REQUIRE(st.contains(1));
	REQUIRE(st.contains(3));
	st.erase(3);
	REQUIRE(!st.contains(3));
}


#include "Data_Structures/binary_heap.h"
TEST_CASE("Binary Heap") {
	int arr[10] = { 4, -2, 3, 0, 5, 2, 8, -9, 3, 7 };
	vi v(arr, arr+10);
	Heap<int> h(10);
	REQUIRE(h.empty() == true);
	FOR(i, 0, 10)
		h.push(arr[i]);
	REQUIRE(h.empty() == false);
	while(!h.empty()) {
		vi::iterator MAX = max_element(v.begin(), v.end());
		REQUIRE(h.top() == *MAX);
		h.pop();
		v.erase(MAX);
		REQUIRE(h.empty() == (v.size() == 0));
	}
}

#include "Data_Structures/fenwick_tree.h"
TEST_CASE("Fenwick Tree") {
	FenwickTree ft(5);
	ft.add(1, 1);
	ft.add(2, 5);
	ft.add(3, 4);
	ft.add(4, -1);
	REQUIRE(ft.query(1, 4) == 9);
	REQUIRE(ft.query(4, 1) == 9);
	REQUIRE(ft.query(1, 3) == 10);
	REQUIRE(ft.query(2, 3) == 9);
	ft.add(3, 2);
	REQUIRE(ft.query(2, 4) == 10);

	FenwickTree2D ft2(4, 4);
	REQUIRE(ft2.query(1, 1, 3, 3) == 0);
	ft2.add(1, 1, 4);
	ft2.add(2, 3, -1);
	ft2.add(3, 1, 2);
	REQUIRE(ft2.query(1, 1, 3, 3) == 5);
	REQUIRE(ft2.query(3, 3, 1, 1) == 5);
	REQUIRE(ft2.query(2, 2, 3, 3) == -1);
	REQUIRE(ft2.query(2, 1, 3, 3) == 1);
	ft2.add(1, 1, -7);
	REQUIRE(ft2.query(1, 1, 3, 3) == -2);
}

#include "Data_Structures/interval_tree.h"
TEST_CASE("Interval Tree") {

}

#define LAZY
#include "Data_Structures/segment_tree.h"
TEST_CASE("Segment Tree") {
	int arr[15] = { 23, 11, 91, -4, 31, 90, 10, 2, 0, 15, 40, 37, 101, 82, 14};
	SegmentTree st(vi(arr, arr+15));
	int queries[7][3] = {{0, 0, 14}, {1, 3, 8}, {0, 1, 9}, {1, 11, -20}, {0, 4, 14}, {1, 0, -30}, {0, 0, 1}};
	FOR(i, 0, 7) {
		int type = queries[i][0];
		if(type == 0) {
			int from = queries[i][1];
			int to = queries[i][2];
			int slow = 0;
			FOR(i, from, to+1)
				slow += arr[i];
			REQUIRE(slow == st.query(from, to));
		} else {
			int pos = queries[i][1];
			int val = queries[i][2];
			arr[pos] = val;
			st.pointUpdate(pos, val);
		}
	}

	int rangeQueries[7][4] = {{0, 0, 14, 0}, {1, 3, 5, 8}, {0, 1, 9, 0}, {1, 11, 14, -20}, {0, 4, 14, 0}, {1, 0, 4, -30}, {0, 0, 1, 0}};
	FOR(i, 0, 7) {
		int type = rangeQueries[i][0];
		if(type == 0) {
			int from = rangeQueries[i][1];
			int to = rangeQueries[i][2];
			int slow = 0;
			FOR(i, from, to+1)
				slow += arr[i];
			REQUIRE(slow == st.query(from, to));
		} else {
			int from = rangeQueries[i][1];
			int to = rangeQueries[i][2];
			int val = rangeQueries[i][3];
			FOR(i, from, to+1)
				arr[i] += val;
			st.update(from, to, val);
		}
	}
}

#include "Data_Structures/suffix_array.h"
TEST_CASE("Suffix Array") {
	char str[] = "abcabacba$";
	buildSA(str, 10);
	int expected[] = { 9, 8, 3, 0, 5, 7, 4, 1, 2, 6 };
	FOR(i, 0, 10)
		REQUIRE(SA[i] == expected[i]);

	buildLCP(str, 10);
	int expected2[] = { 0, 0, 1, 2, 1, 0, 2, 1, 0, 1 };
	FOR(i, 0, 10)
		REQUIRE(LCP[i] == expected2[i]);

	char pattern[] = "ab";
	ii matches = findPattern(str, 10, pattern, 2);
	FOR(i, matches.first, matches.second + 1) {
		REQUIRE((str+SA[i])[0] == 'a');
		REQUIRE((str+SA[i])[1] == 'b');
	}
}

#include "Data_Structures/trie.h"
TEST_CASE("Trie") {
	Trie trie;
	char abc[] = "abc";
	char abd[] = "abd";
	char ahg[] = "ahg";
	char lmn[] = "lmn";
	char a[] = "a";
	char ab[] = "ab";
	trie.insert(abc);
	trie.insert(abc);
	trie.insert(abd);
	trie.insert(ahg);
	trie.insert(lmn);
	REQUIRE(trie.countWords(a) == 0);
	REQUIRE(trie.countWords(abc) == 2);
	REQUIRE(trie.countWords(abd) == 1);
	REQUIRE(trie.countPrefix(a) == 4);
	REQUIRE(trie.countPrefix(ab) == 3);
}

#include "Data_Structures/Geometry/point.h"
TEST_CASE("Point") {
    Point A(5, 5), B, C, D(-5, -5), E(5, -5);
    B = rotate(A, 180);
    C = rotate(A, -90);
    REQUIRE(B == D);
    REQUIRE(C == E);
    REQUIRE(eq(angulo(B), 225));
    REQUIRE(eq(angulo(C), 315));
    REQUIRE(eq(dist(A, C), 10));
}

#include "Data_Structures/Geometry/vectors.h"
TEST_CASE("Vectors") {
    Point A(-5, 0), B(0, 0), C(15.4, 0), D(10, 10);
    REQUIRE(collinear(A, B, C));
    REQUIRE(eq(abs(angle(A, B, D)), 3*acos(-1)/4));
}

#include "Data_Structures/Geometry/lines.h"
TEST_CASE("Line") {
    Point A(0,0), B(4,0), C(0,4), D(4,4), E(5,0), F(2,2), G;
    Line ab(A,B), cd(C,D), ae(A,E), ad(A,D), bc(B,C);
    REQUIRE(areParallel(ab, cd));
    REQUIRE(areSame(ab, ae));
    REQUIRE(areIntersect(ad, bc, G));
    REQUIRE(F == G);
    REQUIRE(eq(distToLine(E, A, C, G), 5));
}

#include "Data_Structures/Geometry/polygons.h"
TEST_CASE("Polygons") {
    Polygon P;
    Point A(0,0), B(1,0), C(1,1), D(0,1), E(-1,-1), F(.5, .5);
    P.pb(A), P.pb(B), P.pb(C), P.pb(D), P.pb(E), P.pb(F);
    REQUIRE(!isConvex(P));
    Polygon ch = convexHull(P);
    REQUIRE(eq(area(ch), 2));
    REQUIRE(ch.size() == 5);
    REQUIRE(inPolygon(F, ch));
    //Polygon cut = (Point(0, 2), Point(2, -1), ch);
    //REQUIRE(cut.size() == 5);
}

#include "Data_Structures/Geometry/triangles.h"
TEST_CASE("Triangles") {
    Point A(0, 0), B(5, 3), C(2, 6);
    Triangle abc(A, B, C);
    REQUIRE(eq(area(abc), 12));
    Point D(4, 3), E(-3, 4), F(0, -5);
    Triangle def(D, E, F);
    REQUIRE(circumcenter(def) == A);
}

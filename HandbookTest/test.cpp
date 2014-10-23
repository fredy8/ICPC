#define CATCH_CONFIG_MAIN
#include "catch.h"

#include "Utility/header.h"

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

#include "Algorithms/Graphs/dijkstra.h"

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
	g.connect(0, Edge(3));
	g.connect(0, Edge(4));
	g.connect(1, Edge(3));
	g.connect(2, Edge(4));
	g.connect(2, Edge(7));
	g.connect(3, Edge(5));
	g.connect(3, Edge(6));
	g.connect(4, Edge(6));
	vi ts = topologicalSort(g);
#define find(a) (find(ts.begin(), ts.end(), (a)))
	REQUIRE(find(0) < find(3));
	REQUIRE(find(0) < find(4));
	REQUIRE(find(1) < find(3));
	REQUIRE(find(2) < find(3));
	REQUIRE(find(2) < find(7));
	REQUIRE(find(3) < find(5));
	REQUIRE(find(3) < find(6));
	REQUIRE(find(4) < find(6));
#undef find
}

#include "Algorithms/Graphs/DAGs/shortest-longest_path.h"
TEST_CASE("Shortest Path in a DAG") {
	
}

#include "Algorithms/Graphs/edge_property_check.h"
TEST_CASE("Edge Property Check") {

}

#include "Algorithms/Graphs/eulerian_path.h"
TEST_CASE("Eulerian Path") {

}

#include "Algorithms/Graphs/floyd_warshall.h"
TEST_CASE("Floyd Warshall") {

}

#include "Data_Structures/sparse_table.h"
TEST_CASE("Sparse Table") {

}

#include "Algorithms/Graphs/lowest_common_ancestor.h"
TEST_CASE("Lowest Common Ancestor") {

}

#include "Algorithms/Graphs/maximum_bipartite_matching.h"
TEST_CASE("Maximum Bipartite Matching") {

}

#include "Algorithms/Graphs/minimum_spanning_tree.h"
TEST_CASE("Minimum Spanning Tree") {

}

#include "Algorithms/Graphs/edmonds_karp.h"
TEST_CASE("Edmonds Karp") {

}

#include "Algorithms/Graphs/strongly_connected_components.h"
TEST_CASE("Strongly Connected Components") {

}

#include "Algorithms/Graphs/tree_hash.h"
TEST_CASE("Tree Hash") {

}

#include "Algorithms/Graphs/tree_height_for_each_root.h"
TEST_CASE("Tree Height for Each Root") {

}

#include "Algorithms/Mathematics/binomial_coefficients.h"
TEST_CASE("Binomial Coefficients") {

}

#include "Algorithms/Mathematics/catalan_numbers.h"
TEST_CASE("Catalan Numbers") {

}

#include "Algorithms/Mathematics/cycle_finding.h"
TEST_CASE("Cycle Finding") {

}

#include "Algorithms/Mathematics/modpow.h"
TEST_CASE("ModPow") {

}

#include "Algorithms/Mathematics/euclid.h"
TEST_CASE("Euclid") {

}

#include "Algorithms/Mathematics/extended_euclidean.h"
TEST_CASE("Extended Euclidean") {

}

#include "Algorithms/Mathematics/factmod.h"
TEST_CASE("FactMod") {

}

#include "Algorithms/Mathematics/fast_exponentiation.h"
TEST_CASE("Fast Exponentiation") {

}

#include "Algorithms/Mathematics/matrices.h"
TEST_CASE("Matrices") {

}

#include "Algorithms/Mathematics/fibonacci.h"
TEST_CASE("Fibonacci") {

}

#include "Algorithms/mathematics/nth_permutation.h"
TEST_CASE("Nth Permutation") {

}

#include "Algorithms/Mathematics/primes.h"
TEST_CASE("Primes") {

}

#include "Algorithms/Ad_hoc/longest_increasing_subsequence.h"
TEST_CASE("Longest Increasing Subsequence") {

}

#include "Algorithms/Ad_hoc/shunting_yard.h"
TEST_CASE("Shunting Yard") {

}

#include "Algorithms/Strings/edit_distance.h"
TEST_CASE("Edit Distance") {

}

#include "Algorithms/Strings/longest_common_subsequence.h"
TEST_CASE("Longest Common Subsequence") {

}

#include "Algorithms/Strings/string_matching.h"
TEST_CASE("String Matching") {

}

#include "Algorithms/Strings/subsequence_counter.h"
TEST_CASE("Subsequence Counter") {

}

#include "Data_Structures/balanced_binary_search_tree.h"
TEST_CASE("Balanced Binary Search Tree") {

}

#include "Data_Structures/binary_heap.h"
TEST_CASE("Binary Heap") {

}

#include "Data_Structures/fenwick_tree.h"
TEST_CASE("Fenwick Tree") {

}

#include "Data_Structures/interval_tree.h"
TEST_CASE("Interval Tree") {

}

#include "Data_Structures/matrix_graph.h"
TEST_CASE("Matrix Graph") {

}

#include "Data_Structures/segment_tree.h"
TEST_CASE("Segment Tree") {

}

#include "Data_Structures/suffix_array.h"
TEST_CASE("Suffix Array") {

}

#include "Data_Structures/trie.h"
TEST_CASE("Trie") {

}

#include "Data_Structures/Geometry/point.h"
TEST_CASE("Point") {

}

#include "Data_Structures/Geometry/vectors.h"
TEST_CASE("Vectors") {

}

#include "Data_Structures/Geometry/lines.h"
TEST_CASE("Line") {

}

#include "Data_Structures/Geometry/polygons.h"
TEST_CASE("Polygons") {

}

#include "Data_Structures/Geometry/triangles.h"
TEST_CASE("Triangles") {

}

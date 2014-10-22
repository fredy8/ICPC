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

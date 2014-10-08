/*
4 1 4 2 3
5 1 4 2 -1 6
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

int rangeOR(int A, int B) {
    int value = 0;
    for(int i= 1<<(sizeof(int)-1); i; i >>= 1) {
        value <<= 1;
        value += A/i&1 || B/i&1 || A/i != B/i;
    }
    return value;
}

mint main() {
    cout << rangeOR(3, 10) << endl;
    cout << (3 | 4 | 5 | 6 | 7 | 8 | 9 | 10) << endl;
}
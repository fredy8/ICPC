/*
8
0 0 0 0 0 0 0 0 
*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std;
typedef long long ll; typedef pair<int, int> ii;
typedef vector<int> vi; typedef vector<ii> vii;
typedef vector<vi> vvi;

mint main() {
	int N;
	cin >> N;
	int arr[N];
	FOR(i, 0, N)
		cin >> arr[i];
	
	sort(arr, arr+N);

	int sum = 0;
	FOR(i, 0, N/2)
		sum += min(abs(arr[i*2] - arr[i*2+1]), 24 - abs(arr[i*2] - arr[i*2+1]));
	
	int sum2 = 0;
	FOR(i, 0, N/2-1)
		sum2 += min(abs(arr[i*2+1] - arr[i*2+2]), 24 - abs(arr[i*2+1] - arr[i*2+2]));
	sum2 += min(abs(arr[0] - arr[N-1]), 24 - abs(arr[0] - arr[N-1]));

	cout << min(sum, sum2) << endl;
}

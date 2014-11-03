/*
3
15 20
19 100
10 10
3
10 20
10 10
10 30
2
10 10
10 10
2
10 1
20 100
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
#define INF 2000000001
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

map<int, map<int, int> > arr;
map<int, set<ii> > intersections;

mint main() {
	int N;
	while(cin >> N) {
	int MAX = 0;
	arr.clear();
	intersections.clear();
	FOR(i, 0, N) {
		int t, v;
		cin >> t >> v;
		arr[t][v]++;
		MAX = max(MAX, arr[t][v]);
	}

	FORC(arr, time_it) {
		FORC(time_it->second, speed_it) {
			typeof(time_it) it = time_it;
			while(it != arr.end() && it->first <= time_it->first+ceil(100.0/speed_it->first)) {
				FORC(it->second, vit) {
					int t1 = time_it->first;
					int v1 = speed_it->first;
					int t2 = it->first;
					int v2 = vit->first;
					if(v2 != v1) {
						//cout << t1 << " " << v1 << " " << t2 << " " << v2 << endl;
						double intersection = double(t2-t1)/(1.0/v1 - 1.0/v2);
						int inter = int(round(intersection*1000000)); 
						//cout << "intersection at: " << inter/1000000 << endl;
						if(inter >= 0 && inter <= 100000000) {
							intersections[inter].insert(ii(t1, v1));
							intersections[inter].insert(ii(t2, v2));
						}
					}
				}
				++it;
			}
		}
	}

	FORC(intersections, it) {
		int k = 0;
		FORC(it->second, it2)
			k += arr[it2->first][it2->second];
		MAX = max(MAX, k);
	}
	cout << MAX << endl;
	}
}

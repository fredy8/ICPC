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
#include <cassert>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef pair<int, int> ii;

#define STRICTLY_INCREASING
vi LongestIncreasingSubsequence(vi &v) {
    vii best;
    vi parent(v.size(), -1);
    FOR(i, 0, v.size()) {
        #ifdef STRICTLY_INCREASING
        ii item = ii(v[i], 0);
        vii::iterator it = lower_bound(best.begin(), best.end(), item);
        item.second = i;
        #else
        ii item = ii(v[i], i);
        vii::iterator it = upper_bound(best.begin(), best.end(), item);
        #endif
        if (it == best.end()) {
            parent[i] = (best.size() == 0 ? -1 : best.back().second);
            best.push_back(item);
        } else {
            parent[i] = parent[it->second];
            *it = item;
        }
    }
    vi lis;
    for(int i=best.back().second; i >= 0; i=parent[i])
        lis.push_back(v[i]);
    //reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
	vi seq; int x;
	
	while(cin >> x) seq.pb(-x);
	reverse(seq.begin(), seq.end());
	
	vi lis = LongestIncreasingSubsequence(seq);
	
	cout << lis.size() << endl << "-" << endl;
	for(int i : lis) {
		cout << i << endl;
	}
}

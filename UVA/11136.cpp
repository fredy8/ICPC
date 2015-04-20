/*
5
3 1 2 3
2 1 1
4 10 5 5 1
0
1 2
2
2 1 2
2 1 2
0
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
#include <list>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int main() {
    int N;
    while(scanf("%d", &N) != EOF && N) {
        multiset<int> ms;
        long long ans = 0;
        FOR(j, 0, N) {
            int K;
            scanf("%d", &K);
            FOR(i, 0, K) {
                int k; scanf("%d", &k);;
                ms.insert(k);
            }
            set<int>::iterator first = ms.begin();
            set<int>::iterator last = --ms.end();
            ans += *last - *first;
            ms.erase(last);
            ms.erase(first);
        }
        printf("%lld\n", ans);
    }
}
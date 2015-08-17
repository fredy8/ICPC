/*
7 1 2 3 4 5 6 7
8 1 2 3 5 8 13 21 34
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int main() {
    int K;
    bool first = true;
    while(cin >> K && K) {
        if(!first)
            cout << endl;
        first = false;

        vi nums;
        FOR(i, 0, K) {
            int n;
            cin >> n;
            nums.pb(n);
        }

        string p = "000000";
        FOR(i, 0, K-6)
            p += "1";

        do {
            int r = 0;
            FOR(i, 0, K) {
                if(p[i] == '0')
                    cout << nums[i] << (r++ == 5 ? "" : " ");
            }
            cout << endl;
        } while(next_permutation(p.begin(), p.end()));
    }
}
/*
2
40 40
80

5
10 2 6 8 4
10
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
    int N;
    while(cin >> N) {
        int arr[N];
        FOR(i, 0, N)
            cin >> arr[i];
        int M; cin >> M;
        sort(arr, arr+N);
        int b1 = 0, b2 = N-1;
        int ans1 = -1, ans2 = -1;
        while(b1 < b2) {
            int s = arr[b1] + arr[b2];
            if(s == M) {
                ans1 = arr[b1], ans2 = arr[b2];
                b1++;
                b2--;
            } else if(s > M) {
                b2--;
            } else {
                b1++;
            }
        }

        printf("Peter should buy books whose prices are %d and %d.\n\n", ans1, ans2);
    }

}
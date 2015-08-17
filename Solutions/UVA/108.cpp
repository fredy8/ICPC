/*
4
0 -2 -7  0
9  2 -6  2
-4 1 -4  1
-1 8  0 -2
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

int maximumSubarray(int numbers[], int N) {
    int maxSoFar = numbers[0], maxEndingHere = numbers[0];
    for(int i=1; i<N; i++) {
        if(maxEndingHere < 0) maxEndingHere = numbers[i];
        else maxEndingHere += numbers[i];
        maxSoFar = max(maxEndingHere, maxSoFar);
    }
    return maxSoFar;
}

int main() {
    int N;
    cin >> N;
    int arr[N][N];
    int sumUntil[N][N];
    memset(sumUntil, 0, sizeof sumUntil);
    FOR(i, 0, N*N) {
        int r = i/N, c = i%N;
        cin >> arr[r][c];
        int u = r ? sumUntil[r-1][c] : 0;
        sumUntil[r][c] = u + arr[r][c];
    }

    int MAX = -INF;
    FOR(i, 0, N)
        FOR(j, i, N) {
            int arr2[N];
            FOR(k, 0, N) {
                arr2[k] = sumUntil[j][k] - (i ? sumUntil[i-1][k] : 0);
            }
            MAX = max(MAX, maximumSubarray(arr2, N));
        }

    cout << MAX << endl;


}
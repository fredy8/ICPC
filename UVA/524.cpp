/*
6
8
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


int sol[17];

bool isPrime(int p)
{
    switch (p) {
        case 2:
        case 3:
        case 5:
        case 7:
        case 11:
        case 13:
        case 17:
        case 19:
        case 23:
        case 29:
        case 31:
        case 37:
        case 41:
            return true;
            break;
    };
    return false;
}
void getSolutions(int used, int M)
{
    int next = __builtin_popcount(used);
    if (next == M) {
        if (isPrime(1+sol[M-1])) {
            cout << 1;
            for (int i = 1; i < M; i++)
                cout << " " << sol[i];
            cout << endl;
        }
        return;
    }
    for (int i = 0; i < M; i++) {
        if (isPrime(i + 1 + sol[next-1]) && !(used & 1<<i)) {
            sol[next] = i+1;
            getSolutions(used | 1<<i, M);
        }
    }
}

int main()
{
    int n, tc = 1;
    while(cin >> n) {
        if(tc != 1)
            cout << endl;
        cout << "Case " << tc++ << ":" << endl;
        sol[0] = 1;
        getSolutions(1, n);
    }
}
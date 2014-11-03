/*
4
1223
2123
2213
3212
2
12
33
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

unsigned short fours[10] = {0xf000, 0xf00, 0xf0, 0xf, 0x8888, 0x4444, 0x2222, 0x1111, 0x8421, 0x1248};

bool xwins(unsigned short xo, unsigned short placed) {
    FOR(i, 0, 10) {
        if(xo & fours[i] == fours[i]) return true;
    }
    return false;
}

bool forcedxwin(unsigned short xo, unsigned short placed) {
    // debe ser mas rapida, esto es 160 deberia ser ~40 ?
    FOR(i,0,16) {
        int square = 1<<i;
        if(!(placed & square) && xwins(xo | square, placed | square)) return true;
    }
    return false;
}

void solve(unsigned short xo, unsigned short placed) {
    
}

int main() {
    while(cin >> N) {
        vii initials;
        FOR(i, 0, N) {
            cin >> arr[i];
            FOR(j, 0, N)
                if(arr[i][j] == '3')
                    initials.pb(ii(i, j));
        }

        solve(initials);


        int MAX = 0;
        FOR(i, 0, N)
            FOR(j, 0, N)
                if(arr[i][j] == '1')
                    MAX = max(MAX, dist[i][j]-1);
        cout << MAX << endl;
    }
}

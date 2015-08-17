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

const int arr[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int flip(int board, int pos) {
    int row = pos/3;
    int col = pos%3;
    board ^= 1<<pos;
    FOR(i, 0, 4) {
        int newR = row + arr[i][0];
        int newC = col + arr[i][1];
        if (0 <= newR && newR < 3 && 0 <= newC && newC < 3) {
            int newP = 3*newR + newC;
            board ^= 1<<newP;
        }
    }
    return board;
}

int solve(int goal) {
    bool visited[1<<9] = {false};
    visited[0] = true;
    queue<ii> q;
    q.push(mp(0, 0));
    while (!q.empty()) {
        ii cur = q.front();
        q.pop();
        if (cur.first == goal)
            return cur.second;
        FOR(i, 0, 9) {
            int newB = flip(cur.first, i);
            if (!visited[newB]) {
                visited[newB] = true;
                q.push(mp(newB, cur.second+1));
            }
        }
    }
    return -1;
}

mint main() {
    int T;
    cin >> T;
    string aux;
    int goal = 0;
    FOR(i, 0, T) {
        goal = 0;
        FOR(j, 0, 3) {
            cin >> aux;
            FOR(k, 0, 3) {
                if (aux[k] == '*') {
                    goal += 1<<(3*j + k);
                }
            }
        }
        cout << solve(goal) << endl;
    }
}

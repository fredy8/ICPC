//624

#ifndef sh
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
#endif

#define MAX 1002

int neigh[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // urdl
int pass[MAX][MAX], cnt[5];
int dir = 1, b, w;
bool board[MAX][MAX];
ii curPos;

bool getTile (ii pos) {return board[pos.first][pos.second];}
void move();
void turn()
{
    ii nextPos;
    nextPos.first = curPos.first + neigh[(dir+1)%4][0];
    nextPos.second = curPos.second + neigh[(dir+1)%4][1];
    if (!getTile(nextPos)) {
        dir = (dir+1)%4;
        move();
        return;
    }
    nextPos.first = curPos.first + neigh[dir][0];
    nextPos.second = curPos.second + neigh[dir][1];
    if (!getTile(nextPos)) {
        move();
        return;
    }
    dir = (dir+3)%4;
    move();
}
void move()
{
    ii nextPos;
    nextPos.first = curPos.first + neigh[dir][0];
    nextPos.second = curPos.second + neigh[dir][1];
    if (!getTile(nextPos)) {
        curPos = nextPos;
        pass[curPos.first][curPos.second]++;
        if (curPos.first == b && curPos.second == 1) return;
    }
    turn();
}

int main()
{
    while (cin >> b >> w && b && w) {
        for (int i = 0; i <= b+1; i++)
            for (int j = 0; j <= w+1; j++)
                board[i][j] = 1, pass[i][j] = 0;
        char aux;
        for (int i = 1; i <= b; i++)
            for (int j = 1; j <= w; j++) {
                cin >> aux;
                board[i][j] = (aux == '1');
            }
        curPos.first = b;
        curPos.second = 1;
        turn();
        for (int i = 1; i <= b; i++)
            for (int j = 1; j <= w; j++)
                if (!board[i][j])
                    cnt[pass[i][j]]++;
        for (int i = 0; i < 5; i++)
            cout << setw(3) << cnt[i];
        cout << endl;
    }
}

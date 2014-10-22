/*
2

1 2 10 I
3 1 10 I
1 2 19 R
3 2 19 R
1 1 25 C
3 2 26 C

1 2 10 I
3 1 10 I
1 2 19 R
3 2 19 R
1 1 25 C
3 2 26 C
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
    int TC;
    cin >> TC;
    string aux;
    getline(cin, aux);
    getline(cin, aux);
    bool first = true;
    while(TC--) {
        if(!first)
            cout << endl;
        first = false;
        string line;

        vector<pair<int, pair<int, pair<int, bool> > > > subs;

        bool accepted[101][10] = {0};
        int acCount[101] = {0};
        int timesPerProblem[101][10] = {0};
        int times[101] = {0};
        bool hasSumbmission[101] = {0};

        while(getline(cin, line) && line.length()) {
            stringstream stream(line);
            int contestant, problem, time;
            char L;
            stream >> contestant >> problem >> time >> L;
            hasSumbmission[contestant] = 1;

            if(L == 'C' || L == 'I') {
                bool ac = L == 'C';
                if(!accepted[contestant][problem]) {
                    if(ac) {
                        accepted[contestant][problem] = 1;
                        acCount[contestant]++;
                        times[contestant] += time + timesPerProblem[contestant][problem];
                    } else {
                        timesPerProblem[contestant][problem] += 20;
                    }
                }
            }
        }

        vector<pair<int, pair<int, int> > > teams;
        FOR(i, 0, 101) {
            if(hasSumbmission[i]) {
                teams.pb(make_pair(-acCount[i], make_pair(times[i], i)));
            }
        }

        sort(teams.begin(), teams.end());

        FOR(i, 0, teams.size()) {
            cout << teams[i].second.second << " " << -teams[i].first << " " << teams[i].second.first << endl;
        }
    }
}
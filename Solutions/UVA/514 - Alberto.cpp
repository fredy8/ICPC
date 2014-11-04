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

template <typename T>
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }

bool solvable(int N, int perm[])
{
    int nextIn = 1, nextOut = 0;
    stack<int> station;
    while (true) {
        while (!station.empty() && station.top() == perm[nextOut]) {
            station.pop();
            nextOut++;
        }
        if (nextOut == N) return true;
        if (nextIn == N+1) return false;
        station.push(nextIn);
        nextIn++;
    }
}

int main()
{
    int N;
    while (cin >> N && N) {
        int perm[1000];
        while (cin >> perm[0] && perm[0]) {
            for (int i = 1; i < N; i++)
                cin >> perm[i];
            if (solvable(N, perm))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        cout << endl;
    }
}

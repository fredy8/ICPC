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

int main()
{
    int casos;
    cin >> casos;
    for (int tc = 0; tc < casos; tc++) {
        cout << (tc ? "\n" : "");
        int a, f;
        cin >> a >> f;
        for (int i = 0; i < f; i++) {
            cout << (i ? "\n" : "");
            for (int j = 1; j <= a; j++) {
                for (int h = 0; h < j; h++) cout << j;
                cout << endl;
            }
            for (int j = a-1; j > 0; j--) {
                for (int h = 0; h < j; h++) cout << j;
                cout << endl;
            }
        }
    }
}

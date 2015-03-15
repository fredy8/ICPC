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

vector<int> split (string text) {
    istringstream iss(text);
    vector<int> v;
    int num;
    while (iss >> num) v.pb(num);
    return v;
}

int main()
{
    string lineC, lineX;
    while (getline(cin, lineC)) {
        getline(cin, lineX);
        vector<int> C = split(lineC);
        vector<int> X = split(lineX);
        for (int i = 0; i < X.size(); i++) {
            int r = 0, x = X[i];
            for (int j = 0; j < C.size(); j++) {
                r *= x;
                r += C[j];
            }
            cout << (i ? " " : "") << r;
        }
        cout << endl;
    }
}
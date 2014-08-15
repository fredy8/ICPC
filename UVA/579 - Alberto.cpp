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

int main()
{
    string hora;
    cout << fixed << setprecision(3);
    while (cin >> hora && hora != "0:00") {
        int dspts = hora.find(':');
        int hr = toNum<int>(hora.substr(0,dspts));
        int mn = toNum<int>(hora.substr(dspts+1));
        double angHr = hr*360/12.0 + 360/12*mn/60.0;
        double angMn = mn*360/60.0;
        double ang = (angHr>angMn ? angHr-angMn : angMn-angHr);
        ang = (ang>=360 ? ang-360 : ang);
        ang = (ang>=180 ? 360-ang : ang);
        cout << ang << endl;
    }
}

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
    using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<char, char> cc;
#endif

int main()
{
    int n;
    cout << fixed << setprecision(2);
    while (cin >> n && n) {
        vector<double> v;
        for (int i = 0; i < n; i++) {
            double tmp;
            cin >> tmp;
            v.pb(tmp);
        }
        int sum = accumulate(v.begin(), v.end(), 0.0)*100;
        int dif = sum%(int)v.size();
        int dif1 = (v.size() - dif)%(int)v.size();
        int avg = floor((double)sum/v.size());
        int avg1 = ceil((double)sum/v.size());
        int s = 0;
        //cout << sum << " " << dif << " " << dif1 << " " << avg << " " << avg1 << endl;
        //double avg = accumulate(v.begin(), v.end(), 0.0)/v.size(), s = 0;
        //double avg1 = round(floor(avg*100))/100.0, avg2 = round(ceil(avg*100))/100.0;
        int cntMayor = 0, cntMenor = 0;
        for (int i = 0; i < n; i++) {
            if (v[i]*100 <= avg) {
                if (cntMenor < dif) {
                    s += avg - v[i]*100;
                    cntMenor++;
                } else {
                    s += avg1 - v[i]*100;
                }
            } else {
                if (cntMayor < dif1) {
                    s += v[i]*100 - avg1;
                    cntMayor++;
                } else {
                    s += v[i]*100 - avg;
                }
            }
        }
        cout << '$' << s/200.0 << endl;
    }
}

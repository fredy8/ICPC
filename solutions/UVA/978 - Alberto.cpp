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
    int casos;
    cin >> casos;
    while (casos--) {
        int b, sg, sb, aux;
        cin >> b >> sg >> sb;
        priority_queue<int> pqg, pqb;
        vii battles;
        battles.assign(b, make_pair(-1, -1));
        for (int i = 0; i < sg; i++) {
            cin >> aux;
            pqg.push(aux);
        }
        for (int i = 0; i < sb; i++) {
            cin >> aux;
            pqb.push(aux);
        }
        while (!pqg.empty() && !pqb.empty()) {
            for (int i = 0; i < b; i++) {
                if (!pqg.empty()) {
                    battles[i].first = pqg.top();
                    pqg.pop();
                }
                if (!pqb.empty()) {
                    battles[i].second = pqb.top();
                    pqb.pop();
                }
            }
            for (int i = 0; i < b; i++) {
                int a = battles[i].first, b = battles[i].second;
                battles[i].first = (a == -1 ? -1 :
                                    (b == -1 ? a :
                                     (a > b ? a-b :
                                      (-1))));
                battles[i].second = (b == -1 ? -1 :
                                     (a == -1 ? b :
                                      (b > a ? b-a :
                                      (-1))));
            }
            for (int i = 0; i < b; i++) {
                int a = battles[i].first, b = battles[i].second;
                if (a != -1)
                    pqg.push(a);
                if (b != -1)
                    pqb.push(b);
            }
            for (int i = 0; i < b; i++) {
                battles[i].first = battles[i].second = -1;
            }
        }
        if (pqg.empty() && pqb.empty()) {
            cout << "green and blue died" << endl;
        } else if (pqg.empty()) {
            cout << "blue wins" << endl;
            while (!pqb.empty()) {
                cout << pqb.top() << endl;
                pqb.pop();
            }
        } else {
            cout << "green wins" << endl;
            while (!pqg.empty()) {
                cout << pqg.top() << endl;
                pqg.pop();
            }
        }
        cout << (casos ? "\n" : "");
    }
}

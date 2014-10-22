/*
1
7
5
1
2
3
1
8
4
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
    while(TC--) {
        int N;
        cin >> N;
        set<int> s;
        int MAX = 1;
        int start = 0;
        int arr[N];
        FOR(i, 0, N) {
            int sf;
            cin >> sf;
            arr[i] = sf;
            if(s.find(sf) == s.end()) {
                s.insert(sf);
            } else {
                MAX = max(MAX, int(s.size()));
                while(arr[start] != sf) {
                    s.erase(s.find(arr[start]));
                    start++;
                }
                start++;
            }
        }
        MAX = max(MAX, int(s.size()));
        cout << MAX << endl;
    }
}
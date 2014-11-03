/*
pretty
women
walking
down
the
street
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int main() {
    string a, b;
    while(getline(cin, a) && getline(cin, b)) {
        int arr1[26], arr2[26];
        FOR(i, 0, 26)
            arr1[i] = arr2[i] = 0;

        FOR(i, 0, a.length())
            arr1[a[i] - 'a']++;

        FOR(i, 0, b.length())
            arr2[b[i] - 'a']++;

        FOR(i, 0, 26) {
            int m = min(arr1[i], arr2[i]);
            FOR(j, 0, m)
                cout << (char)('a'+i);
        }
        cout << endl;
    }
}
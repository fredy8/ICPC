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
#include <cstdlib>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

#define MAX 1001

char fun(int i) {
    if (i == 0) return '+';
    if (i == 1) return '-';
    if (i == 2) return '0';
}

int main() {
    vector<string> arr(MAX, "");
    int pot = 1, start = 1, index;
    FOR(i, 0, 7) {
        for (int j = 0; j + start < MAX; j++) {
            arr[j+start] = fun((j/pot)%3) + arr[j+start];
        }
        start += pot;
        pot *= 3;
    }
    cin >> index;
    cout << arr[index] << endl;
}

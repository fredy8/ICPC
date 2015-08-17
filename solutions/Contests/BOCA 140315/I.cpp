#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std;
typedef long long ll; typedef pair<int, int> ii;
typedef vector<int> vi; typedef vector<ii> vii;
typedef vector<vi> vvi;

int MSB(int x) {
	if(!x) return 0;
	int ans = 1;
	while(x>>1) x>>=1, ans<<=1;
	return ans;
}

mint main() {
    int N;
    long long a, b;
    cin >> N;
    while (N--) {
        cin >> a >> b;
        if (a < b)
            swap(a, b);
        int diagA = MSB(a)*2-1;
        int diagB = MSB(b)*2-1;
        int sobranA = diagA - a;
        int sobranB = 0;
        for (int diag = diagA; diag >= diagB; diag /= 2) {
            int quitoA = max(0ll, diag - a);
            int quitoB = diag - b;
            int overlap = min(0ll, diag + 1 - quitoA - quitoB);
            //cout << quitoA << " " << quitoB << " " << overlap << endl << " ";
            sobranB += quitoB + overlap;
        }
        cout << 2*diagA + 1 - sobranA - sobranB << endl;
    }
}

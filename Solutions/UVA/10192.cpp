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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

int LCS(const string &a, const string &b) {
    int n = a.length(), m = b.length();
    int D[n][m];
    char c[n][m];
    FOR(i, 0, n)
        FOR(j, 0, m)
            if(a[i] == b[j]) {
                D[i][j] = i&&j ? D[i-1][j-1] + 1 : 1;
                c[i][j] = a[i];
            }
            else {
                c[i][j] = (i ? D[i-1][j] : 0) >= (j ? D[i][j-1] : 0);
                D[i][j] = max(i ? D[i-1][j] : 0, j ? D[i][j-1] : 0);
            }
    
    return D[n - 1][m - 1];
}

int main() {
	string a, b;
	int c = 1;
	
	while(getline(cin, a) && getline(cin, b) && a[0] != '#') {
		cout << "Case #" << c << ": you can visit at most "
			<< LCS(a, b) << " cities." << endl;
		
		c++;
	}
}

/*
 * 
3755PR/1E/9V6
5377BR/12/9WU
5707BA/12/9V6
5327BA/1E/9V6
7337BA/1E/9V6
7137BA/11/9V6

*/

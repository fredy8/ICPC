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


//int D[n][m];
/*unordered_map<int, int> *ranks;

int rank(int i) {
	if(ranks->find(i) != ranks->end())
		return ranks[i];
	else return INF
}*/

int rango[251*251];

bool cmp(const ii &a, const ii &b) {
	return rango[a.first] < rango[b.first];
}

#define STRICTLY_INCREASING
int lis(const vi &v) {
		
    vii best;
    vi parent(v.size(), -1);
    FOR(i, 0, v.size()) {
        #ifdef STRICTLY_INCREASING
        ii item = ii(v[i], 0);
        vii::iterator it = lower_bound(best.begin(), best.end(), item, cmp);
        item.second = i;
        #else
        ii item = ii(v[i], i);
        vii::iterator it = upper_bound(best.begin(), best.end(), item, cmp);
        #endif
        if (it == best.end()) {
            parent[i] = (best.size() == 0 ? -1 : best.back().second);
            best.push_back(item);
        } else {
            parent[i] = parent[it->second];
            *it = item;
        }
    }
    
     vi lis;
    for(int i=best.back().second; i >= 0; i=parent[i])
        lis.push_back(v[i]);
    reverse(lis.begin(), lis.end());
    //return lis;
    //FOR(i, 0, lis.size()) {cout << "lis"<<lis[i] << endl;}
    
    return best.size();
}

int LCS(const vi &a, const vi &b) {
    int n = a.size(), m = b.size();
    //char c[n][m];
    vvi D(n, vi(m, 0));
    
    FOR(i, 0, n)
        FOR(j, 0, m)
            if(a[i] == b[j]) {
                D[i][j] = i&&j ? D[i-1][j-1] + 1 : 1;
                //c[i][j] = a[i];
            }
            else {
                //c[i][j] = (i ? D[i-1][j] : 0) >= (j ? D[i][j-1] : 0);
                D[i][j] = max(i ? D[i-1][j] : 0, j ? D[i][j-1] : 0);
            }
    
    return D[n - 1][m - 1];
}

int main() {
	int t; cin >> t;
	
	FOR(c, 1, t+1) {
		int n, p, q; cin >> n >> p >> q;
		vi a(p+1), b(q+1);
		
		FOR(i, 0, p+1) {
			cin >> a[i];
		}
		
		FOR(i, 0, q+1) {
			cin >> b[i];
		}
		
		
		if(a.size() < b.size()) {
			swap(a, b);
		}	
		
		// a es grande
		
		FOR(i, 0, 251*251) rango[i] = INF; // unsigned memset -1
		//memset(rango, -1, sizeof rango);
		
		
		for(int i = 0; i < a.size(); i++) {
			rango[a[i]] = i;
		}
			
		cout << "Case " << c << ": " << lis(b) << endl;
		
		
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

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
#include <unordered_map>
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int adj[51][51];

int main() {
	int P, R;
	int cs = 0;
	
	while(cin >> P >> R, P || R) {
		//cout << "P " << P << " R " << R << endl;
		cs++;
		unordered_map<string, int> people;
		
		
		
		string a, b;
		
		int c = 1;
		
		FOR(i, 0, 51) {
			FOR(j, 0, 51) {
				adj[i][j] = i == j ? 0 : INF;
			}
		}
		
		FOR(i, 0, R) {
			cin >> a >> b;
			int &pa = people[a], &pb = people[b];
			
			if(!pa) pa = c++;
			if(!pb) pb = c++;
			
			adj[pa][pb] = adj[pb][pa] = 1;
		}
		
		FOR(k, 1, P + 1) {
			FOR(i, 1, P + 1) {
				FOR(j, 1, P + 1) {
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				}
			}
		}
		
		/*FOR(i, 1, P + 1) {
			FOR(j, 1, P + 1) {
				printf("%7d ", adj[i][j]);
			}
			printf("\n");
		}*/
		
		int m = -1;
		
		FOR(i, 1, P + 1) {
			FOR(j, 1, P + 1) {
				m = max(m, adj[i][j]);
			}
		}
		
		
		cout << "Network " << cs << ": ";
		
		if(m >= INF) {
			cout << "DISCONNECTED";
		} else {
			cout << m;
		}
		cout << endl << endl;
	}
}

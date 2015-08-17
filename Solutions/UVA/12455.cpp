

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
#include <unordered_map>
#include <vector>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int sisuma[2][1001], nums[21];
int n, p;

int main() {
	int t, n, p;
	cin >> t;
	
	while(t--) {
		memset(sisuma, 0, sizeof sisuma);
		sisuma[0][0] = sisuma[1][0] = true;
		
		cin >> n >> p;
		FOR(i, 0, p) {
			cin >> nums[i];
		}
		
		//sort(nums, nums + p);
		
		/*int it = 0;
		
		FOR(i, 0, p) {
			int num = nums[i];
			FOR(sum, num, n + 1) {
				sisuma[it][sum] = 
					sisuma[it ^ 1][sum] 
						|| sisuma[it ^ 1][sum - num];
				//if(sisuma[it][n])
				
			}
			it ^= 1;
		}
		cout << (sisuma[it ^ 1][n] ? "YES" : "NO") << endl;*/
		
		int suma;
		FOR(conf, 0, 1 << p) {
			suma = 0;
			for(int i = 0; i < p; i++) {
				if(conf & (1 << i)) {
					suma += nums[i];
				}
			}
			if(suma == n) break;
		}
		
		if(suma == n) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}

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
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

double adj[21][21][21];
int last[21][21][21];

void printseq(int steps, int i, int j) {
	if(steps) printseq(steps - 1, i, last[steps][i][j]);
	cout << (j + 1) << " ";
}

int main() {
	int n;
	int cs = 0;
	
	while(cin >> n) {
		FOR(i, 0, n) {
			FOR(j, 0, n) {
				last[1][i][j] = i;
				if(i != j) {
					cin >> adj[1][i][j];
				} else {
					adj[1][i][j] = 1.0;
				}
				
				FOR(steps, 2, n + 1) {
					last[steps][i][j] = i;
					adj[steps][i][j] = 0.0;
				}
			}
		}
		
		FOR(steps, 2, n + 1) {
			FOR(k, 0, n) {
				FOR(i, 0, n) {
					FOR(j, 0, n) {
						double profit = adj[steps - 1][i][k] * adj[1][k][j];
						
						//if(stp < steps[i][j] || (stp == steps[i][j] && profit > adj[i][j])) {
						//if(profit > adj[i][j] || (profit == adj[i][j] && stp < steps[i][j])) {
						//if(profit > adj[i][j] && stp <= steps[i][j]) {
						if(profit > adj[steps][i][j]) {
							//cout << "i " << i << " k " << k << " j " << j << endl;
							adj[steps][i][j] = profit;
							last[steps][i][j] = k;
						}
					}
				}
			}
		}
		
		FOR(steps, 2, n + 1) {
			FOR(i, 0, n) {
				if(adj[steps][i][i] > 1.01) {
					printseq(steps - 1, i, last[steps][i][i]);
					cout << (i + 1);
					goto end;
				}
			}
		}
		
		cout << "no arbitrage sequence exists";
		
		end:
		cout << endl;
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

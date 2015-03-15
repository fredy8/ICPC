/*
4
AA
AB
AC
AD
BA
BB
BC
BD
2
GAUSS
GALOIS
ERDOS
EULER
*/
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


string arr[200];

int func(int a, int b) {
	int k = 0;
	while(arr[a][k] == arr[b][k]) k++;
	return k+1;
}

mint main() {
	int N;
	cin >> N;
	N *= 2;
	FOR(i, 0, N) {
		cin >> arr[i];
		arr[i].pb('$');
	}
	
	sort(arr, arr + N);
	vi p[2];
	int turn = 0;
	queue<pair<ii, int> > q;
	q.push(mp(ii(0, N-1), 0));
	while(!q.empty()) {
		ii range = q.front().first;
		int col = q.front().second;
		q.pop();
		cout << range.first << " " << range.second << " " << col << endl;
		if(range.second == range.first) {
			p[turn].pb(range.first);
		} else {
			FOR(i, range.first, range.second+1) {
				int start = i;
				while(i++ < range.second+1 && arr[i][col] == arr[start][col]);
				i--;
				q.push(mp(ii(start, i), col+1));
			}
		}


		turn = !turn;
	}

	int ans[2][N];
	FOR(i, 0, 2) {
		FOR(j, 0, p[i].size()) {
			int letras = 1;
			FOR(k, 0, p[i].size()) {
				if(j != k) {
					letras = max(letras, func(p[i][j], p[i][k]));	
				}
			}
			ans[i][j] = letras; 
		}
	}

	int total = 0;
	FOR(i, 0, p[0].size()) {
		FOR(j, 0, p[1].size()) {
			total += ans[0][i] + ans[0][j];
		}
	
	}

	cout << total << endl;

}

/*
100 99
WWWBWBWWB
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

mint main() {
	int A, B;
	cin >> A >> B;
	string S;
	cin >> S;
	
	int bs = 0;
	FORC(S, it) if(*it == 'B') bs++;

	int N = S.size();
	
	int arr[S.size()];
	for(int i = N-1; i>= bs; i--) {
		if(S[i] == 'W') arr[i] = (i == 	N-1 ? -1 : arr[i+1]);
		else arr[i] = i;
		//cout << arr[i] << endl;
	}

	int k = bs;
	int ans = 0;
	for(int i = bs-1; i>=0; i--) {
		int swapCost = arr[k] == -1 ? INF : (arr[k] - i)*(A-B);
		if(S[i] == 'W') {
			if(swapCost < A) {
				ans += swapCost;
				k = arr[k]+1;
			}
			else
			ans += A;
		}
	}


	cout << ans << endl;
		
}

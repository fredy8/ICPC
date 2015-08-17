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
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

int main() {
	priority_queue<ii, vector<ii>, greater<ii> > qs;
	unordered_map<int, int> ps;
	
	string s;
	int qnum, period;
	while(cin >> s, s != "#") {
		cin >> qnum >> period;
		ps[qnum] = period;
		//cout << "q " << qnum << "p" << period << endl;
		qs.push(ii(period, qnum));
	}
	
	int k; cin >> k;
	
	while(k--) {
		ii q = qs.top(); qs.pop();
		
		cout << q.second << endl;
		qs.push(ii(q.first + ps[q.second], q.second));
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

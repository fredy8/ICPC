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
typedef long long ll;

#define SEARCH(i, j) searchm(memo, s, sub, (i), (j))

ii searchm(unordered_map<ll, ii> memo, const string &s, 
	const string &sub, int i, int j);

ii ksearch(unordered_map<ll, ii> memo, 
const string &s, const string &sub, int i, int j) {
	if(j >= sub.size() || i >= s.size()) {
		return ii(-1, -1);
	}
	
	if(s[i] == sub[j]) {
		ii include(i, 
			j == sub.size() - 1 ? i : SEARCH(i + 1, j + 1).second);
		if(include.second == -1) return SEARCH(i + 1, j);
		else return include;
	} else return SEARCH(i + 1, j);
	
}

ii searchm(unordered_map<ll, ii> memo, const string &s, 
	const string &sub, int i, int j) {
	ll key = i * 128 + j;
	auto res = memo.find(key); 
	
	if(res != memo.end())
		return res->second;
	
	else return memo[key] = ksearch(memo, s, sub, i, j);
}

int main() {
	string s;
	
	cin >> s;
	int t; cin >> t;
	
	while(t--) {
		string sub;
		cin >> sub;
		unordered_map<ll, ii> memo;
		
		ii r = SEARCH(0, 0);
		
		if(r.second == -1) {
			cout << "Not matched" << endl;
		} else {
			cout << "Matched " << r.first << " " << r.second << endl;
		}
	}
}
// a b a b a3

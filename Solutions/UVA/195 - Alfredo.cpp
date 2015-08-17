/*
1
aAzZ
*/
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<int, pair<int, int> > point;

int main() {
	int N; cin >> N;
	while(N--) {
		string word; cin >> word;
		set<char> letters;
		FORC(word, it)
			letters.insert(*it);
		word = "";
		FORC(letters, it)
			word += *it;
		sort(word.begin(), word.end());
		do cout << word << endl;
		while(next_permutation(word.begin(), word.end()));
	}
}
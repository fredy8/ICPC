
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
#include <cassert>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
typedef long long ll;

#define EXPECT(expr) if(!(expr)) return -1;
#define MATCH(c) { assert(in.peek() == c); in.ignore();}

#define L (pattern.length() - 1)

vi buildTable(string& pattern) {
    vi table(pattern.length() + 1);
    int i = 0, j = -1, m = pattern.length();
    table[0] = -1;
    while(i < m) {
        while(j >= 0 && pattern[L - i] != pattern[L - j]) j = table[j];
        i++, j++;
        //cout << "write " << i << endl;
        table[i] = j;
    }
    return move(table);
}

int find(string& text) {
	string &pattern = text;
    vi matches;
    int i = 0, j = 0, n = text.length(), m = pattern.length();
    vi table = move(buildTable(pattern));
    while(i < n) {
        while(j >= 0 && text[i] != pattern[L - j]) j = table[j];
        i++, j++;
        /*if(i == ni - j == m) {
            matches.push_back(i-j);
            j = table[j];
        }*/
    }
    // i == n
    
    return j; 
}


int main() {
	string s;
	
	while(cin >> s) {
		int j = find(s);
		//cout << "jis" << j << endl;
		
		cout << s;
		
		for(int i = s.size() - j - 1; i >= 0; i--) {
			cout << s[i];
		} cout << endl;
	}	
	
}
// a b a b a3

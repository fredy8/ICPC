/*
10 10
7 7 3 3 5 9 9 8 1 8 
QUERY 6 6 
UPDATE 3 4 
QUERY 0 1 
QUERY 0 5 
QUERY 4 7 
QUERY 3 5 
QUERY 0 2 
QUERY 4 6 
UPDATE 6 10 
QUERY 0 9
10 10
7 7 3 3 5 9 9 8 1 8 
QUERY 6 6 
UPDATE 3 4 
QUERY 0 1 
QUERY 0 5 
QUERY 4 7 
QUERY 3 5 
QUERY 0 2 
QUERY 4 6 
UPDATE 6 10 
QUERY 0 9
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
#include <ctime>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int facs[2001][2001];
int cfacs[2001];

int visited[5][2001][2001];

void all(string &s, int i, int sum, int prod) {
	if(visited[i][sum][prod]) return;
	visited[i][sum][prod] = true;
	if(i == 4 && sum = 0 && prod == 1) {
		cout << s << endl;
	} else {
		int siz = s.size();
		FOR(f, 0, cfacs[
		
		ss += to_string(
	}
}

int main() {
    for(int p = 2; p < 45; p++) {
		for(int n = p * p; n <= 2000; n += p) {
			facs[n][cfacs[n]++] = p;
		}
	}
}

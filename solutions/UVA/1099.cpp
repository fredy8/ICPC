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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int poss[101][65535];


int friends[20];
int f;
bool possiblem(int w, bitset<15> requests, unordered_map<int, vi> &sumc)
;

template<size_t N>
int dot(bitset<N> a) {
	int res = 0;
	FOR(i, 0, f) {
		res += a[i] * friends[i];
	}
	return res;
}
bool possible(int w, bitset<15> requests, unordered_map<int, vi> &sumc) {
	int ip = dot(requests);
	int h = ip / w;
	
	if(requests.count() == 1) {
		if(ip == w*h)
			return true;
		else return false;
	} else {
		FOR(i, 1, w) {
			vi &opts = sumc[i];
			
			FORC(opts, it) {
				if(requests.to_ulong() & *it == *it) {
					return possiblem(i, bitset<15>(*it), sumc) 
						&& possiblem(w - i, bitset<15>(requests.to_ulong() & ~(*it)), sumc);
				}
			}
		}
		
		FOR(i, 1, h) {
			vi &opts = sumc[i];
			
			FORC(opts, it) {
				if(requests.to_ulong() & *it == *it) {
					return possiblem(w, bitset<15>(*it), sumc) 
						&& possiblem(w, bitset<15>(requests.to_ulong() & ~(*it)), sumc);
				}
			}
		}
	}
}

bool possiblem(int w, bitset<15> requests,  unordered_map<int, vi> &sumc) {
	if(poss[w][requests.to_ulong()] != -1) {
		return poss[w][requests.to_ulong()];
	} else {
		return poss[w][requests.to_ulong()]
			= possible(w,requests,sumc);
	}
}

int main() {
	int n, c = 0;
	
	while(cin >> f, f) {
		c++;
		int x, y; cin >> x >> y;
		
		cout << "Case " << c <<": ";
		
		unordered_map<int, vi> sumc;
		
		memset(poss, -1, sizeof poss);
		
		int total = 0;
		FOR(i,0,f) cin >> friends[i], total += friends[i];
		
		if(total != x * y) {
			cout << "No" << endl;
			continue;
		}
		
		FOR(i, 0, 1<<16 - 1) {
			bitset<15> bs(i);
			int sum = dot(bs);
			sumc[sum].push_back(i);
		}
		
		if(possible(x, 1 << 16 - 1, sumc))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}

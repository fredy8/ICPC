
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

struct UnionFindDS {
    vi tree, sizes;
    int N;
    UnionFindDS(int n) : N(n) {
        tree.reserve(n);
        FOR(i, 0, n) tree[i] = i;
        sizes.assign(n, 1);
    }
    int root(int i) { return (tree[i] == i) ? i : (tree[i] = root(tree[i]));}
    int countSets() { return N;}
    int getSize(int i) { return sizes[root(i)];}
    bool connected(int i, int j) { return root(i) == root(j);}
    void connect(int i, int j) {
        int ri = root(i), rj = root(j);
        if(ri != rj) {
            N--;
            sizes[rj] += sizes[ri];
            tree[ri] = rj;
        }
    }
};

int main() {
	int n, m;
	cin >> n;
	while(n--) {
		cin >> m;
		
		int c = 0;
		UnionFindDS friends(100000);
		unordered_map<string, int> peop;
		
		while(m--) {
			string a, b;
			cin >> a >> b;
			
			if(peop.find(a) == peop.end()) {
				peop[a] = c++;
			}
			
			if(peop.find(b) == peop.end()) {
				peop[b] = c++;
			}
			
			int x;
			
			friends.connect(x = peop[a], peop[b]);
			cout << friends.getSize(x) << endl;
		}
	}
	
	
}
// a b a b a3

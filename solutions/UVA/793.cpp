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
#define INF 100000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

// la descripcion del problema no decia que habia mas de un caso ni que habia
// que leer el numero de casos al principio, ni que habia que imprimir
// una linea entre los casos, lo descubri en los foros

struct UnionFindDS {
    vi tree;
    UnionFindDS(int n) { FOR(i, 0, n) tree.push_back(i); }
    int root(int i) { return tree[i] == i ? i : tree[i] = root(tree[i]); }
    bool connected(int i, int j) {return root(i) == root(j);}
    void connect(int i, int j) { tree[root(i)] = tree[root(j)]; }
};

inline void ignores() {
	while(isspace(cin.peek())) cin.ignore();
}

int main() {
	int cs; cin >> cs;
	
	while(cs--) {
		int n; cin >> n;
		
		UnionFindDS net(n + 1);
		
		char x;
		int i, j;
		
		int succ = 0, failed = 0;
		
		//if(!getline(cin, s)) goto skip;
		
		
		while(ignores(), isalpha(cin.peek())) {
			cin >> x >> i >> j;
			if(x == 'c') {
				net.connect(i, j);
				
				
			} else if(x == 'q') {
				if(net.connected(i, j))
				//if(mat[i][j])
					succ++;
				else
					failed++;
			}
		}
		
		cout << succ << "," << failed << endl;
		
		if(cs > 0)
			cout << endl;
	}
}

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


int dist[81][81];

int editDistance(string &A, string &B) {
    int n = A.length(), m = B.length();
    dist[0][0] = 0;
    FOR(i, 1, n+1) dist[i][0] = i;
    FOR(j, 1, m+1) dist[0][j] = j;
    FOR(i, 1, n+1)
        FOR(j, 1, m+1)
            dist[i][j] = 
            min(dist[i-1][j-1] + (A[i-1] != B[j-1]), 
            min(dist[i-1][j] + 1, 
				dist[i][j-1] + 1));
    return dist[n][m];
}

int printsol(string &A, string &B,int i, int j, int depth) {
	//cout << "printsol "<< depth << ":" << i << ", " << j << endl;
	//if(depth == 0) return A.size();
	if(depth && (i || j)) {
		if (false); 
		 else if(i > 0 && dist[i][j] == dist[i - 1][j] + 1) {
			int ch = printsol(A,B,i-1,j, depth-1);
			
			cout << depth << " Delete " <<(ch + i) << endl;
			
			return ch - 1;
		} else if(j > 0 && dist[i][j] == dist[i][j - 1] + 1) {
			int ch = printsol(A,B,i,j-1, depth-1);
			//cout << "i " << i << "," << j << endl;
			cout << depth << " Insert " <<(ch + i + 1)<<","<<B[j - 1] << endl;
			
			return ch + 1;
		} else if(i > 0 && j > 0 && dist[i][j] == dist[i-1][j-1] + (A[i - 1] != B[j - 1])) {
			int ch = printsol(A,B,i-1,j-1, depth-(A[i - 1] != B[j - 1]));
			
			if(A[i - 1] != B[j - 1]) 
				cout << depth << " Replace " <<(ch + i)<<","<<B[j-1]<<endl; 
				
			return ch;
		} else assert(false);
		
		
	}
	return 0;
}
	
	/*if(i && j) {
		cout << i << "," << j << endl;
		int rep = i&&j ? dist[i-1][j-1] + (A[i-1] != B[j-1]) : INF,
			del = i ? dist[i-1][j] + 1 : INF,
			ins = j ? dist[i][j-1] + 1 : INF,
			m = dist[i][j];
			
		if(m == del) {
			printsol(A,B,i-1,j, depth-1);
			cout << depth << " Delete " <<(i-1) << endl;
		} else if(m == ins) {
			printsol(A,B,i,j-1,depth-1);
			cout << depth << " Insert " <<i<<","<<A[i-1] << endl;
		} else if(m == rep) {
			printsol(A,B,i-1, j-1, depth - (A[i-1] != B[j-1]));
			if(A[i-1] != B[j-1]) 
				cout << depth << " Replace " <<(i-1)<<","<<B[j-1]<<endl; 
		} else assert(false);
	}*/


int main() {
	string a, b;
	int c = 0;
	
	while(getline(cin, a) && getline(cin, b)) {
		if(c) cout << endl;
		int de;
		cout << (de = editDistance(a, b)) << endl;
		printsol(a,b,a.size(), b.size(), de);
		
		/*FOR(i, 0, a.size() +1) {
			FOR(j, 0, b.size() +1) {
				printf("%3d ", dist[i][j]);
			}cout << endl;
		}*/
		c = 1;		
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

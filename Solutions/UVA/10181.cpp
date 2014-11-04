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
#include <random>
#define INF 1000000000 // avoid overflow
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(auto it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int heurs[4][4], tab[4][4];

int put(int num, int i, int j) {
	tab[i][j] = num;
	heurs[i][j] = std::abs((num - 1) % 4 - j) + std::abs((num - 1) / 4 - i);
}

bool ordered() {
	FOR(i, 0, 4)
		FOR(j, 0, 4) {
			if(tab[i][j] != (i * 4 + j + 1) % 16) return false;
		}
		
	return true;
}

int lcrow(int r) {
	int lc = 0;
	FOR(i,0,3) {
		if(tab[r][i] && (tab[r][i] - 1) / 4 == r){
			FOR(j,i+1,4) {
				if(tab[r][j] && (tab[r][j] - 1) / 4 == r) {
					if(tab[r][i] > tab[r][j]) {
						lc++;
					}
				}
			}
		}
	}
	return lc * 2;
}

int lccol(int r) {
	int lc = 0;
	FOR(i,0,3) {
		if(tab[i][r] && (tab[i][r] - 1) % 4 == r){
			FOR(j,i+1,4) {
				if(tab[j][r] && (tab[j][r] - 1) % 4 == r) {
					if(tab[i][r] > tab[j][r]) {
						lc++;
					}
				}
			}
		}
	}
	return lc * 2;
}

int newdepth;


int maxdepth;

string out;

bool solve(int hist, int heur, int i, int j, char prev = 0) {
	if(ordered()) return true;
	if(hist + heur > maxdepth) {
		newdepth = min(newdepth, hist + heur);
		return false;
	}
	if(j < 3 && prev != 'L') {
		int newheur = 0;
		newheur -= lccol(j+1) + lccol(j) + lcrow(i);
		put(tab[i][j+1], i, j);
		newheur += heur - heurs[i][j+1] + heurs[i][j];
		newheur += lccol(j+1) + lccol(j) + lcrow(i);
		heurs[i][j + 1] = tab[i][j+1] = 0;
		if(solve(hist + 1, 
				newheur, 
				i, 
				j+1, 
				'R')) {
			out.push_back('R');
			return true;
		}
		put(tab[i][j], i, j+1);
		heurs[i][j] = tab[i][j] = 0;
	}
	
	
	if(i > 0 && prev != 'D') {
		int newheur = 0;
		newheur -= lcrow(i-1) + lccol(j) + lcrow(i);
		put(tab[i-1][j], i, j);
		newheur += lcrow(i-1) + lccol(j) + lcrow(i);
		newheur += heur - heurs[i - 1][j] + heurs[i][j];
		heurs[i - 1][j] = tab[i - 1][j] = 0;
		if(solve(hist + 1, 
				newheur, 
				i - 1, 
				j, 
				'U')) {
			out.push_back('U');
			return true;
		}
		put(tab[i][j], i-1, j);
		heurs[i][j] = tab[i][j] = 0;
	}
	
	if(j > 0 && prev != 'R') {
		int newheur = 0;
		newheur -= lccol(j-1) + lccol(j) + lcrow(i);
		put(tab[i][j-1], i, j);
		newheur += lccol(j-1) + lccol(j) + lcrow(i);
		newheur += heur - heurs[i][j-1] + heurs[i][j];
		heurs[i][j - 1] = tab[i][j-1] = 0;
		if(solve(hist + 1, 
				newheur, 
				i, 
				j-1, 
				'L')) {
			out.push_back('L');
			return true;
		}
		put(tab[i][j], i, j-1);
		heurs[i][j] = tab[i][j] = 0;
	}
	
	if(i < 3 && prev != 'U') {
		int newheur = 0;
		newheur -= lcrow(i+1) + lccol(j) + lcrow(i);
		put(tab[i+1][j], i, j);
		newheur += lcrow(i+1) + lccol(j) + lcrow(i);
		newheur += heur - heurs[i + 1][j] + heurs[i][j];
		heurs[i + 1][j] = tab[i + 1][j] = 0;
		if(solve(hist + 1, 
				newheur, 
				i + 1, 
				j, 
				'D')) {
			out.push_back('D');
			return true;
		}
		put(tab[i][j], i+1, j);
		heurs[i][j] = tab[i][j] = 0;
	}
	
	
	
	return false;
}

int main() {
	int t; cin >> t;
	
	/*FOR(i, 0, 4) FOR(j,0,4) tab[i][j] = i * 4 + j;
	shuffle(((int *)tab), ((int *)tab) + 16, mt19937(random_device()()));
	FOR(i, 0, 4) {FOR(j,0,4) cout << tab[i][j] << " "; cout << endl;}*/
	
	while(t--) {
		int heur = 0, i0, j0;
		FOR(i,0,4)
			FOR(j,0,4) {
				cin >> tab[i][j];
			}
		
		//string sol;
		out = "";
		
		bool solved = false;
		
		newdepth = 0;
		
		while(newdepth < 53) {
		
			heur = 0;
			FOR(i,0,4)
				FOR(j,0,4) {
					if(tab[i][j]) {
						put(tab[i][j], i, j);
						heur += heurs[i][j];
					} else {
						heurs[i][j] = 0;
						i0 = i; j0 = j;
					}
				}
				
			FOR(i, 0, 4) heur += lcrow(i);
			FOR(j, 0, 4) heur += lccol(j);
			
			maxdepth = newdepth;
			newdepth = INF;
			//cout << "trying " << maxdepth << endl;
			
			if(solved = solve(0, heur, i0, j0)) break;
		}
		if(solved) reverse(out.begin(), out.end()), cout << out << endl;
		else cout << "This puzzle is not solvable." << endl;
	}
}

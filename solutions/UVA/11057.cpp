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
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int books[10001];
int price[2000003];

int main() {
	int n;
	
	while(cin >> n) {
		memset(price, 0, sizeof price);
		//memset(mprice, 0, sizeof mprice);
		for(int i = 0; i < n; i++) {
			cin >> books[i];
			price[books[i]]++;
			//cout << "read" << books[i] << endl;
		}
		int m;
		cin >> m;
		
		int best_dif = INF, best_price = INF;
		
		for(int i = 0; i < n; i++) {
			if(books[i] < m && price[m - books[i]]
				&& (books[i] * 2 != m || price[books[i]] > 1)) {
				int price = max(books[i], m - books[i]);
				int dif = price - (m - price);
				
				/*cout 
					<< "considering " 
					<< books[i] <<","<<(m - books[i]) 
					<< " difis " << dif << endl;/**/
				
				if(dif < best_dif) {
					best_dif = dif;
					best_price = price;
				}
			}
		}
		
		cout 
			<< "Peter should buy books whose prices are "
			<< (m - best_price) << " and " << best_price << "." << endl << endl;
	}
}

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
#include <cstdlib>
#include <fstream>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

#define MAX 10000000
bitset<MAX> sieve;
void buildSieve() {
	sieve.set();
	sieve[0] = sieve[1] = 0;
	int root = sqrt(MAX);
	FOR(i, 2, MAX)
		if (sieve[i] && i <= root)
			for(int j = i*i; j < MAX; j+=i)
				sieve[j] = 0;
}

vi primesList;
void buildPrimesList() {
	if(!sieve[2])
		buildSieve();
	primesList.reserve(MAX/log(MAX));
	FOR(i, 2, MAX+1)
		if(sieve[i])
			primesList.pb(i);
}

int main() {
    buildPrimesList();
    int np = primesList.size(), intervalos = 0;
    ofstream arc("output.txt");
    for (int pi = 0; pi < np-1; pi++) {
        if (pi%10000 == 0) cout << primesList[pi] << " " << intervalos << endl;
        int p = primesList[pi], q = primesList[pi+1];
        //int p = 2183, q = 2201;
        int size = q-p-1;
        vector<vector<bool> > primRel(size, vector<bool>(size, false));
        vi I(size, 1), D(size, 1);
        //bool primRel[size][size] = {{false}};
        for (int i = 0; i < size; i++) {
            for (int j = i+1; j < size; j++) {
                primRel[i][j] = primRel[j][i] = (__gcd(p+1+i, p+1+j) == 1);
            }
        }
        for (int i = 0; i < size; i++) {
            int j;
            j = i-1;
            while (j >= 0 && primRel[i][j]) {
                j--;
                I[i]++;
            }
            j = i+1;
            while (j < size && primRel[i][j]) {
                j++;
                D[i]++;
            }
            //cout << "=" << p+i+1 << ": " << I[i] << " " << D[i] << endl;
        }
        for (int i = 0; i < size; i++) {
            int m = D[i];
            for (int j = i+1; j < size; j++) {
                int e = j-i;
                if (I[j] <= e) {
                    if (m <= e) {
                        arc << p + i + 1 << " " << p + j + 1 << endl;
                        intervalos++;
                    }
                } else if (e+D[j] > m) {
                    m = e+D[j];
                }
            }
        }
    }
    arc.close();
}

/*int main() {
    buildPrimesList();
    int np = primesList.size(), d, md = 0, mi = -1;
    ll s = 0;
    for (int i = 0; i < np-1; i++) {
        d = primesList[i+1] - primesList[i];
        s += (d-1)*(d-1);
        if (d > md) {
            md = d;
            mi = i;
        }
    }
    cout << md << " = " << primesList[mi+1] << " - " << primesList[mi] << endl;
    cout << "operaciones: " << s << endl;
}*/

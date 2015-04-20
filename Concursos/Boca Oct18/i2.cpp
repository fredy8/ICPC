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

int main() {
    ifstream ent("output.txt");
    ofstream sal("output2.txt");
    int a, b, t = 0;
    sal << "intervalos[][2] = {";
    while (ent >> a >> b) {
        sal << (t ? "," : "") << "{" << a << "," << b << "}";
        if ((t+1) % 100 == 0) sal << endl;
        t++;
    }
    sal << "};" << endl;
    sal << t << endl;
    ent.close();
    sal.close();
}

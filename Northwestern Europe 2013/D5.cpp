#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
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
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

template <typename T>
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }
void printNum(int num) {
    if(num > 999)
        printf("0x%x", num);
    else
        printf("%d", num);
}


mint main() {
    ifstream ent("outputD.txt");
    ofstream sal("outputD2.txt");
    string line;
    //int cnt = 0;
    while (getline(ent, line)) {
        int n, k, d, r, t;
        string dstr, rstr;
        n = line[4] - '0';
        k = line[7] - '0';
        dstr = line.substr(10, line.find(']', 10) - 10);
        rstr = line.substr(line.find('=')+2);
        rstr = rstr.substr(0, rstr.length()-1);
        d = toNum<int>(dstr);
        r = toNum<int>(rstr);
        //cout << n << " " << k << " " << d << " " << r << endl;
        //if (cnt > 40) break;
        //cnt++;
        t = (8*k+n) + d*64;

        cout << "a[";
        printNum(t);
        cout << "]=";
        printNum(r);
        cout << ";";
    }
    ent.close();
    sal.close();
}


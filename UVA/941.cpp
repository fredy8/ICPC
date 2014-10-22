/*
1
00112233445566778899
2432902008176639999
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
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

long long fact(int n) {
    long long res = 1;
    FOR(i, 2, n+1) res*=i;
    return res;
}

//seq must be sorted
string nthPermutation(string seq, long long permNum) {
    if(!seq.length())
        return "";
    long long f = fact(seq.length() - 1);
    int q = permNum / f;
    long long r = permNum % f;
    return seq[q] + nthPermutation(seq.substr(0, q) + seq.substr(q+1), r);
}

int main() {
    int TC;
    cin >> TC;
    while(TC--) {
        string seq;
        long long permNum;
        cin >> seq >> permNum;
        sort(seq.begin(), seq.end());
        cout << nthPermutation(seq, permNum) << endl;
    }
}
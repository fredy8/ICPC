#ifndef sh
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
#endif

string toBaseN(long long num, int N) {
    string converted;
    for(long long div=num; div; div /= N) {
        int value = div % N;
        char c = value > 9 ? value + 'A' - 10 : value + '0';
        converted = c + converted;
    }
    return converted;
}
long long toBase10(string num, int b) {
    long long res = 0, k = 1;
    for(int i=num.length()-1; i>=0; i--) {
        char c = num[i];
        int value = c > '9' ? c - 'A' + 10 : c - '0';
        res += (value)*k;
        k*=b;
    }
    return res;
}
int main()
{
    string num;
    int a, b;
    while (cin >> num >> a >> b) {
        long long n = toBase10(num, a);
        num = toBaseN(n, b);
        if (num.length() > 7)
            num = "ERROR";
        cout << setw(7) << num << endl;
    }
}

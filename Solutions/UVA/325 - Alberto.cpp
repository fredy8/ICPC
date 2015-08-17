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

bool validInteger(string num)
{
    if (num.length() == 0) return false;
    if (num[0] == '+' || num[0] == '-') num = num.substr(1);
    for (int i = 0; i < num.length(); i++)
        if (num[i] < '0' || '9' < num[i])
            return false;
    return true;
}
bool validDecimal(string dec)
{
    if (dec.length() == 0) return false;
    int point = dec.find('.');
    if (point == -1) return false;
    return validInteger(dec.substr(0, point)) && validInteger(dec.substr(point+1));
}
bool validPascal(string pas)
{
    int e = pas.find('e');
    if (e == -1) e = pas.find('E');
    if (e == -1) return validDecimal(pas);
    string bef = pas.substr(0, e), aft = pas.substr(e+1);
    return (validInteger(bef) || validDecimal(bef)) && validInteger(aft);
}
int main()
{
    string pas;
    while (cin >> pas && pas != "*")
        cout << pas << " is " << (validPascal(pas) ? "" : "il") << "legal." << endl;
}

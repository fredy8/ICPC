//624

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

char cowInv[] = {'V', 'U', 'C', 'D'};
map <char, int> cowMap;
void fillMap() {
    for (int i = 0; i < 4; i++)
        cowMap[cowInv[i]] = i;
}
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
string toCow(string b)
{
    string cow;
    for (int i = 0; i < b.length(); i++)
        cow += cowInv[b[i]-'0'];
    while (cow.length() < 8)
        cow = "V" + cow;
    return cow;
}
string toBase4(string cow)
{
    string b = "";
    for (int i = 0; i < cow.length(); i++)
        b += (cowMap[cow[i]] + '0');
    return b;
}
int main()
{
    fillMap();
    int casos;
    cin >> casos;
    cout << "COWCULATIONS OUTPUT" << endl;
    while (casos--) {
        string num1, num2;
        int n1, n2;
        cin >> num1 >> num2;
        num1 = toBase4(num1);
        num2 = toBase4(num2);
        n1 = toBase10(num1, 4);
        n2 = toBase10(num2, 4);
        //cout << num1 << " " << n1 << " " << num2 << " " << n2 << endl;
        for (int i = 0; i < 3; i++) {
            string op;
            cin >> op;
            if (op == "A") n2 += n1;
            else if (op == "R") n2 /= 4;
            else if (op == "L") n2 *= 4;
            else if (op == "N") {}
        }
        num2 = toBaseN(n2, 4);
        num2 = toCow(num2);
        cin >> num1;
        if (num1 == num2) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    cout << "END OF OUTPUT" << endl;
}

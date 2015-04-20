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
    using namespace std; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi; typedef pair<char, char> cc;
#endif

void fun(string from, string to, string path, stack<char> s, int pos1, int pos2, set<string> &sol)
{
    if (pos1 == from.length()) {
        if (s.empty()) {
            sol.insert(path);
        } else if (s.top() == to[pos2]) {
            s.pop();
            fun(from, to, path+" o", s, pos1, pos2+1, sol);
        }
    } else {
        if (!s.empty() && s.top() == to[pos2]) {
            stack<char> r = s;
            r.pop();
            fun(from, to, path+" o", r, pos1, pos2+1, sol);
        }
        s.push(from[pos1]);
        fun(from, to, path += " i", s, pos1+1, pos2, sol);
    }
}

set<string> solve(string from, string to)
{
    set<string> v;
    stack<char> s;
    if (from.length() != to.length()) return v;
    fun(from, to, "", s, 0, 0, v);
    return v;
}

int main()
{
    string from, to;
    while (cin >> from >> to) {
        set<string> v = solve(from, to);
        cout << "[" << endl;
        for(set<string>::iterator iter = v.begin(); iter != v.end(); iter++)
            cout << (*iter).substr(1) << endl;
        cout << "]" << endl;
    }
}

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

map<char, int> v;
bool visited[26];

struct Edge {
    int to, weight;
    Edge(int to, int weight = 1) : to(to), weight(weight) {}
};
struct Graph {
    int V;
    vector<vector<Edge> > edges;
    bool undirected;
    Graph(int v, bool undirected = true) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
    void connect(int from, Edge edge) {
        edges[from].push_back(edge);
        if(undirected) {
            int aux = edge.to;
            edge.to = from;
            edges[aux].push_back(edge);
        }
    }
    void visitGraph(int v, int &cnt) {
        if (visited[v]) return;
        cnt++;
        visited[v] = true;
        for (int i = 0; i < edges[v].size(); i++) {
            visitGraph(edges[v][i].to, cnt);
        }
    }
};

int main()
{
    int casos;
    cin >> casos;
    while (casos--) {
        string tmp;
        vector<cc> aristas;
        while (cin >> tmp && tmp[0] != '*') {
            cc aux;
            aux.first = tmp[1];
            aux.second = tmp[3];
            aristas.pb(aux);
        }
        cin >> tmp;
        for (int i = 0; i < tmp.length(); i += 2) {
            v[tmp[i]] = i/2;
            visited[i/2] = false;
        }
        Graph g(tmp.length()/2+1);
        for (int i = 0; i < aristas.size(); i++) {
            g.connect(v[aristas[i].first], Edge(v[aristas[i].second]));
        }
        int t = 0, cnt = 0, acn = 0;
        for (int i = 0; i < g.V; i++) {
            cnt = 0;
            g.visitGraph(i, cnt);
            acn += (cnt == 1);
            t += (cnt > 1);
        }
        cout << "There are " << t << " tree(s) and " << acn << " acorn(s)." << endl;
    }
}

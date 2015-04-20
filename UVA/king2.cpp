
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

#include <sys/resource.h>

#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
typedef int mint;
#define int ll
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
    ll to, weight;
    Edge(ll to, ll weight = 1) : to(to), weight(weight) {}
};
struct Graph {
    ll V; bool undirected;
    vector<vector<Edge> > edges;
    Graph(ll v, bool undirected = true) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
    void connect(ll from, Edge edge) {
        edges[from].pb(edge);
        if(undirected) {
            ll aux = edge.to;
            edge.to = from;
            edges[aux].pb(edge);
        }
    }
};

vii longestPathDown;
vii secondLongestPathDown;
vi parent;

ll getLongestPathDown(Graph &g, ll cv) {
    FORC(g.edges[cv], edge) {
        if(edge->to != parent[cv]) {
            parent[edge->to] = cv;
            ll pathDownLength = 1 + getLongestPathDown(g, edge->to);
            
            ii a = ii(edge->to, pathDownLength);
            if(pathDownLength > longestPathDown[cv].second) {
                //cout << cv << endl;
            	//return 0;
                secondLongestPathDown[cv] = longestPathDown[cv];
                longestPathDown[cv] = ii(edge->to, pathDownLength);
            } else if(pathDownLength > secondLongestPathDown[cv].second) {
            	//return 0;
                secondLongestPathDown[cv] = ii(edge->to, pathDownLength);
            }
        }
    }
    return longestPathDown[cv].second;
}

//g is an unrooted tree
void getLongestPath(Graph &g, vii &longestPath) {
    longestPath.assign(g.V, ii(-1, 0));
    vii secondLongestPath(g.V, ii(-1, 0));
    longestPathDown.assign(g.V, ii(-1, 1)), secondLongestPathDown.assign(g.V, ii(-1, 1)); 
    parent.assign(g.V, -1);
    getLongestPathDown(g, 0);
    queue<ll> q;
    q.push(0);
    //return;
    while(!q.empty()) {
        ll cv = q.front(); q.pop();
        FORC(g.edges[cv], edge) {
            if(parent[cv] != edge->to)
                q.push(edge->to);
        }
        
        if(parent[cv] == -1) {
            longestPath[cv] = longestPathDown[cv];
            secondLongestPath[cv] = secondLongestPathDown[cv];
        } else {
            ii longestPathThroughParent = ii(parent[cv], (longestPath[parent[cv]].first != cv ? longestPath[parent[cv]].second : secondLongestPath[parent[cv]].second)+1);
            if(longestPathThroughParent.second >= longestPathDown[cv].second) {
                longestPath[cv] = longestPathThroughParent;
                secondLongestPath[cv] = longestPathDown[cv];
            } else if(longestPathThroughParent.second >= secondLongestPathDown[cv].second) {
                longestPath[cv] = longestPathDown[cv];
                secondLongestPath[cv] = longestPathThroughParent;
            } else {
                longestPath[cv] = longestPathDown[cv];
                secondLongestPath[cv] = secondLongestPathDown[cv];
            }
        }
    }
}

mint main() {
#if 0
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %lld\n", result);
            }
        }
    }

    #endif

    ll N, Q;
    cin >> N >> Q;

    Graph gN(N), gQ(Q);

    FOR(i, 0, N-1) {
        ll from, to;
        cin >> from >> to;
        gN.connect(from-1, to-1);
    }

    FOR(i, 0, Q-1) {
        ll from, to;
        cin >> from >> to;
        gQ.connect(from-1, to-1);
    }

    vii lpN, lpQ;
    getLongestPath(gN, lpN);
    getLongestPath(gQ, lpQ);

    //return 0;

    ll Ndiameter = 0, Qdiameter = 0;
    FOR(i, 0, N)
        Ndiameter = max(Ndiameter, lpN[i].second-1);
    FOR(i, 0, Q)
        Qdiameter = max(Qdiameter, lpQ[i].second-1);

    //cout << "N diam: " << Ndiameter << endl;
    //cout << "Q diam: " << Qdiameter << endl;
    //cout << "Diameters: " << endl;

    ll NcitiesWithExactlyNDiameter[50000] = {0};
    FOR(i, 0, N) {
        ll diameter = lpN[i].second - 1;
        NcitiesWithExactlyNDiameter[diameter]++;
        //cout << i << ": " << diameter << " " << NcitiesWithExactlyNDiameter[diameter] << endl;
    }

    ll NcitiesWithAtMostNDiameter[50000] = {0};
    ll Nsum[50000] = {0};
    NcitiesWithAtMostNDiameter[0] = NcitiesWithExactlyNDiameter[0];
    Nsum[0] = 0;
    FOR(i, 1, 50000) {
        NcitiesWithAtMostNDiameter[i] = NcitiesWithAtMostNDiameter[i-1] + (i < N ? NcitiesWithExactlyNDiameter[i] : 0);
        Nsum[i] = Nsum[i-1] + (i < N ? NcitiesWithExactlyNDiameter[i] : 0)*i;
        //cout << i << ": " << NcitiesWithAtMostNDiameter[i] << " " << Nsum[i] << endl;
    }

    ll currentTotalDiameter = max(Ndiameter, Qdiameter);

    //cout << "ll: " << currentTotalDiameter << endl;
    long long ans = 0;
    FOR(i, 0, Q) {
        ll diameter = lpQ[i].second-1;
        ll k = currentTotalDiameter - diameter - 2;
        //cout << k << endl;
        ll sumOfDiametersIfIConnectToOtherKingdom;

        if(k >= 0)
            sumOfDiametersIfIConnectToOtherKingdom = (Nsum[N-1] - Nsum[k] + (diameter + 1)*(NcitiesWithAtMostNDiameter[N-1] - NcitiesWithAtMostNDiameter[k])) + NcitiesWithAtMostNDiameter[k]*currentTotalDiameter;
        else
            sumOfDiametersIfIConnectToOtherKingdom = (Nsum[N-1] + diameter*N + N);

        //cout << sumOfDiametersIfIConnectToOtherKingdom << endl;

        ans += sumOfDiametersIfIConnectToOtherKingdom;
    }

    //cout << N*Q << endl;

    double d = ((double)ans)/(N*Q);
    printf("%.3lf\n", d);
}

int getLongestPathDown(Graph &g, int cv, vii &longestPathDown, vii &secondLongestPathDown, vi &parent) {
    FOR(i, 0, g.edges[cv].size()) {
        int to = g.edges[cv][i].to;
        if(to != parent[cv]) {
            parent[to] = cv;
            int pathDownLength = 1 + getLongestPathDown(g, to, longestPathDown, secondLongestPathDown, parent);
            if(pathDownLength > longestPathDown[cv].second) {
                secondLongestPathDown[cv] = longestPathDown[cv];
                longestPathDown[cv] = ii(to, pathDownLength);
            } else if(pathDownLength > secondLongestPathDown[cv].second) {
                secondLongestPathDown[cv] = ii(to, pathDownLength);
            }
        }
    }
    return longestPathDown[cv].second;
}

//g is an unrooted tree
void getLongestPath(Graph &g, vii &longestPath) {
    longestPath.assign(g.V, ii(-1, 0));
    vii longestPathDown(g.V, ii(-1, 1)), secondLongestPathDown(g.V, ii(-1, 1)), secondLongestPath(g.V, ii(-1, 0));
    vi parent(g.V, -1);
    getLongestPathDown(g, 0, longestPathDown, secondLongestPathDown, parent);
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
        int cv = q.front(); q.pop();
        FOR(i, 0, g.edges[cv].size()) {
            int to = g.edges[cv][i].to;
            if(to != parent[cv]) 
                q.push(g.edges[cv][i].to);
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
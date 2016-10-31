/* Eulerian Path
O(V+E)
Partitions the vertices of a directed graph into strongly connected components.
A strongly connected component is a subset of a graph where every vertex is reachable from every other vertex.
Returns V where V_i is the index of the component of node i.
*/
vi low1, num1, components;
int counter1, SCCindex;
vector<bool> visited;
stack<int> S;

void dfs(Graph &g, int cv) {
  low1[cv] = num1[cv] = counter1++;
  S.push(cv);
  visited[cv] = true;
  FORC(g.edges[cv], edge) {
    if(num1[edge->to] == -1)
      dfs(g, edge->to);
    if(visited[edge->to])
      low1[cv] = min(low1[cv], low1[edge->to]);        
  }
  if(low1[cv] == num1[cv]) {
    int index = SCCindex++;
    while(true) {
      int v = S.top(); S.pop(); visited[v] = 0;
      components[v] = index;
      if (cv == v)
        break;
    }
  }
}

vi stronglyConnectedComponents(Graph &g) {
  counter1 = 0, SCCindex = 0;
  visited = vector<bool>(g.V, 0);
  num1 = vi(g.V, -1), low1 = vi(g.V, 0), components = vi(g.V, 0);
  S = stack<int>();
  FOR(i, 0, g.V)
    if(num1[i] == -1)
      dfs(g, i);
  return components;
}

#define MAX_V 400
void floydWarshall(Graph &g, int distance[MAX_V][MAX_V])
{
    FOR(i, 0, g.V-1)
        FOR(j, i, g.V)
            distance[i][j] = distance[j][i] = INF*(i != j);
    FOR(i, 0, g.V)
        FOR(j, 0, g.edges[i].size())
            distance[i][g.edges[i][j].to] = g.edges[i][j].weight;
    FOR(i, 0, g.V)
        FOR(j, 0, g.V)
            FOR(k, 0, g.V)
                distance[j][k] = min(distance[j][k], distance[j][i] + distance[i][k]);
}
int editDistance(string A, string B) {
    int n = A.length(), m = B.length();
    int dist[n+1][m+1];
    dist[0][0] = 0;
    FOR(i, 1, n+1) dist[i][0] = i;
    FOR(j, 1, m+1) dist[0][j] = j;
    FOR(i, 1, n+1)
        FOR(j, 1, m+1)
            dist[i][j] = min(dist[i-1][j-1] + (A[i-1] != B[j-1]), min(dist[i-1][j] + 1, dist[i][j-1] + 1));
    return dist[n][m];
}
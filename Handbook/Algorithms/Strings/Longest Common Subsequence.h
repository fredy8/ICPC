string LCS(string a, string b) {
    int n = a.length(), m = b.length();
    int D[n][m];
    char c[n][m];
    FOR(i, 0, n)
        FOR(j, 0, m)
            if(a[i] == b[j]) {
                D[i][j] = i&&j ? D[i-1][j-1] + 1 : 1;
                c[i][j] = a[i];
            }
            else {
                c[i][j] = (i ? D[i-1][j] : 0) >= (j ? D[i][j-1] : 0);
                D[i][j] = max(i ? D[i-1][j] : 0, j ? D[i][j-1] : 0);
            }
    string lcs;
    while(n-- && m--) {
        if(c[n][m] == 0) n++;
        else if(c[n][m] == 1) m++;
        else lcs = c[n][m] + lcs;
    }
    return lcs;
}
#define MAX_N 100010

int RA[MAX_N], SA[MAX_N], LCP[MAX_N];

void countingSort(int k, char S[], int n) {
    vi c(max(300, n), 0), tempSA(n);
    int sum = 0, maxi = max(300, n);
    FOR(i, 0, n) c[i+k<n ? RA[i+k]:0]++;
    FOR(i, 0, maxi) {
        sum += c[i];
        c[i] = sum - c[i];
    }
    FOR(i, 0, n)
        tempSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++] = SA[i];
    FOR(i, 0, n)
        SA[i] = tempSA[i];
}

//S must end with a <=47 char
//FOR(i, 0, n) 
//   cout << S+SA[i] << ": " << LCP[i] << endl;
void buildSA(char S[], int n) {
    vi tempRA(n);
    FOR(i, 0, n)
        RA[i] = S[i], SA[i] = i;
    for(int k=1, r=0; k<n; k<<=1) {
        countingSort(k, S, n);
        countingSort(0, S, n);
        tempRA[SA[0]] = r = 0;
        FOR(i, 1, n)
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        FOR(i, 0, n)
            RA[i] = tempRA[i];
        if(RA[SA[n-1]] == n-1) break;
    }
}

ii findPattern(char S[], int n, char P[], int m) {
    int lo = 0, hi = n-1, mid;
    while(lo < hi) {
        mid = (lo + hi) / 2;
        if(strncmp(S+SA[mid], P, m) >= 0) hi = mid;
        else lo = mid+1;
    }
    if(strncmp(S+SA[lo], P, m) != 0) return ii(-1, -1);
    ii bounds; bounds.first = lo;
    lo = 0; hi = n-1; mid = lo;
    while(lo < hi) {
        mid = (lo + hi)/2;
        if(strncmp(S+SA[mid], P, m) > 0) hi = mid;
        else lo = mid+1;
    }
    if(strncmp(S+SA[hi], P, m) != 0) hi--;
    bounds.second = hi;
    return bounds;
}

//Amortized O(n)
//LCP[i] = longest common prefix between SA[i] and SA[i-1], LCP[0] = 0
void buildLCP(char S[], int n) {
    vi phi(n), plcp(n);
    int L = 0;
    phi[SA[0]] = -1;
    FOR(i, 1, n)
        phi[SA[i]] = SA[i-1];
    FOR(i, 0, n) {
        if(phi[i] == -1) { plcp[i] = 0; continue; }
        while(S[i+L] == S[phi[i]+L]) L++;
        plcp[i] = L;
        L = max(L-1, 0);
    }
    FOR(i
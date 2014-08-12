struct SparseTable {
    vi A; vvi M;
    int log2(int n) { int i=0; while(n >>= 1) i++; return i; }
    SparseTable(vi arr) { //O(NlogN)
        int N = arr.size();
        A.assign(N, 0);
        M.assign(N, vi(log2(N)+1));
        int i, j;
        for(i=0; i<N; i++)
            M[i][0] = i, A[i] = arr[i];

        for(j=1; 1<<j <= N; j++)
            for(i=0; i + (1<<j) - 1 < N; i++)
                if(A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
                    M[i][j] = M[i][j - 1];
                else
                    M[i][j] = M[i + (1 << (j - 1))][j - 1];
    }
    //returns the index of the minimum value
    int query(int i, int j) {
        if(i > j) swap(i, j);
        int k = log2(j-i+1);
        if(A[M[i][k]] < A[M[j-(1 << k)+1][k]])
            return M[i][k];
        return M[j-(1 << k)+1][k];
    }
};
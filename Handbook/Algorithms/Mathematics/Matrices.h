typedef vector<vector<double> > Matrix;

#define CREATE(R, C) Matrix(R, vector<double>(C));

Matrix identity(int n) {
    Matrix m = CREATE(n, n);
    FOR(i, 0, n)
        m[i][i] = 1;
    return m;
}

Matrix multiply(Matrix m, double k) {
    FOR(i, 0, m.size())
        FOR(j, 0, m[0].size())
            m[i][j] *= k;
    return m;
}

Matrix multiply(Matrix m1, Matrix m2) {
    Matrix result = CREATE(m1.size(), m2[0].size());
    if(m1[0].size() != m2.size())
        return result;
    FOR(i, 0, result.size())
        FOR(j, 0, result[0].size())
            FOR(k, 0, m1[0].size())
                result[i][j] += m1[i][k]*m2[k][j];
    return result;
}

Matrix pow(Matrix m, int exp) {
    if(!exp) return identity(m.size());
    if(exp == 1) return m;
    Matrix result = identity(m.size());
    while(exp) {
        if(exp & 1) result = multiply(result, m);
        m = multiply(m, m);
        exp >>= 1;
    }
    return result;
}

//solves AX=B, output: A^-1 in A, X in B, returns det(A)
double gaussJordan(Matrix &a, Matrix &b) {
    int n = a.size(), m = b[0].size();
    vi irow(n), icol(n), ipiv(n);
    double det = 1;
    FOR(i, 0, n) {
        int pj = -1, pk = -1;
        FOR(j, 0, n) if (!ipiv[j])
            FOR(k, 0, n) if (!ipiv[k])
                if (pj == -1 || abs(a[j][k]) > abs(a[pj][pk])) { pj = j; pk = k; }
        if (abs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
        ipiv[pk]++;
        swap(a[pj], a[pk]);
        swap(b[pj], b[pk]);
        if (pj != pk) det *= -1;
        irow[i] = pj;
        icol[i] = pk;

        double c = 1.0 / a[pk][pk];
        det *= a[pk][pk];
        a[pk][pk] = 1.0;
        FOR(p, 0, n) a[pk][p] *= c;
        FOR(p, 0, m) b[pk][p] *= c;
        FOR(p, 0, n) if (p != pk) {
            c = a[p][pk];
            a[p][pk] = 0;
            FOR(q, 0, n) a[p][q] -= a[pk][q] * c;
            FOR(q, 0, m) b[p][q] -= b[pk][q] * c;      
        }
    }
    for(int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
        FOR(k, 0, n) swap(a[k][irow[p]], a[k][icol[p]]);
    }
    return det;
}

//returns the rank of a
int rref(Matrix &a) {
    int n = a.size(), m = a[0].size();
    int r = 0;
    FOR(c, 0, m) {
        int j = r;
        FOR(i, r+1, n)
            if (abs(a[i][c]) > abs(a[j][c])) j = i;
        if (abs(a[j][c]) < EPS) continue;
        swap(a[j], a[r]);
        double s = 1.0 / a[r][c];
        FOR(j, 0, m) a[r][j] *= s;
        FOR(i, 0, n) if (i != r) {
            double t = a[i][c];
            FOR(j, 0, m) a[i][j] -= t * a[r][j];
        }
        r++;
    }
    return r;
}
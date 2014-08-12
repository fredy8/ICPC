struct FenwickTree {
    vi ft;
    FenwickTree(int N) { ft.assign(N, 0); }
    int query(int to) { int sum = 0; while(to) sum += ft[to], to -= to&-to; return sum; }
    int query(int from, int to) { if(from > to) swap(to, from); return query(to) - query(from - 1); }
    void add(int i, int value) { while(i < int(ft.size())) ft[i] += value, i += i&-i;}
};

struct FenwickTree2D {
    vvi ft;
    FenwickTree2D(int R, int C) { ft.assign(R, vi(C, 0)); }
    int query(int r, int c) {
        int sum = 0;
        for(; r; r-=r&-r)
            for(int j=c; j; j-=j&-j)
                sum += ft[r][j];
        return sum;
    }
    int query(int r, int c, int R, int C) { return query(R, C) - query(r-1, C) - query(R, c-1) + query(r-1, c-1); }
    void update(int r, int c , int val) {
        for(; r<int(ft.size()); r+=r&-r)
            for(int j=c; j<int(ft.size()); j+=j&-j)
                ft[r][j] += val;
    }
};
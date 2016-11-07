struct SegmentTree {
  vi t; int N;
  SegmentTree(vi &values) {
    N = values.size();
    t.assign(N<<1, 0);
    for(int i = 0; i < N; i++) t[i+N] = values[i];
    for(int i = N-1; i; --i) t[i] = combine(t[i<<1], t[i<<1|1]);
  }
  int combine(int a, int b) { return a+b; }
  void set(int index, int value) {
    t[index+N] = value;
    for(int i = (index+N)>>1; i; i >>= 1) t[i] = combine(t[i<<1], t[i<<1|1]);
  }
  int query(int from, int to) {
    int ansL = 0, ansR = 0;
    for(int l = N+from, r = N+to; l<r; l >>= 1, r >>= 1) {
      if (l&1) ansL = combine(ansL, t[l++]);
      if (r&1) ansR = combine(ansR, t[--r]);
    }
    return combine(ansL, ansR);
  }
};

struct LazySegmentTree {
  vi t, d; int n, h;
  LazySegmentTree(vi &values) {
    n = values.size();
    h = sizeof(int) * 8 - __builtin_clz(n);
    t.assign(n<<1, 0), d.assign(n, 0);
    for(int i = 0; i < N; i++) t[i+N] = values[i];
    build(i+N, n<<1);
  }
  void calc(int p, int k) {
    if (d[p] == 0) t[p] = t[p<<1] + t[p<<1|1];
    else t[p] = d[p] * k;
  }
  void apply(int p, int value, int k) {
    t[p] = value * k;
    if (p < n) d[p] = value;
  }
  void push(int l, int r) {
    int s = h, k = 1 << (h-1);
    for (l += n, r += n-1; s > 0; --s, k >>= 1)
      for (int i = l >> s; i <= r >> s; ++i) if (d[i]) {
        apply(i<<1, d[i], k);
        apply(i<<1|1, d[i], k);
        d[i] = 0;
      }
  }
  void build(int l, int r) {
    int k = 2;
    for (l += n, r += n-1; l; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; --i) calc(i, k);
    }
  }
  void modify(int l, int r, int value) {
    if (value == 0) return;
    push(l, l + 1); push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l&1) apply(l++, value, k);
      if (r&1) apply(--r, value, k);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }
  int query(int l, int r) {
    push(l, l + 1); push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }
};

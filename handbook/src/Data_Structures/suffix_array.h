struct SuffixArray {
	vi sa, lcp;
	int N, Q = 1<<7;
	vector<int> csort(vector<ii> &val) {
		#define get(t, num) ((num) ? ((t).fi) : ((t).se))
		vi currentOrder(N, 0), nextOrder(N, 0);
		FOR(i, 0, N) currentOrder[i] = i;
		auto cur = &currentOrder, nex = &nextOrder;
		FOR(j, 0, 2) {
			vi freq(N, 0), rank(N, 0), count(N, 0);
			FOR(i, 0, N) freq[get(val[i], j)]++;
			for(int i = 0, k = 0; i < N; i++) rank[i] = k, k += freq[i];	
			FOR(i, 0, N) (*nex)[rank[get(val[(*cur)[i]], j)]++] = (*cur)[i];
			swap(cur, nex);
		}
		return *cur;
	}
	SuffixArray(char *S, int N) : N(N) {
		sa.assign(N, 0);
		FOR(i, 0, N) sa[i] = i;
		vi freq(Q, 0);
		int index[Q], rank[N], k = 0;
		FOR(i, 0, N) freq[S[i]]++;
		FOR(i, 0, Q) index[i] = k, k += freq[i];
		FOR(i, 0, N) rank[i] = index[S[i]];
		for(int len = 2; len <= N*2; len <<= 1) {
			vii val;
			FOR(i, 0, N) val.eb(rank[i], (i + len/2 >= N) ? 0 : rank[i + len/2]);
			vi order = csort(val);
			FOR(i, 0, N) rank[order[i]] = i && val[order[i]] == val[order[i-1]] ? rank[order[i-1]] : i;
		}
		FOR(i, 0, N) sa[rank[i]] = i;
		buildLCP(S);
	}
	void buildLCP(char *S) {
		vi phi(N), plcp(N);
		int L = 0;
		phi[sa[0]] = -1;
		FOR(i, 1, N) phi[sa[i]] = sa[i-1];
		FOR(i, 0, N) {
			if(phi[i] == -1) { plcp[i] = 0; continue; }
			while(S[i+L] == S[phi[i]+L]) L++;
			plcp[i] = L;
			L = max(L-1, int(0));
		}
		FOR(i, 0, N) lcp.pb(plcp[sa[i]]);
	}
};

struct MaxBipartiteMatching {
	int L, R;
	vvi edgesL;
	vi visitedL, matchR, matchL, inCoverL, inCoverR;
	MaxBipartiteMatching(int L, int R) : L(L), R(R) { edgesL.assign(L, vi()); }
	void addEdge(int l, int r) { edgesL[l].pb(r); }
	bool augment(int l) {
		if (visitedL[l]) return 0;
		visitedL[l] = 1;
		for (auto r: edgesL[l])
			if (matchR[r] == -1 || augment(matchR[r])) { matchR[r] = l; return 1; }
		return 0;
	}
	int maxMatching() {
		int ans = 0;
		matchR.assign(R, -1), matchL.assign(L, -1);
		for(int i = 0; i < L; i++)
			visitedL.assign(L, 0), ans += augment(i);
		for(int i = 0; i < R; i++) if (matchR[i] != -1) matchL[matchR[i]] = i;
		return ans;
	}
	void augment2(int l) {
		if (l == -1 || !inCoverL[l]) return;
		inCoverL[l] = 0;
		for (auto r: edgesL[l])
			if (!inCoverR[r]) inCoverR[r] = 1, augment2(matchR[r]);
	}
	void minCover() { // assuming matching found
		inCoverL.assign(L, 1), inCoverR.assign(R, 0);
		for(int i = 0; i < L; i++)
			if (matchL[i] == -1) augment2(i);
	}
};

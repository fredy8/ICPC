const int INIT = 191, P1 = 701, P2 = 34943;

int hs(vector<vi> &children, int root) {
	int value = INIT;
	vi sub;
	FORC(children[root], it)
		sub.pb(hs(children, *it));
	sort(sub.begin(), sub.end());
	FORC(sub, it)
		value = ((value * P1) ^ *it) % P2;
	return value % P2;
}

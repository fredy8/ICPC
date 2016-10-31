/* Longest Increasing Subsequence
*/
vi longestIncreasingSubsequence(vi v) {
	vii best;
	vi parent(v.size(), -1);
	FOR(i, 0, v.size()) {
		ii item = ii(v[i], i);
		vii::iterator it = upper_bound(best.begin(), best.end(), item);
		if (it == best.end()) {
			parent[i] = (best.size() == 0 ? -1 : best.back().second);
			best.pb(item);
		} else {
			parent[i] = parent[it->second];
			*it = item;
		}
	}
	vi lis;
	for(int i=best.back().second; i >= 0; i=parent[i])
		lis.pb(v[i]);
	reverse(lis.begin(), lis.end());
	return lis;
}

#define STRICTLY_INCREASING
vi LongestIncreasingSubsequence(vi v) {
    vii best;
    vi parent(v.size(), -1);
    FOR(i, 0, v.size()) {
        #ifdef STRICTLY_INCREASING
        ii item = ii(v[i], 0);
        vii::iterator it = lower_bound(best.begin(), best.end(), item);
        item.second = i;
        #else
        ii item = ii(v[i], i);
        vii::iterator it = upper_bound(best.begin(), best.end(), item);
        #endif
        if (it == best.end()) {
            parent[i] = (best.size() == 0 ? -1 : best.back().second);
            best.push_back(item);
        } else {
            parent[i] = parent[it->second];
            *it = item;
        }
    }
    vi lis;
    for(int i=best.back().second; i >= 0; i=parent[i])
        lis.push_back(v[i]);
    reverse(lis.begin(), lis.end());
    return lis;
}
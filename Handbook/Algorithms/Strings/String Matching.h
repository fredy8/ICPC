vi buildTable(string& pattern) {
    vi table(pattern.length());
    int i = 0, j = -1, m = pattern.length();
    table[0] = -1;
    while(i < m) {
        while(j >= 0 && pattern[i] != pattern[j]) j = table[j];
        i++, j++;
        table[i] = j;
    }
    return table;
}

vi find(string& text, string& pattern) {
    vi matches;
    int i = 0, j = 0, n = text.length(), m = pattern.length();
    vi table = buildTable(pattern);
    while(i < n) {
        while(j >= 0 && text[i] != pattern[j]) j = table[j];
        i++, j++;
        if(j == m) {
            matches.push_back(i-j);
            j = table[j];
        }
    }
    return matches;
}
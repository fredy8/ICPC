#define ALPHABET_SIZE 52
int getIndex(char c) {
    if(c >= 'A' && c <= 'Z')
        return c-'A';
    return c-'a'+26;
}

struct Trie {
    int words, prefixes;
    Trie *edges[ALPHABET_SIZE];
    Trie() : words(0), prefixes(0) { FOR(i, 0, ALPHABET_SIZE) edges[i] = 0; }
    ~Trie(){ FOR(i, 0, ALPHABET_SIZE) if(edges[i]) delete edges[i]; }
    void insert(char *word, int pos = 0) {
        if(word[pos] == 0) {
            words++;
            return;
        }
        prefixes++;
        int index = getIndex(word[pos]);
        if(edges[index] == 0)
            edges[index] = new Trie;
        edges[index]->insert(word, pos+1);
    }
    int countWords(char *word, int pos = 0) {
        if(word[pos] == 0)
            return words;
        int index = getIndex(word[pos]);
        if(edges[index]==0)
            return 0;
        return edges[index]->countWords(word, pos+1);
    }
    int countPrefix(char *word, int pos = 0) {
        if(word[pos] == 0)
            return prefixes;
        int index = getIndex(word[pos]);
        if(edges[index] == 0)
            return 0;
        return edges[index]->countPrefix(word, pos+1);
    }
};
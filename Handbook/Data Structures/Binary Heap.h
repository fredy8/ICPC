template <typename T>
struct Heap {
    vector<T> tree;
    int last;
    Heap(int size) : last(1) { tree.assign(size+1, 0); }
    void push(T n) {
        tree[last++] = n;
        for(int i=last-1; i != 1 && tree[i>>1] < tree[i]; i>>=1)
            swap(tree[i], tree[i>>1]);
    }
    void pop() {
        swap(tree[--last], tree[1]);
        for(int i=1; (i<<1) < last && tree[i] < tree[i<<1] || (i<<1)+1 < last && tree[i] < tree[(i<<1)+1];)
        {
            int k = ((i<<1) + ((i<<1)+1 < last && tree[(i<<1)+1] > tree[i<<1]));
            swap(tree[i], tree[k]);
            i=k;
        }
    }
    int top() { return tree[1]; }
    bool empty() { return last == 1; }
    bool size() { return last - 1; }
};

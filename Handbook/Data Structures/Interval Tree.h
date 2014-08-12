#define LCHILD(n) ((n)->parent->left == (n))
class IntervalTree {
    struct Node {
        Node *left, *right, *parent;
        set<int> intervals;
        int key, area;
        bool isLeaf;
        void unLeaf(int k) {
            isLeaf = 0, key = k;
            left = new Node(this), right = new Node(this);
        }
        Node(Node *p) : parent(p), isLeaf(1), area(0) {}
        Node(int k, Node *p) : parent(p), area(0) { unLeaf(k); }
    };
    Node *root;
    void insert(Node *node, int key) {
        Node *parent = find(node, key);
        if(parent->key == key) return;
        (key < parent->key ? parent->left : parent->right)->unLeaf(key);
    }
    void insert(Node *node, int interval, int a, int b, int imin, int imax) {
        if(a <= imin && b >= imax) { node->area = imax-imin; node->intervals.insert(interval); return; }
        if(a < node->key)
            insert(node->left, interval, a, b, imin, node->key);
        if(b > node->key)
            insert(node->right, interval, a, b, node->key, imax);
        if(node->intervals.size() == 0)
            node->area = (node->left ? node->left->area : 0) + (node->right ? node->right->area : 0);
    }
    Node * find(Node *node, int key) {
        if(key == node->key) { return node; }
        if(key < node->key) return !node->left->isLeaf ? find(node->left, key) : node;
        return !node->right->isLeaf ? find(node->right, key) : node;
    }
    void query(Node *node, int a, int b, int imin, int imax, set<int> &result) {
        if(!node) return;
        result.insert(node->intervals.begin(), node->intervals.end());
        if(a < node->key)
            query(node->left, a, b, imin, node->key, result);
        if(b >= node->key)
            query(node->right, a, b, node->key, imax, result);
    }
    void erase(Node *node, int interval, int a, int b, int imin, int imax) {
        if(a <= imin && b >= imax) {
            node->intervals.erase(interval);
            if(node->intervals.size() == 0)
                node->area = (node->left ? node->left->area : 0) + (node->right ? node->right->area : 0);
            return;
        }
        if(a < node->key)
            erase(node->left, interval, a, b, imin, node->key);
        if(b > node->key)
            erase(node->right, interval, a, b, node->key, imax);
        if(node->intervals.size() == 0)
                node->area = (node->left ? node->left->area : 0) + (node->right ? node->right->area : 0);
    }
    void dealloc(Node *node) { if(node->left) dealloc(node->left); if(node->right) dealloc(node->right); delete node; }
public:
    IntervalTree() : root(0) {}
    ~IntervalTree() { if(root) dealloc(root); }
    void insert(int key) { if(root) insert(root, key); else root = new Node(key, 0); }
    bool contains(int key) { return root && find(root, key)->key == key; }
    void insert(int interval, int a, int b) { insert(a); insert(b+1); insert(root, interval, a, b+1, -INF, INF); }
    set<int> query(int a, int b) { set<int> s; if(root) query(root, a, b, -INF, INF, s); return s; }
    void erase(int interval, int a, int b) { erase(root, interval, a, b+1, -INF, INF); }
    int getArea() { if(root) return root->area - 1; return 0; }
};
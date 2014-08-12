#define LCHILD(n) ((n)->parent->left == (n))
template< typename K, typename Compare = less<K> >
class SplayTree {
    Compare compare;
    struct Node {
        Node *left, *right, *parent;
        K key;
        Node(K k, Node *p) : key(k), parent(p), left(0), right(0) {}
    };
    Node *root;
    void insert(Node *node, K key) {
        Node *parent = find(node, key);
        if(parent->key == key) return;
        (compare(key, parent->key) ? parent->left : parent->right) = new Node(key, parent);
    }
    Node * find(Node *node, K key) {
        if(key == node->key) { splay(node); return node; }
        if(compare(key, node->key)) return node->left ? find(node->left, key) : node;
        return node->right ? find(node->right, key) : node;
    }
    void erase(Node *node, K key) {
        node = find(node, key);
        if(node->key != key) return;
        if(node == root && !node->left && !node->right) {
            root = 0;
            delete node;
        } else if(node->left && node->right) {
            Node *pred = node->left;
            while(pred->right) pred = pred->right;
            swap(node->key, pred->key);
            if(pred != root) (LCHILD(pred) ? pred->parent->left : pred->parent->right) = pred->left ? pred->left : pred->right;
            if(pred->left || pred->right) (pred->left ? pred->left : pred->right)->parent = pred->parent;
            delete pred;
        } else {
            if(node == root) root = node->left ? node->left : node->right;
            else (LCHILD(node) ? node->parent->left : node->parent->right) = node->left ? node->left : node->right;
            if(node->left || node->right) (node->left ? node->left : node->right)->parent = node->parent;
            delete node;
        }
    }
    void leftRotate(Node *parent) {
        Node *child = parent->right;
        parent->right = child->left;
        if(child->left) child->left->parent = parent;
        child->parent = parent->parent;
        if(!parent->parent) root = child;
        else if(LCHILD(parent)) parent->parent->left = child;
        else parent->parent->right = child;
        child->left = parent;
        parent->parent = child;
    }
    void rightRotate(Node *parent) {
        Node *child = parent->left;
        parent->left = child->right;
        if(child->right) child->right->parent = parent;
        child->parent = parent->parent;
        if(!parent->parent) root = child;
        else if(!LCHILD(parent)) parent->parent->right = child;
        else parent->parent->left = child;
        child->right = parent;
        parent->parent = child;
    }
    void splay(Node *node) {
        while(root != node) {
            if(node->parent->parent) {
                if(LCHILD(node)) {
                    if(LCHILD(node->parent)) {
                        rightRotate(node->parent->parent);
                        rightRotate(node->parent);
                    } else {
                        rightRotate(node->parent);
                        leftRotate(node->parent);
                    }
                } else {
                    if(LCHILD(node->parent)) {
                        leftRotate(node->parent);
                        rightRotate(node->parent);
                    } else {
                        leftRotate(node->parent->parent);
                        leftRotate(node->parent);
                    }
                }
            } else if(LCHILD(node)) {
                rightRotate(node->parent);
            } else {
                leftRotate(node->parent);
            }
        }
    }
    void dealloc(Node *node) { if(node->left) dealloc(node->left); if(node->right) dealloc(node->right); delete node; }
public:
    SplayTree() : root(0) {}
    ~SplayTree() { if(root) dealloc(root); }
    void insert(K key) { if(root) insert(root, key); else root = new Node(key, 0); }
    void erase(K key) { if(root) erase(root, key); }
    bool contains(K key) { return root && find(root, key)->key == key; }
};
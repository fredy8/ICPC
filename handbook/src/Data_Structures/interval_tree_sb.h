#ifndef LCHILD
#define LCHILD(n) ((n)->parent->left == (n))
#define _LCHILD(n) ((n)->parent->*left == (n))
#endif
#define FIX(n) (n ? (maxsec = max(maxsec, n->maxsec)) : 0)
#define ICONTAINS(i, v) ((v) >= (i).first && (v) <= (i).second)
#define IOVERLAPS(a, b) ((a).first <= (b).second && (a).second >= (b).first)
template< typename T, typename Compare = less<pair<T, T> > >
class IntervalSplayTree {
    typedef pair<T, T> K;
	Compare compare;
	struct Node {
		Node *left, *right, *parent;
		K key;
        T maxsec;
		Node(K k, Node *p) : key(k), parent(p), left(0), right(0), maxsec(key.second) {}
        void fix() {
            T mx = maxsec; 
            maxsec = key.second; 
            FIX(left); FIX(right); 
            if(maxsec != mx && parent) parent->fix();}
	    };
	Node *root;
	void insert(Node *node, K key) {
		Node *parent = find(node, key);
		if(parent->key == key) return;
		(compare(key, parent->key) ? parent->left : parent->right) = new Node(key, parent);
        parent->fix(); 
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
            if(node->parent) pred->parent->fix();
			delete pred;
		} else {
			if(node == root) root = node->left ? node->left : node->right;
			else (LCHILD(node) ? node->parent->left : node->parent->right) = node->left ? node->left : node->right;
			if(node->left || node->right) (node->left ? node->left : node->right)->parent = node->parent;
            if(node->parent) node->parent->fix();
			delete node;
		}
	}

    void rotate(Node *parent, bool rleft) {
        Node *Node::*left = &Node::left, *Node::*right = &Node::right;
        if(!rleft) swap(left, right);
		Node *child = parent->*right;
		parent->*right = child->*left;
		if(child->*left) (child->*left)->parent = parent;
		child->parent = parent->parent;
		if(!parent->parent) root = child;
		else if(_LCHILD(parent)) parent->parent->*left = child;
		else parent->parent->*right = child;
		child->*left = parent;
		parent->parent = child;
        parent->fix();
    }
	void splay(Node *node) {
		while(root != node) {
			if(node->parent->parent) {
                bool lcnode = LCHILD(node), lcparent = LCHILD(node->parent);
                rotate(lcnode == lcparent ? node->parent->parent : node->parent, !lcnode);
                rotate(node->parent, !lcparent);
			} else rotate(node->parent, !LCHILD(node));
		}
	}
	void dealloc(Node *node) { if(node->left) dealloc(node->left); if(node->right) dealloc(node->right); delete node; }
public:
	IntervalSplayTree() : root(0) {}
	~IntervalSplayTree() { if(root) dealloc(root); }
	void insert(K key) { if(root) insert(root, key); else root = new Node(key, 0); }
	void erase(K key) { if(root) erase(root, key); }
	bool contains(K key) { return root && find(root, key)->key == key; }
    void search(Node *n, K p, set<K> &result) {
     if (!n) return;
     if (p.first > n->maxsec) return; // p > maxsec
     if (n->left) search(n->left, p, result);
     if (IOVERLAPS(n->key, p))result.insert(n->key);
     if (p.second< n->key.first) return;
     if (n->right) search(n->right, p, result);
    }
    set<K> intersections(K i) {
        set<K> res; search(root, i, res);
        return res;
    }
    bool overlaps(K i) {
        return !intersections(i).empty();
    }
};



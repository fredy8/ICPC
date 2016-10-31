#define LC(a) ((a) == ((a)->parent->left))
template<typename K>
struct Treap {
	struct Node {
		K key;
		int priority;
		Node *left, *right, *parent;};
	Node *root = 0;
	Treap(Node *root = 0) : root(root) { srand(time(0)); }
	void fixDown(Node *n) {
		bool a, b;
		while((a = (n->left && n->priority < n->left->priority)) || (b = (n->right && n->priority < n->right->priority))) rotate(n, a && b ? rand()%2 : b); }
	Node *find(K key, bool leaf, Node *start, bool onlyLeft = 0) {
		if (!start) return 0;
		Node *n = start, *next;
		while((next = (key < n->key || onlyLeft ? n->left : n->right)) && (leaf || key != n->key)) n = next;
		return n; }
	void insert(K key, int priority = -1) {
		Node *p = find(key, 1, root), *n = new Node { key, priority == -1 ? rand()%100000 : priority , 0, 0, p };
		if (!root) { root = n; return; }
		(key < p->key ? p->left : p->right) = n;
		while(p && n->priority > p->priority) rotate(p, !LC(n)), p = n->parent; }
	void erase(K key) {
		if (!root) return;
		Node *n = find(key, 0, root), *del = n;
		if (!n || n->key != key) return;
		if (n->left && n->right) {
			del = find(key, 1, n->right, 1);
			n->key = del->key, n->priority = del->priority;
			fixDown(n); }
		if (del->left || del->right) (del->left ? del->left : del->right)->parent = del->parent;
		if (del->parent) (LC(del) ? del->parent->left : del->parent->right) = del->left ? del->left : del->right;
		else root = del->left ? del->left : del->right;
		delete del; }
	void rotate(Node *n, bool left) {
		Node *u = (left ? n->right : n->left), *p = n->parent;
		if (p) (LC(n) ? p->left : p->right) = u;
		else root = u;
		Node *c = left ? u->left : u->right;
		(left ? n->right : n->left) = c;
		if (c) (left ? u->left : u->right)->parent = n;
		(left ? u->left : u->right) = n;
		u->parent = p, n->parent = u; }
};

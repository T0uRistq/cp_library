struct Node {
    int key;
    int priority;
    int size;
    long long sum;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int key) : key(key), priority(rng()), left(nullptr), right(nullptr), size(1), sum(key) {}

    // apply, for example, size, sum or any funciton on subtree
    void update() {
        size = 1;
        sum = key;
        if (left != nullptr) {
            size += left->size;
            sum += left->sum;
        }
        if (right != nullptr) {
            size += right->size;
            sum += right->sum;
        }
    }
};

// contains unique elements
// delete erase line in insert to allow repeating elements
struct Treap {
    Node* root = nullptr;

    Treap() {}

    Treap(vector<int> &a) {
        for (int i : a)
            insert(i);
    }

    Node* merge(Node* left_tree, Node* right_tree) {
        if (left_tree == nullptr) return right_tree;
        if (right_tree == nullptr) return left_tree;
        if (left_tree->priority > right_tree->priority) {
            left_tree->right = merge(left_tree->right, right_tree);
            left_tree->update();
            return left_tree;
        } else {
            right_tree->left = merge(left_tree, right_tree->left);
            right_tree->update();
            return right_tree;
        }
    }

    pair<Node*, Node*> split(Node* node, int x) {
        if (node == nullptr) return {nullptr, nullptr};
        if (x > node->key) {
            pair<Node*, Node*> split_right = split(node->right, x);
            node->right = split_right.first;
            node->update();
            return {node, split_right.second};
        } else {
            pair<Node*, Node*> split_left = split(node->left, x);
            node->left = split_left.second;
            node->update();
            return {split_left.first, node};
        }
    }

    pair<Node*, Node*> split_by_size(Node* node, int sz) {
        if (node == nullptr) return {nullptr, nullptr};
        int lsz = (node->left == nullptr ? 0 : node->left->size);
        if (sz > lsz) {
            pair<Node*, Node*> split_right = split_by_size(node->right, sz - lsz - 1);
            node->right = split_right.first;
            node->update();
            return {node, split_right.second};
        } else {
            pair<Node*, Node*> split_left = split_by_size(node->left, sz);
            node->left = split_left.second;
            node->update();
            return {split_left.first, node};
        }
    }

    void insert(int key) {
        erase(key);
        Node* k = new Node(key);
        pair<Node*, Node*> p = split(root, key);
        root = merge(merge(p.first, k), p.second);
    }

    void erase(int key) {
        if (root == nullptr) return;
        pair<Node*, Node*> p1 = split(root, key);
        pair<Node*, Node*> p2 = split(p1.second, key + 1);
        root = merge(p1.first, p2.second);
    }

    Node* find_by_order(int o) {
        if (o >= root->size) return nullptr;
        pair<Node*, Node*> p = split_by_size(root, o + 1);
        Node* r = p.first;
        while (r->right != nullptr) r = r->right;
        root = merge(p.first, p.second);
        return r;
    }
};
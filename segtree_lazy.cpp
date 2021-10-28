struct Item {
    // members, e.g. val, min, max, gcd, etc.
    bool tomod = false;

    template<typename T>
    void init(const T &t, int l, int r) {
        // only applied for single elements while building, usually val = t;
    }

    void update(const Item &first, const Item &second, int l, int r) {
        // way to merge items, e.g. val = first.val + second.val, mn = min(second.mn, first.mn), etc.
    }

    static Item merge(const Item &first, const Item &second, int l, int r) {
        Item res;
        res.update(first, second, l, r);  // careful with different lengths
        return res;
    }

    template<typename T>
    void modify(const T &t, int l, int r) {
        // apply here, save for children
        tomod = true;
    }

    void push(Item &first, Item &second, int l, int r) {
        // do stuff and mark as modified
        if (tomod) {
            int m = (l + r) >> 1;
            // first.modify(, l, m);
            // second.modify(, m + 1, r);
            tomod = false;
        }
    }
};

template<typename T>
struct SegTree {
    vector<Item> tree;
    int n = 1;

    SegTree(int n = 1) : n(n) {
        tree.resize(1 << (__lg(n - 1) + 2));
    }

    void build(const vector<T> &v, int i, int l, int r) {
        if (l == r) {
            tree[i].init(v[l], l, r);
            return;
        }
        int m = (l + r) >> 1;
        build(v, i * 2 + 1, l, m);
        build(v, i * 2 + 2, m + 1, r);
        tree[i].update(tree[i * 2 + 1], tree[i * 2 + 2], l, r);
    }

    void build(const vector<T> &v) {
        n = v.size();
        tree.resize(1 << (__lg(n - 1) + 2));
        build(v, 0, 0, n - 1);
    }

    Item ask(int l, int r, int i, int vl, int vr) {
        if (vl != vr) {
            tree[i].push(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
        }
        if (l == vl && r == vr) {
            return tree[i];
        }
        int m = (vl + vr) >> 1;
        if (r <= m) {
            return ask(l, r, i * 2 + 1, vl, m);
        } else if (m < l) {
            return ask(l, r, i * 2 + 2, m + 1, vr);
        } else {
            return Item::merge(ask(l, m, i * 2 + 1, vl, m), ask(m + 1, r, i * 2 + 2, m + 1, vr), l, r);
        }
    }

    // quiries in form 0-indexed [l, r]
    Item ask(int l, int r) {
        l = max(l, 0); r = min(r, n - 1);
        if (l > r) return Item();
        return ask(l, r, 0, 0, n - 1);
    }

    void set(int i, const T &t, int x, int l, int r) {
        if (l != r) {
            tree[x].push(tree[x * 2 + 1], tree[x * 2 + 2], l, r);
        }
        if (l == r) {
            tree[x].init(t, l, r);
            return;
        }
        int m = (l + r) >> 1;
        if (i <= m) {
            set(i, t, 2 * x + 1, l, m);
        } else {
            set(i, t, 2 * x + 2, m + 1, r);
        }
        tree[x].update(tree[2 * x + 1], tree[2 * x + 2], l, r);
    }

    template<typename M>
     void modify(int l, int r, const M &t, int i, int vl, int vr) {
        if (vl != vr) {
            tree[i].push(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
        }
        if (l == vl && r == vr) {
            tree[i].modify(t, vl, vr);
            return;
        }
        int m = (vl + vr) >> 1;
        if (r <= m) {
            modify(l, r, t, i * 2 + 1, vl, m);
        } else if (m < l) {
            modify(l, r, t, i * 2 + 2, m + 1, vr);
        } else {
            modify(l, m, t, i * 2 + 1, vl, m);
            modify(m + 1, r, t, i * 2 + 2, m + 1, vr);
        }
        tree[i].update(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
    }
 
    template<typename M>
    void modify(int l, int r, const M &t) {
        l = max(l, 0); r = min(r, n - 1);
        if (l > r) return;
        modify(l, r, t, 0, 0, n - 1);
    }
};
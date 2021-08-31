// one-based impementation of Union-Find structure
// to make it zero-based remove n++; from constructor (line 6)
// path compression optimized
struct DSU {
    vector<int> size;
    vector<int> parent;
    int n;

    DSU(int n = 1) : n(n) {
        n++;
        reset(n);
    }

    void reset(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    bool check(int u, int v) {
        return find_set(u) == find_set(v);
    }
};
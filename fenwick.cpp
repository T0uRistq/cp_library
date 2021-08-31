template<typename T>
struct FenwickTree {
    vector<T> bit; // binary indexed tree
    int n;

    FenwickTree(int n = 0) : n(n) {
        bit.assign(n, 0);
    }

    FenwickTree(vector <T> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    T sum(int r) {
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    T sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    void add(int idx, T delta) {
        for (; idx < n; idx = (idx | (idx + 1)))
            bit[idx] += delta;
    }
};
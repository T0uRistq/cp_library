template<typename T>
struct FenwickTree2D {
    vector<vector<T>> bit; // binary indexed tree
    int n, m;

    FenwickTree2D(int n = 0, int m = 0) : n(n), m(m) {
        bit.assign(n, vector<T>(m, 0));
    }

    FenwickTree2D(vector<vector<T>> a) : FenwickTree2D(a.size(), a[0].size()) {
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < a[0].size(); j++)
                add(i, j, a[i][j]);
    }

    T sum(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            ret += bit[i][j];
    return ret;
    }

    T sum(int l1, int r1, int l2, int r2) {
        if (l1 > r1 || l2 > r2) return 0;
        return sum(r1, r2) - sum(l1 - 1, r2) - sum(r1, l2 - 1) + sum(l1 - 1, l2 - 1);
    }

    void add(int x, int y, T delta) {
    for (int i = x; i < n; i = i | (i + 1))
        for (int j = y; j < m; j = j | (j + 1))
            bit[i][j] += delta;
    }
};
template<typename T>
struct SparseTable {
    vector<vector<T>> st;
    int log;

    SparseTable(vector<T> &v) {
        int n = v.size();
        log = 32 - __builtin_clz(n);
        st.assign(n, vector<T> (log));
        for (int i = 0; i < n; i++) {
            st[i][0] = v[i];
        }
        for (int pw = 1; pw < log; pw++) {
            for (int i = 0; i + (1 << pw) <= n; i++) {
                st[i][pw] = min(st[i][pw - 1], st[i + (1 << (pw - 1))][pw - 1]);
            }
        }
    }
    
    T ask(int l, int r) {
        int pw = 31 - __builtin_clz(r - l + 1);
        return min(st[l][pw], st[r - (1 << pw) + 1][pw]);
    }
};
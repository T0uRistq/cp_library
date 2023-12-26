template<const int &MOD>
struct Modular {
    int val;

    Modular(long long v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    Modular<MOD> inv() const {
        int a = val, b = MOD, x = 0, y = 1;
        while (a != 0) { int k = b / a; b -= k * a; x -= k * y; swap(a, b); swap(x, y); }
        return Modular<MOD>(x);
    }

    friend Modular<MOD>& operator += (      Modular<MOD>& n, const Modular<MOD>& m) { n.val += m.val; if (n.val >= MOD) n.val -= MOD; return n; }
    friend Modular<MOD>  operator +  (const Modular<MOD>& n, const Modular<MOD>& m) { Modular<MOD> r = n; return r += m; }

    friend Modular<MOD>& operator -= (      Modular<MOD>& n, const Modular<MOD>& m) { n.val -= m.val; if (n.val < 0)  n.val += MOD; return n; }
    friend Modular<MOD>  operator -  (const Modular<MOD>& n, const Modular<MOD>& m) { Modular<MOD> r = n; return r -= m; }
    friend Modular<MOD>  operator -  (const Modular<MOD>& n)                      { return Modular<MOD>(-n.val); }

    friend Modular<MOD>& operator *= (      Modular<MOD>& n, const Modular<MOD>& m) { n.val = 1ll * n.val * m.val % MOD; return n; }
    friend Modular<MOD>  operator *  (const Modular<MOD>& n, const Modular<MOD>& m) { Modular<MOD> r = n; return r *= m; }

    friend Modular<MOD>& operator /= (      Modular<MOD>& n, const Modular<MOD>& m) { return n *= m.inv(); }
    friend Modular<MOD>  operator /  (const Modular<MOD>& n, const Modular<MOD>& m) { Modular<MOD> r = n; return r /= m; }

    Modular<MOD>& operator ++ (   ) { return *this += 1; }
    Modular<MOD>& operator -- (   ) { return *this -= 1; }
    Modular<MOD>  operator ++ (int) { Modular<MOD> r = *this; *this += 1; return r; }
    Modular<MOD>  operator -- (int) { Modular<MOD> r = *this; *this -= 1; return r; }

    friend bool operator == (const Modular<MOD>& n, const Modular<MOD>& m) { return n.val == m.val; }
    friend bool operator != (const Modular<MOD>& n, const Modular<MOD>& m) { return n.val != m.val; }

    explicit    operator       int() const { return val; }
    explicit    operator      bool() const { return val; }
    explicit    operator long long() const { return val; }

    friend istream& operator >> (istream& i,       Modular<MOD>& m) { long long k; i >> k; m = Modular<MOD> (k); return i; }
    friend ostream& operator << (ostream& o, const Modular<MOD>& m) { return o << m.val; }
    friend string   to_string(const Modular<MOD>& m) { return to_string(m.val); }
};


const int mod = 1000000007;
// const int mod = 998244353;
using Mint = Modular<mod>;

Mint mpow(Mint num, long long p) {
    Mint ans = 1;
    while (p) {
        if (p & 1) ans *= num;
        num *= num;
        p >>= 1;
    }
    return ans;
}

vector<Mint> fact, ifact;
bool __factorials_generated__ = 0;

void gen_factorials(int n) {
    __factorials_generated__ = 1;
    fact.assign(n, 1); ifact.assign(n, 1);
    for (int i = 2; i < n; i++) fact[i] = i * fact[i - 1];
    ifact[n - 1] = fact[n - 1].inv();
    for (int i = n - 2; i >= 2; i--) ifact[i] = (i + 1) * ifact[i + 1];
}

Mint nchoosek(int n, int k) {
    if (!__factorials_generated__) {
        cerr << "Call gen_factorials" << endl;
        exit(1);
    }
    if (k < 0 || n < k) return 0;
    Mint den = ifact[k] * ifact[n - k];
    return den * fact[n];
}

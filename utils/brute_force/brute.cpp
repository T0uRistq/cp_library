#include <bits/stdc++.h>
using namespace std;

int f(int x) {
    if (x == 1) return 0;
    if (x & 1) return f(x / 2);
    return f(x / 2) + 1;
}

int g(int x) {
    if (x == 1) return 1;
    if (x & 1) return 2 * g(x / 2);
    return 2 * g(x / 2) + 1;
}

void solve() {
    int L, R;
    cin >> L >> R;
    int ans = 0, I = 0;
    for (int i = L; i <= R; i++) {
        int val = f(i) + g(i);
        if (val > ans)
            ans = f(i) + g(i),
            I = i;
    }
    cout << ans << '\n';
    // cout << I << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // gen_primes();
    // gen_factorials((int)1e6 + 5);
    // cout << fixed << setprecision(12);
    cin >> t;
    for (int te = 0; t--;){
        // cout << "Case #" << ++te << ": ";
        solve();
    }
}

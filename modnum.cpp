#include <bits/stdc++.h>
using namespace std;

const int mod = 1'000'000'007;

long long mpow(long long num, long long pow){
    long long ans = 1;
    while (pow){
        if (pow & 1) ans = (ans * num) % mod;
        num = (num * num) % mod;
        pow >>= 1;
    }
    return ans;
}

long long madd(long long a, long long b) {
    return (a + b) % mod;
}

long long msub(long long a, long long b) {
    return (((a - b) % mod) + mod) % mod;
}

long long mmul(long long a, long long b) {
    return ((a % mod) * (b % mod)) % mod;
}

long long minv(long long base) {
    return mpow(base, mod - 2);
}

long long mdiv(long long a, long long b) {
    return mmul(a, minv(b));
}

vector <long long> fact, ifact;
bool __factorials_generated__ = 0;
void gen_factorials(int n) {
    __factorials_generated__ = 1;
    fact.assign(n + 1, 1); ifact.assign(n + 1, 1);
    fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    
    for (long long i = 2; i <= n; i++) {
        fact[i] = (i * fact[i - 1]) % mod;
    }
    ifact[n] = minv(fact[n]);
    for (long long i = n - 1; i >= 2; i--) {
        ifact[i] = ((i + 1) * ifact[i + 1]) % mod;
    }
}

long long nchoosek(int n, int k) {
    if (!__factorials_generated__) {
        cerr << "Call gen_factorials" << endl;
        exit(1);
    }
    if (k < 0 || n < k) return 0;
    long long den = (ifact[k] * ifact[n - k]) % mod;
    return (den * fact[n]) % mod;
}

int main(){
    int val;
    //gen_factorials((int)3e5);
    cin >> val;
    cout << nchoosek(23, 4);
}

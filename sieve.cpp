#include <bits/stdc++.h>
using namespace std;

constexpr int mod = (int)1e6 - 1;
bool is_prime[mod];
vector <int> primes;

void sieve(){
    for (int i = 2; i < mod; i++){
        is_prime[i] = true;
    }
    for (int i = 2; i * i < mod; i++){
        if (!is_prime[i]) continue;
        for (int j = i * i; j < mod; j += i){
            is_prime[j] = false;
        }
    }
}

void gen_primes(){
    sieve();
    for (int i = 2; i < mod; i++){
        if (is_prime[i]) primes.push_back(i);
    }
}

int main(){
    gen_primes();
    for (int i : primes){
        cout << i << ' ';
    }
}
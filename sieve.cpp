vector<bool> is_prime;
vector<int> primes;

void sieve(int n){
    is_prime.assign(n, false);
    for (int i = 2; i < n; i++){
        is_prime[i] = true;
    }
    for (int i = 2; i * i < n; i++){
        if (!is_prime[i]) continue;
        for (int j = i * i; j < n; j += i){
            is_prime[j] = false;
        }
    }
}

void gen_primes(int n){
    sieve(n);
    primes.clear();
    for (int i = 2; i < n; i++){
        if (is_prime[i]) primes.push_back(i);
    }
}
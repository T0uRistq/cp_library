#include <bits/stdc++.h>
using namespace std;

int uf_link[100005];
int uf_size[100005];

int find(int x) {
    while (x != uf_link[x]) x = uf_link[x];
    return x;
}

bool same(int a, int b) {
    return find(a) == find(b);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (uf_size[a] < uf_size[b]) swap(a,b);
    uf_size[a] += uf_size[b];
    uf_link[b] = a;
}

int main()
{   
    int n; // n is less than 100005
    cin >> n;
    for (int i = 1; i <= n; i++) {
        uf_link[i] = i;
        uf_size[i] = 1;
    }
}
#include <bits/stdc++.h>
using namespace std;

vector <int> z_algorithm(string s) {
    int n = s.size();
    vector <int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - x],y - i + 1));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            x = i; y = i + z[i]; z[i]++;
        }
    }
    return z;
}

int main()
{
    string s = "ACBACDACBACBACDA";
    vector <int> z_array = z_algorithm(s);
}
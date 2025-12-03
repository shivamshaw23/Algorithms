#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define mod 1000000007
 
 
 
// Sparse Table for RMQ (min). Compile with: g++ -std=c++17 rmq_sparse.cpp -O2
#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    int n, LOG;
    vector<vector<long long>> st;
    vector<int> lg;

    SparseTable(const vector<long long>& a) {
        n = (int)a.size();
        LOG = 32 - __builtin_clz(max(1, n));
        st.assign(LOG, vector<long long>(n));
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;
        st[0] = a;
        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i + (1<<k) <= n; ++i) {
                st[k][i] = min(st[k-1][i], st[k-1][i + (1<<(k-1))]);
            }
        }
    }

    // query inclusive: [L, R]
    long long query(int L, int R) {
        if (L > R) swap(L, R);
        int j = lg[R - L + 1];
        return min(st[j][L], st[j][R - (1<<j) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SparseTable st(a);
    while (q--) {
        int l, r; cin >> l >> r; // 0-based or 1-based? example uses 0-based
        cout << st.query(l, r) << '\n';
    }
    return 0;
}

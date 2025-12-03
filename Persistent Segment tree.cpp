// persistent_seg.cpp
// Persistent segment tree (point update, range sum query).
// - 0-indexed array positions
// - build initial version from array
// - update creates a new version (shares unchanged nodes)
// - query runs on any version's root index
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum;
    int l, r; // child indices in 'seg' vector
    Node(ll s = 0, int L = 0, int R = 0) : sum(s), l(L), r(R) {}
};

vector<Node> seg;   // pool of nodes
vector<int> roots;  // root indices for each version

int build(const vector<int>& a, int tl, int tr) {
    if (tl == tr) {
        seg.emplace_back(a[tl], 0, 0);
        return (int)seg.size() - 1;
    }
    int tm = (tl + tr) >> 1;
    int left = build(a, tl, tm);
    int right = build(a, tm + 1, tr);
    seg.emplace_back(seg[left].sum + seg[right].sum, left, right);
    return (int)seg.size() - 1;
}

int update(int node, int tl, int tr, int pos, int val) {
    seg.emplace_back(seg[node]);          // copy current node
    int cur = (int)seg.size() - 1;
    if (tl == tr) {
        seg[cur].sum = val;
        return cur;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
        int newLeft = update(seg[node].l, tl, tm, pos, val);
        seg[cur].l = newLeft;
    } else {
        int newRight = update(seg[node].r, tm + 1, tr, pos, val);
        seg[cur].r = newRight;
    }
    seg[cur].sum = seg[seg[cur].l].sum + seg[seg[cur].r].sum;
    return cur;
}

ll query(int node, int tl, int tr, int l, int r) {
    if (r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) return seg[node].sum;
    int tm = (tl + tr) >> 1;
    return query(seg[node].l, tl, tm, l, r) + query(seg[node].r, tm + 1, tr, l, r);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    seg.reserve(40 * n); // heuristic reserve (each update adds ~log n nodes)
    // build initial version (version 0)
    int root0 = build(a, 0, n - 1);
    roots.push_back(root0);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int v, pos, val;
            cin >> v >> pos >> val;
            --pos; // convert to 0-based
            int newRoot = update(roots[v], 0, n - 1, pos, val);
            roots.push_back(newRoot);
            cout << (int)roots.size() - 1 << '\n'; // print new version index
        } else if (type == 2) {
            int v, l, r;
            cin >> v >> l >> r;
            --l; --r; // convert to 0-based
            ll ans = query(roots[v], 0, n - 1, l, r);
            cout << ans << '\n';
        } else {
         
        }
    }
    return 0;
}

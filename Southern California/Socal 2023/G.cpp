#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

void solve() {
    int n; cin >> n;
    vector<int> a(3);
    rep(i, 0, n) {
        int x; cin >> x; x--;
        a[x]++;
    }

    int X = accumulate(all(a), 0LL);

    vector<string> out{"Future One", "Two-gether", "Triple Harmony"};

    rep(i, 0, 3) {
        if (a[i] > X - a[i]) {
            cout << out[i] << " Dominates" << endl;
            exit(0);
        }
    }

    cout << "Power Balanced" << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
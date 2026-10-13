#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

typedef long double ld;

const ld U_TO_IN = 1.75;
const ld IN_TO_CM = 2.54;

void solve() {
    ld r1, r2, c1, c2;
    while (cin >> r1 >> c1 >> r2 >> c2) {
        const vector<pair<string, ld>> cand = {
            {"0.5", 50.0 - IN_TO_CM * 4},
            {"1", 100.0 - IN_TO_CM * 8},
            {"2", 200.0 - IN_TO_CM * 8},
            {"3", 300.0 - IN_TO_CM * 8},
            {"5", 500.0 - IN_TO_CM * 8},
        };

        for (auto &[out, len] : cand) {
            ld d = 1e18;
            if (out == "0.5") {
                ld dx = abs(c1 - c2) * IN_TO_CM;
                ld dy = abs(r1 - r2) * U_TO_IN * IN_TO_CM;
                d = min(d, sqrtl(dx * dx + dy * dy));
            } else {
                ld dy = abs(r1 - r2) * U_TO_IN * IN_TO_CM;
                for (auto dx : {c1 * IN_TO_CM + c2 * IN_TO_CM, (19.0 - c1) * IN_TO_CM + (19.0 - c2) * IN_TO_CM}) {
                    d = min(d, dx + dy);
                }
            }

            if (d <= len) {
                cout << out << endl;
                break;
            }
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
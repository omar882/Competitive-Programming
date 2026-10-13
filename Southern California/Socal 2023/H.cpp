#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

int issq(int zz){
    int z = sqrt(zz);
    while(z * z > zz) z--;
    while(z * z < zz) z++;
    return z;
}


void solve() {
    int k;
    while (cin >> k) {
        int ans = 0;
        for (int y = 1; y <= k; y++) {
            int v = -4k(y-k);
            if(v <= 0) continue;
            if(issq(v) * issq(v) != v) continue;
            int x = issq(v);


            int g = gcd(x, y);
            if (g > 1) continue;
            int zz = x * x + y * y;
            int z = sqrt(zz);
            while(z * z > zz) z--;
            while(z * z < zz) z++;
            if(z*z == zz) ans++;
        }
        // cout << "---" << endl;
        cout << k << " "<< ans << endl;

    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
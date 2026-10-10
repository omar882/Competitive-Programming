#include <bits/stdc++.h>
using namespace std;

#define int long long
// #define endl '\n'
// #define ll long long
// #define ld long double
// const int M = 998244353;
// const int MAXN = 0;
#define sp << ' ' <<
#define all(x) begin(x), end(x)
#define F first
#define S second
typedef complex<int> P;
#define X real()
#define Y imag()

int cr(P a, P b) {
    return (conj(a)*b).Y;
}

void solve() {
    int x1,y1,x2,y2,x3,y3,x4,y4; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    P p1(x1,y1), p2(x2,y2), p3(x3,y3), p4(x4,y4);
    if (cr(p2-p1,p3-p2) == 0 and cr(p4-p3,p3-p2) == 0) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
    }
}


signed main() {
    cin.tie(0)->sync_with_stdio(0);
    // freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}

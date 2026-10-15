#include <bits/stdc++.h>
using namespace std;

#define int long long
// #define endl '\n'
// #define ll long long
#define ld long double
// const int M = 998244353;
// const int MAXN = 0;
#define sp << ' ' <<
#define all(x) begin(x), end(x)
#define F first
#define S second

int time(string s) {
    stringstream ss(s);
    int a, b, c;
    ss >> a; ss.ignore();
    ss >> b;
    ss.ignore();
    ss >> c;
    return a*60*60+b*60+c;
}

void solve() {
    cout << setprecision(20);
    ld yc, xc; cin >> yc >> xc;
    vector<int> ts;
    vector<array<ld,3>> ps;
    while (true){
        
        string s; ld lat, lon, alt; cin >> s >> lat >> lon >> alt;
        if (cin.fail()) break;
        int t = time(s);
        ld l1 = lat*yc;
        ld l2 = lon*xc;
        ts.push_back(t);
        ps.push_back({l1,l2,alt});  
    }
    ld cur = 0;
    for (int i = 1; i < ts.size(); i++) {
        int dt = ts[i]-ts[0];
        ld dist = sqrtl((ps[i][1]-ps[i-1][1])*(ps[i][1]-ps[i-1][1])+(ps[i][0]-ps[i-1][0])*(ps[i][0]-ps[i-1][0])+(ps[i][2]-ps[i-1][2])*(ps[i][2]-ps[i-1][2]));
        ld dalt = ps[i][2]-ps[0][2];
        cur = cur + dist;
        cout << dt sp cur sp dalt << endl;
    }
}


signed main() {
    cin.tie(0)->sync_with_stdio(0);
    // freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}

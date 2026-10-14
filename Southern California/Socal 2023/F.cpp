// 10/13/26 solve by Alan, GPT-assisted (had occasional negative outputs)
// Brute force algorithm kept for fun

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
ld v, T, W;
ld eps = 1e-9;
ld best = 1e9;

ld calc(ld init, ld start) {
    int l = 0, r = 3e5;
    while (l < r) {
        int m = (l+r)/2; // m * T is how much time extra
        ld nw = (ld)m*T*v+init;
        if (nw > W-eps and m*T+start >= 0) {
            r = m;
        } else {
            l = m+1;
        }
    }
    return (ld)l*T;
}

ld dist(ld rad, ld phase, ld t) {
    return v*t+rad*cos(2*(acos(-1))/T*t+phase);
}

void att(ld x, ld y) {
    ld phase = atan2(y,x);
    if (phase < 0) phase += 2*acos(-1);
    ld rad = sqrtl(x*x+y*y);
    ld mx;
    if (2*acos(-1)*rad/T < v-eps) {
        mx = 0;
    } else {
        mx = (asin(v*T/(2*acos(-1)*rad))-phase)*(T/(2*acos(-1)));
    }
    ld zerot = mx;
    ld ref = calc(dist(rad,phase,zerot),zerot);
    ld l = ref+zerot-T, r = ref+zerot;
    for (int i = 0; i < 100; i++) {
        ld m = (l+r)/2; // time
        ld pos = dist(rad,phase,m);
        if (pos < W) {
            l = m;
        } else {
            r = m;
        }
    }
    best = min(best, l);
}

// ld calc(ld x, ld y, ld t) {
//     ld phase = atan2(y,x);
//     if (phase < 0) phase += 2*acos(-1);
//     ld rad = sqrtl(x*x+y*y);
//     ld z1 = v*t+rad*cos(2*(acos(-1))/T*t+phase);
//     return z1;
// }

void solve() {
    cout << setprecision(20);
    ld x1,y1,x2,y2,x3,y3; 
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    cin >> v >> T >> W;
    att(x1,y1);
    att(x2,y2);
    att(x3,y3);
    // ld step = 1e-5;
    // ld t = 0;
    // ld brute = 0;
    // while (true) {
    //     ld z1 = calc(x1,y1,t), z2 = calc(x2,y2,t), z3 = calc(x3,y3,t);
    //     if (z1 >= W or z2 >= W or z3 >= W) {
    //         // if (z1 >= W) cout << "IT WAS 1" << endl;
    //         // if (z2 >= W) cout << "IT WAS 2" << endl;
    //         // if (z3 >= W) cout << "IT WAS 3" << endl;
    //         brute = t;
    //         break;
    //     }
    //     t += step;
    // }
    // cout << brute << endl;
    cout << best << endl;
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

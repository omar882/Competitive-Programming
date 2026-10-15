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
#define rep(i,a,b) for (int i = a; i < b; i++)
#define sz(x) (int)x.size()

template<class T>
struct Point {
    typedef Point P;
    T x,y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    P operator+(P p) const { return P(x+p.x,y+p.y);}
    P operator-(P p) const { return P(x-p.x,y-p.y);}
    P operator*(T d) const { return P(x*d,y*d);}
    P operator/(T d) const { return P(x/d,y/d);}
    T cross(P p) const { return x*p.y-y*p.x;}
    T cross(P a, P b) const { return (a-*this).cross(b-*this);}
};

typedef Point<ld> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
    vector<P> res;
    rep(i,0,sz(poly)) {
        P cur = poly[i],prev = i ? poly[i-1] : poly.back();
        auto a = s.cross(e,cur), b = s.cross(e,prev);
        if ((a<0) != (b<0))
            res.push_back(cur + (prev-cur) * (a / (a-b)));
        if (a < 0)
            res.push_back(cur);
    }
    return res;
}

ld polygonArea(vector<P>& v) {
    if (!v.size()) return 0;
    ld a = v.back().cross(v[0]);
    rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
    return abs(a)/2;
}

void solve() {
    cout << setprecision(20);
    ld x1, y1,x2,y2,x3,y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if (cin.fail()) exit(0);
    vector<P> ps;
    ps.push_back(P(x1,y1));
    ps.push_back(P(x2,y2));
    ps.push_back(P(x3,y3));
    ld A = polygonArea(ps);
    ld l = -5000, r = 5000;
    for (int i = 0; i < 100; i++) {
        ld m = (l+r)/2;
        auto v = polygonCut(ps,P(1,m),P(0,m));
        auto area = polygonArea(v);
        if (area < A/2) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << l << endl;
}


signed main() {
    cin.tie(0)->sync_with_stdio(0);
    // freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int t = 1;
    // cin >> t;
    while (true) solve();

    return 0;
}

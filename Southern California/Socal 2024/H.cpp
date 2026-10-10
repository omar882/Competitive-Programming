// solved by Alan 8/2/26

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

template<class T>
struct Point {
    typedef Point P;
    T x,y;
    explicit Point(T x, T y) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y);}
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y);}
    P operator+(P p) const { return P(x+p.x,y+p.y);}
    P operator-(P p) const { return P(x-p.x,y-p.y);}
    P operator*(T d) const { return P(x*d, y*d);}
    P operator/(T d) const { return P(x/d, y/d);}
    T dot(P p) const { return x*p.x + y*p.y;}
    T cross(P p) const { return x*p.y - y*p.x;}
    T cross(P a, P b) const { return (a-*this).cross(b-*this);}
    T dist2() const { return x*x + y*y;}
    ld dist() const { return sqrt(dist2());}
    P perp() const { return P(-y, x);}
    P unit() const { return *this/dist();}
};
typedef Point<ld> P;

vector<P> circleLine(P c, ld r, P a, P b) {
    P ab = b-a, p = a+ab*(c-a).dot(ab)/ab.dist2();
    ld s = a.cross(b,c), h2 = r*r-s*s/ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p-h, p+h};
}

bool circleInter(P a, P b, ld r1, ld r2, pair<P, P>& out) {
    if (a==b) { assert(r1 != r2); return false;}
    P vec = b-a;
    ld d2 = vec.dist2(), sum=r1+r2, dif=r1-r2, p = (d2+r1*r1-r2*r2)/(d2*2),h2=r1*r1-p*p*d2;
    if (sum*sum<d2 or dif*dif > d2) return false;
    P mid = a+vec*p, per=vec.perp()*sqrt(fmax(0,h2)/d2);
    out = {mid+per,mid-per};
    return true;
}

ld eps = 1e-10;

void solve() {
    // run Dijkstra's
    int n; cin >> n;
    vector<P> holds;
    for (int i = 0; i < n; i++) {
        ld x, y; cin >> x >> y;
        holds.push_back(P(x,y));
    }
    
    P dest = holds[n-1];
    vector<P> ps;
    holds.push_back(P(0,0));
    holds.push_back(P(-0.2,0));
    holds.push_back(P(0.2,0));
    holds.push_back(dest);
    holds.push_back(dest);
    // oh my fuck repeated points count you can't skip them
    // wait maybe it's fine actually?
    n = holds.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (holds[i] == holds[j]) continue;
            pair<P, P> inters = {P(0,0), P(0,0)};
            if (circleInter(holds[i], holds[j], 1, 1, inters)) {
                ps.push_back(inters.F);
                ps.push_back(inters.S);
            }
        }
    }
    ps.push_back(P(0,0));
    ps.push_back(dest);
    sort(all(ps));
    ps.erase(unique(all(ps)), ps.end());
    int m = ps.size();
    vector<vector<pair<int, ld>>> adj(m);
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            P cur = ps[i];
            P next = cur;
            bool good = true;
            while ((ps[j]-cur).dist() - (next-cur).dist() > eps) {
                cur = next;
                int ct = 0;
                ld mn = 1e18;
                for (int k = 0; k < n; k++) {
                    P tocen = holds[k]-cur;
                    if (tocen.dist() > 1+eps) continue;
                    if (abs(tocen.dist()-1) < eps) {
                        if (tocen.dot(ps[j]-cur) < eps) continue;
                    }
                    vector<P> inters = circleLine(holds[k], 1, cur, ps[j]);
                    for (auto x : inters) {
                        if ((x-cur).dot(ps[j]-cur) > eps) {
                            // cout << k << endl;
                            // cout << x.x sp x.y << endl;
                            mn = min(mn, (x-cur).dist());
                            break;
                        }
                    }
                    ct++;
                }
                if (ct < 3) {
                    good = false;
                    break;
                }
                next = cur + (ps[j]-cur).unit()*mn;
                // cerr << cur.x sp cur.y sp next.x sp next.y << endl;
            }
            if (good) {
                adj[i].push_back({j, (ps[j]-ps[i]).dist()});
                adj[j].push_back({i, (ps[j]-ps[i]).dist()});
                // cout << (ps[j]-ps[i]).dist() << endl;
            }
        }
    }
    // for (int i = 0; i < m; i++) {
    //     cout << "P: " << ps[i].x sp ps[i].y << endl;
    //     for (auto x : adj[i]) cout << x.F sp x.S << endl;
    // }

    int start;
    int stop;
    // set<P> stops;
    for (int i = 0; i < m; i++) {
        if (ps[i] == P(0,0)) start = i;
        if (ps[i] == dest) stop = i;
        // if ((ps[i]-dest).dist() < 1+eps) stops.insert(ps[i]);
    }
    vector<ld> dist(m, 1e18);
    dist[start] = 0;
    priority_queue<pair<ld, int>> pq;
    pq.push({0, start});
    vector<int> vis(m, 0);
    while (!pq.empty()) {
        auto [d, nd] = pq.top(); pq.pop();
        // cout << nd << endl;
        d *= -1;
        if (d != dist[nd]) continue;
        vis[nd] = 1;
        for (auto [x, c] : adj[nd]) {
            if (vis[x]) continue;
            if (dist[x] > dist[nd]+c) {
                dist[x] = dist[nd]+c;
                pq.push({-dist[x], x});
            }
        }
    }
    // need to be like, if there's a direct path from this point to the destination, take dist[i] + d-1
    // for (auto x : ps) cout << x.x sp x.y << endl;
    // cout << start sp dest << endl;
    if (dist[stop] > 1e17) {
        cout << -1 << endl;
        return;
    }
    cout << setprecision(20) << max((ld)0, dist[stop]-1) << endl;
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

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")
#ifdef __x86_64__
#pragma GCC target("avx2")
#endif
using namespace std;

// #define endl '\n'  //comment in interactive problems
#define ll long long
#define double long double
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define int long long
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vvpii = vector<vector<pair<int,int>>>;
using vpii = vector<pair<int,int>>;
using pii = pair<int,int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

#define F first
#define S second

typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;

const int MOD = 1e9+7;


struct Affine{
    double sl, c;
    double eval(double x){
        return sl*x + c;
    }
};

Affine comp(Affine f, Affine g){
    return {f.sl*g.sl, f.c + g.c*f.sl};
}

Affine inv(Affine f){
    return {1.0/f.sl, -f.c/f.sl};
}
string garb;
struct DSU{
    int n;
    vi p;
    vector<Affine> d;
    vector<int> sz;


    DSU(int n){
        this->n = n;
        d.assign(n, {1, 0});
        p.assign(n, 0);
        sz.assign(n, 1);
        iota(all(p), 0);
    }

    int find(int u){
        if(p[u] == u) return u;
        int root = find(p[u]);
        d[u] = comp(d[u], d[p[u]]);
        p[u] = root;
        return root;
    }

    void merge(int u, int v, Affine f){
        int ru = find(u); int rv = find(v);
        if(ru == rv) return;
        d[ru] = comp(inv(d[u]),comp(f, d[v]));
        p[ru] = rv;
        sz[rv] += sz[ru];
    }
    Affine get(int u, int v){
        int ru = find(u);
        find(v);
        return comp(d[u],inv(d[v]));
    }
};

int solve()
{
    map<string, int> strtov;
    int v = 0;

    DSU dsu(5e5);
    auto get = [&](string s){
        if(strtov.contains(s)) return strtov[s];
        strtov[s] = v++;
        return strtov[s];
    };

    while(true){
        string s;
        getline(cin, s);
        istringstream ss(s);

        string tp;
        ss >> tp;

        if(tp == "K"){
            string u1, u2;
            ss >> u1;
            ss >> garb;
            double sl; 
            ss >> sl;
            ss >> u2;

            string op;
            double c = 0;
            if(!ss.eof()){
                ss >> op;
                ss >> c;
                if(op == "-") c = -c;
            }
            int v1 = get(u1), v2 = get(u2);

            Affine f = {sl, c};

            dsu.merge(v1, v2, f);
        }
        else if(tp == "H"){
            double amt;
            ss >> amt;

            string u1, u2;
            ss >> u1;

            ss >> garb;
            ss >> garb;

            ss >> u2;
            if(u1 == u2){
                cout << amt << endl;
                continue;
            }
            if(!strtov.contains(u1) || !strtov.contains(u2)){
                cout << "Too hard!" << endl;
                continue;
            }
           
            int v1 = get(u1), v2 = get(u2);
            if(dsu.find(v1) != dsu.find(v2)){
                cout << "Too hard!" << endl;
            }
            else{
                Affine f = dsu.get(v2, v1);
                cout << fixed << setprecision(10) << f.eval(amt) << endl;
            }
        }
        else{
            exit(0);
        }
    }
    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}
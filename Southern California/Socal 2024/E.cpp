#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")
#ifdef __x86_64__
#pragma GCC target("avx2")
#endif
using namespace std;

#define endl '\n'  //comment in interactive problems
#define ll long long
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

int MOD = 1e9+7;


template<class T> struct GaussResult {
    int status, rank; // 0 impossible, 1 unique, 2 multiple
    vector<T> x;
    vector<int> where;
};


ll mulmod(ll a, ll b, ll p) {
    return (ll)((__int128)a * b % p);
}

ll submod(ll a, ll b, ll p) {
    return a >= b ? a - b : a + (p - b);
}

ll modpow(ll a, ll e, ll p) {
    ll res = 1;
    for (; e; e >>= 1, a = mulmod(a, a, p))
        if (e & 1) res = mulmod(res, a, p);
    return res;
}

GaussResult<ll> gaussMod(vector<vector<ll>> a, ll p) {
    int n = a.size(), m = a[0].size() - 1, r = 0;
    vector<int> where(m, -1);

    for (auto &row : a)
        for (auto &v : row) {
            v %= p;
            if (v < 0) v += p;
        }

    for (int c = 0; c < m && r < n; c++) {
        int s = r;
        while (s < n && a[s][c] == 0) s++;
        if (s == n) continue;

        swap(a[s], a[r]);
        where[c] = r;

        ll inv = modpow(a[r][c], p - 2, p);
        for (int j = c; j <= m; j++)
            a[r][j] = mulmod(a[r][j], inv, p);

        for (int i = r + 1; i < n; i++) {
            ll f = a[i][c];
            if (f == 0) continue;
            a[i][c] = 0;
            for (int j = c + 1; j <= m; j++)
                a[i][j] = submod(a[i][j], mulmod(f, a[r][j], p), p);
        }
        r++;
    }

    for (int i = r; i < n; i++)
        if (a[i][m]) return {0, r, {}, where};

    vector<ll> x(m, 0);
    for (int c = m - 1; c >= 0; c--) if (where[c] != -1) {
        ll v = a[where[c]][m];
        for (int j = c + 1; j < m; j++)
            v = submod(v, mulmod(a[where[c]][j], x[j], p), p);
        x[c] = v;
    }
    return {r == m ? 1 : 2, r, x, where};
}


int solve()
{
    int n, p; cin >> n >> p;
    MOD = p;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int m; cin >> m;
    vvi spells(m);
    for(int i = 0; i < m; i++){
        vi x(n);
        for(int j = 0; j < n; j++) {
            cin >> x[j];
            x[j] %= MOD;
        }
        spells[i] = x;
    }
    vi b(n);
    for(int i = 0; i < n; i++){
        b[i] = (a[(i+1)%n] - a[i]+MOD)%MOD;
    }
    vvi mat(n, vi(m+1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mat[i][j] = (spells[j][i] - spells[j][(i+1)%n] + MOD) % MOD;
        }
    }
    vi tmp(m);
    for(int i = 0; i < n; i++){
        mat[i][m] = b[i];
    }
    if(gaussMod(mat, p).status != 0){
        cout << "Possible" << endl;
    }
    else{
        cout << "Impossible" << endl;
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
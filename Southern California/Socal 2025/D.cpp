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

typedef __gnu_pbds::tree<
    int,
    __gnu_pbds::null_type,
    less<int>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
> ordered_set;

const int MOD = 1e9+7;

bitset<10000> conn[10000];

int solve()
{
    int m;
    cin >> m;

    int cur = 0;
    vector<array<int,2>> edges;

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        if(u > v) swap(u, v);

        edges.push_back({u, v});
        conn[u][v] = 1;
        conn[v][u] = 1;
    }

    sort(all(edges));
    edges.erase(unique(all(edges)), end(edges));

    int ans1 = 0, ans2 = 0;

    m = edges.size();

    for(int i = 0; i < m; i++){
        for(int j = i + 1; j < m; j++){
            auto [u1, v1] = edges[i];
            auto [u2, v2] = edges[j];

            // cout << u1 << " " << v1 << endl;
            // cout << u2 << " " << v2 << endl;

            if(u1 == u2){
                if(conn[v1][v2]) ans1++;
                else ans2++;
            }
            else if(u1 == v2){
                if(conn[v1][u2]) ans1++;
                else ans2++;
            }
            else if(v1 == u2){
                if(conn[u1][v2]) ans1++;
                else ans2++;
            }
            else if(v1 == v2){
                if(conn[u1][u2]) ans1++;
                else ans2++;
            }

            // cout << ans1 << " " << ans2 << endl;
            // cout << endl;
        }
    }

    cout << ans1 / 3 << " " << ans2 << endl;

    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--){
        solve();
    }

    return 0;
}
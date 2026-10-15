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

const int MOD = 1e9+7;

int n, m, k;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool in(int r, int c){
    return r <= n && c <= m && r >= 0 && c >= 0;
}

int gt(int r, int c){
    return r*(m+1) + c;
}

pair<int,int> ungt(int num){
    return {num/(m+1), num%(m+1)};
}

int solve()
{
    cin >> n >> m >> k;
    vvi dp(n+1, vi(m+1));
    vvi fst(n+1, vi(m+1, 1e9));

    vvi adj((n+1)*(m+1));
    for(int i = 0; i < k; i++){
        int x, y, u, v; cin >> x >> y >> u >> v;
        adj[gt(x,y)].push_back(gt(u,v));
        adj[gt(u,v)].push_back(gt(x,y));
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j<= m; j++){
            for(int k = 0; k < 4; k++){
                int ni = dx[k] + i, nj = dy[k] + j;
                if(!in(ni, nj)) continue;
                adj[gt(i, j)].push_back(gt(ni, nj));
            }
        }
    }

    queue <pii> q;
    q.push({0, 0});
    vvi d(n+1, vi(m+1, 1e9));
    d[0][0] = 0;
    dp[0][0] = 1;
    while(q.size()){
        auto [u, v] = q.front();
        q.pop();

        for(auto x: adj[gt(u, v)]){
            auto [a, b] = ungt(x); 
            
            if(d[a][b] == 1e9) q.push({a, b});
            if(d[a][b] == 1e9 || d[a][b] == d[u][v] + 1){
                dp[a][b] += dp[u][v];
                d[a][b] = d[u][v] + 1;
            }
        }
    }

    cout << dp[n][m] << endl;
    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;

    while (T--)
    {
        solve();
    }

    return 0;
}

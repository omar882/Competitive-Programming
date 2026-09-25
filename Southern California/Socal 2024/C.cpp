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
// #define int long long
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

const int N = 1e5+5;
int dp[N];

int solve()
{
    int n, m; cin >> n >> m;
    vi denom(n);
    set<int> have;

    for(int i = 0;i < n;i++){
        cin >> denom[i];
        have.insert(denom[i]);
    }
    memset(dp,-1,sizeof(dp));

    vector<int> ans;

    vector<pair<char,int>> queries; 

    for(int i = 0;i < m; i ++){
        char a;
        int b; cin >> a >> b;
        queries.push_back({a, b});
        if(a == 'X') have.erase(b);
    }
    dp[0] = 0;
    for(int i = 0;i < N; i++){
        for(auto d: have){
            if(i - d >= 0 && dp[i - d] != -1) {
                if(dp[i] == -1) dp[i] = dp[i - d] + 1;
                dp[i] = min(dp[i - d]+1,dp[i]);
            }
        }
    }

    for(int i = m-1;i>=0;i--){
        auto [a, b] = queries[i];

        if(a == 'X'){
            int d = b;
            for(int i = 0;i < N; i++){
                if(i - d >= 0 && dp[i - d] != -1) {
                    if(dp[i] == -1) dp[i] = dp[i - d] + 1;
                    dp[i] = min(dp[i - d]+1,dp[i]);
                }
            }
        }
        else{
            ans.push_back(dp[b]);
        }
    }
    reverse(all(ans));
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
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
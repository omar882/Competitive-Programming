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

int solve()
{
    int n, r; cin >> n >> r;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vi dp(r+1);
    dp[0] = 1;

    auto valid = [](int x, string a){
        string s = to_string(x);
        if(s.size() < a.size()){
            s = "0" + s;
        }
        for(int j = 0; j < s.size();j ++){
            if(a[j] == '?') continue;
            if(a[j] != s[j]) return false;
        }
        return true;
    };

    for(int i = 0; i < n; i++){
        vi ndp(r+1);
        for(int p = 0; p <= r; p++){
            for(int k = p+1; k <= r; k++){
                if(valid(k, a[i])){
                    ndp[k] += dp[p];
                }
            }
        }
        dp = ndp;
    }
    int ans = 0;
    for(int i = 1; i <= r; i++){
        ans += dp[i];
    }

    cout << ans << endl;
    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}
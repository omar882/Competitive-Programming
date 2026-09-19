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
    vector<vector<string>> grid(10, vector<string>(10));
    int dp[106];
    for(int i = 0;i<=105;i++) dp[i] = 1e9;
    vector<string> row(101);
    int cur = 100;
    for(int i = 0;i < 10;i++){
        for(int j = 0; j < 10;j++){
            cin >> grid[i][j];
        }
    }
    for(int i = 0;i < 10;i++){
        if(i%2 == 0){
            for(int j = 0; j < 10; j++){
                row[cur] = grid[i][j];
                cur--;
            }
        }
        else{
            for(int j = 9; j >= 0; j--){
                row[cur] = grid[i][j];
                cur--;
            }
        }
        
    }
    for(int i = 105; i >= 100; i--) dp[i] = 0;
    for(int i = 99; i >= 1; i--){
        if(row[i] == "."){
            for(int j = i+1; j<= i+6;j++){
                dp[i] = min(1 + dp[j], dp[i]);
            }
        }
        else if(row[i][0] == 'S'){
            continue;
        }
        else{
            int to = stoi(row[i].substr(1));
            dp[i] = dp[to];
        }
    }
    if(dp[1] >= 1e9){
        cout << "Snakes awaiting" << endl;
    }
    else{
        cout << "Win in " << dp[1] << endl;
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
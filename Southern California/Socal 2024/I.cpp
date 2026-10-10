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
    string s; cin >> s;
    int n = s.size();
    map<char,int> cnt;
    map<char,int> sum;

    for(int i = 0; i < n;i++) {
        cnt[s[i]]++;
        sum[s[i]] += i + 1;
    }
    int init = 0;
    for(int i = 0; i < n; i++){
        init += (i+1)*(i+1)*(n-cnt[s[i]]);
        init %= MOD;
    }
    // cout << init << endl;
    int tot = n*(n+1)/2;
    for(int i = 0; i < n; i ++ ){
        init -= (i+1)*(tot-sum[s[i]])%MOD;
        init%= MOD;
    }
    init %= MOD;
    init += MOD;

    cout << init%MOD << endl;
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
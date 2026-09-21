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
    int m, n, t;
    cin >> m >> n >> t;
    vi a(m);
    map<int,int> cnt;
    if(t%2 == 0) cnt[t/2] = 0;
    cnt[0] = 0;
    for(int i = 0;i < m; i++){
        cin >> a[i];
        cnt[t-a[i]] += 0;
        cnt[a[i]]++;
    }
    int init = 0;
    int best = 0;
    for(auto [v, c]: cnt){
        if(v > t/2) continue;
        if(t-v < 0 || v < 0) continue;
        if(t%2 == 0 && v == t/2){
            init += c*(c-1)/2;
            assert(t-v == v);

        }
        else{
            assert(t-v > v);
            init += c*cnt[t-v];
        }
    }

    best = init;

    for(auto [v, c]: cnt){
        if(t-v < 0 || v < 0) continue;
        int cur = init;
        
        if(t%2 == 0 && v == t/2){
            cur -= c*(c-1)/2;
        }
        else{
            cur -= c*cnt[t-v];
        }

        if(t%2 == 0 && v == t/2){
            int nc = c + n-m;
            cur += nc*(nc-1)/2;
        }
        else{
            int l = cnt[t-v], r = c;
            if(l > r) swap(l, r);
            int have = n-m;
            int tk = min(r-l, have);

            have -= tk;
            l += tk;

            int both = have/2;
            l += both;
            r += both;

            have -= both*2;

            
            if(have) {
                r++;
                have--;
            }

            assert(have == 0);
            
            cur += l*r;
        }

        best = max(cur, best);

    }

    cout << best << endl;
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
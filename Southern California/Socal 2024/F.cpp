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

map<vector<string>,string> ans;

string merge(string s, string t, int j){
    string suff = s.substr(s.size()-j, j);
    string pref = t.substr(0, j);
    if(suff == pref){
        int len = t.size()-j;
        string nword = s + t.substr(t.size()-len, len);
        return nword;
    }
    return "";
}
string recurse(vector<string> &a){
    sort(all(a));
    if(ans.contains(a)){
        return ans[a];
    }
    if(a.size() == 1){
        return a[0];
    }
    int n = a.size();
    string best = "";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            for(int k = 1; k <= min(a[i].size(), a[j].size()); k++){
                string nword = merge(a[i], a[j], k);
                if(nword == "") continue;
                vector<string> na;
                for(int p = 0; p < n; p++){
                    if(p == i) continue;
                    if(p == j) continue;
                    na.push_back(a[p]);
                }
                na.push_back(nword);
                string can = recurse(na);
                if(can == "") continue;
                if(can.size() < best.size() || best == ""){
                    best = can;
                }
                else if(can.size() == best.size()){
                    best = min(can, best);
                }
            }
        }
    }
    sort(all(a));
    ans[a] = best;

    return best;
}
int solve()
{
    int n; cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    string ans = recurse(a);
    if(ans == ""){
        cout << -1 << endl;
    }
    else{
        cout << ans << endl;
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
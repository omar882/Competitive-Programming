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
int len(int x0, int y0, int x1, int y1){
    return (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1);
}

int cr(int x0, int y0, int x1, int y1){
    return (y1*x0)-x1*y0;
}

int solve()
{
    int x0, y0, x1, y1, x2, y2; cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    int lA = len(0, 0, x0, y0);
    int lB = len(x0, y0, x1, y1);
    int lC = len(x0, y0, x2, y2);
    // cout << lA << " " << lB << " " << lC << endl;
    if(lB > lA || lC > lA){
        cout << "NO" << endl;
        return 0;
    }
    
    if(lA > lB && lA > lC){
        cout << "YES" << endl;
    }
    else if(lA > lC && cr(x0, y0, x1-x0, y1-y0) != 0){
        cout << "YES" << endl;
    }
    else if(lA > lB && cr(x0, y0, x2-x0, y2-y0) != 0){
        cout << "YES" << endl;
    }
    else cout << "NO" << endl;
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
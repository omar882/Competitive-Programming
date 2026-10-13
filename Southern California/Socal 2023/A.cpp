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

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


int solve(string s)
{

    int dir = 0;
    int x = 0, y = 0;
    int cost = 0;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] == 'D') {
            cost++;
            x += dx[dir], y += dy[dir];
        }
        else if(s[i] == 'R'){
            dir = (dir+1)%4;
        }
        else{
            dir = (dir-1+4)%4; 
        }
    }
    if(cost == abs(x) + abs(y)){
        cout << "fair fare" << endl;
    }
    else cout << "overpaid by " << cost -(abs(x) + abs(y)) << endl;
    return 0;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    string s;
    while (cin >> s)
    {
        solve(s);
    }

    return 0;
}
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

struct DSU{
    vi p, d;
    int n;
    DSU(int sz){
        n = sz;
        p.resize(n);
        d.assign(n,0);
        iota(all(p), 0);
    }
    int find(int node){
        if(p[node] == node) return node;
        int root = find(p[node]);
        d[node] = d[p[node]] ^ d[node];
        p[node] = root;
        return root;
    }
    // u ^ v = x
    bool merge(int u, int v, int x){
        int r1 = find(u), r2 = find(v);
        
        if(r1 == r2) {
            if((d[u]^d[v] != x)){
                cout << 0 << endl;
                exit(0);
            }

            return true;
        }

        d[r1] = d[u] ^ d[v] ^ x;
        p[r1] = r2;
        return true;
    }
};


int solve()
{
    int n, m, slots; cin >> n >> m >> slots;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        grid[i] = s;
    }
    vector<array<string,2>> words(slots);
    for(int i = 0; i < slots; i++) cin >> words[i][0] >> words[i][1];

    vvpii takenRow(n, vpii(m,{-1,-1}));
    vvpii takenCol(n, vpii(m,{-1,-1}));

    int cur = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '#') continue;
            // try row
            if(takenRow[i][j].F == -1){
                if(j + 1 < m && grid[i][j+1] == '.'){
                    int c = j;
                    int x = 0;
                    while(c < m && grid[i][c] == '.'){
                        takenRow[i][c] = {cur, x++};
                        c++;
                    }
                    cur++;
                }
            }

            if(takenCol[i][j].F == -1){
                if(i + 1 < n && grid[i+1][j] == '.'){
                    int r = i;
                    int x = 0;
                    while(r < n && grid[r][j] == '.' ){
                        takenCol[r][j] = {cur, x++};
                        r++;
                    }
                    cur++;
                }
            }
        }
    }
  

    DSU uf(slots+1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(takenCol[i][j].F == -1 || takenRow[i][j].F == -1) continue;
            int w1 = takenCol[i][j].F, w2 = takenRow[i][j].F;
            int i1 = takenCol[i][j].S, i2 = takenRow[i][j].S;
            if(words[w1][0][i1] == words[w2][0][i2] && 
                words[w1][1][i1] == words[w2][0][i2] &&
                words[w1][0][i1] == words[w2][1][i2] &&
                words[w1][1][i1] == words[w2][1][i2]
            ){
                // case 1: everything works
                continue;
            }
            else if(words[w1][0][i1] == words[w2][0][i2] && 
                words[w1][1][i1] == words[w2][1][i2] 
            ){
                // case 2: x_i = x_j

                uf.merge(w1, w2, 0);
            }
            else if(words[w1][0][i1] == words[w2][1][i2] && 
                words[w1][1][i1] == words[w2][0][i2] 
            ){
                // case 3: x_i^x_j = 1
                uf.merge(w1, w2, 1);
            }
            else if(words[w1][0][i1] == words[w2][0][i2] && 
                words[w1][0][i1] == words[w2][1][i2] 
            ){
                // case 4: x_i = 0
                uf.merge(w1, slots, 0);
            }
            else if(words[w1][1][i1] == words[w2][0][i2] && 
                words[w1][1][i1] == words[w2][1][i2] 
            ){
                // case 5: x_i = 1
                uf.merge(w1, slots, 1);
            }
            else if(words[w1][1][i1] == words[w2][0][i2] && 
                words[w1][0][i1] == words[w2][0][i2] 
            ){
                // case 6: x_j = 0
                uf.merge(w2, slots, 0);
            }
             else if(words[w1][1][i1] == words[w2][1][i2] && 
                words[w1][0][i1] == words[w2][1][i2] 
            ){
                // case 7: x_j = 1
                uf.merge(w2, slots, 1);
            }
            else if(words[w1][0][i1] == words[w2][0][i2] 
            ){
                // case 8: x_i = 0, x_j = 0
                uf.merge(w1, slots, 0);
                uf.merge(w2, slots, 0);
            }
            else if(words[w1][1][i1] == words[w2][1][i2] 
            ){
                // case 9: x_i = 1, x_j = 1
                uf.merge(w1, slots, 1);
                uf.merge(w2, slots, 1);
            }
            else if(words[w1][0][i1] == words[w2][1][i2] 
            ){
                // case 10: x_i = 0, x_j = 1
                uf.merge(w1, slots, 0);
                uf.merge(w2, slots, 1);
            }
             else if(words[w1][1][i1] == words[w2][0][i2] 
            ){
                // case 11: x_i = 1, x_j = 0
                uf.merge(w1, slots, 1);
                uf.merge(w2, slots, 0);
            }
            else{
                cout << 0 << endl;
                exit(0);
            }
        }
    }
    int ans = 1;
    for(int i = 0; i <= slots; i++){
        if(uf.p[i] == i){
            if(uf.find(slots) == i){
                continue;
            }
            else {
                ans *= 2;
                ans %= MOD;
            }
        }
    }
    cout << ans << endl;
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
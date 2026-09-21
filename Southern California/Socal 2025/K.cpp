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

    vvpii adj;
    vb cyc;
    vi in, down, up;


    void dfs1(int node, int parent){
        for(auto [x, w]: adj[node]){
            if(cyc[x] || x == parent) continue;
            dfs1(x, node);
            down[node] = max(w + down[x], down[node]);
        }
    }

    void dfs2(int node, int parent){
        vector<array<int,2>> options;

        for(auto [x, w]: adj[node]){
            if(cyc[x] || x == parent) continue;
            options.push_back({w + down[x], x});
        }

        sort(all(options));
        reverse(all(options));
        for(auto [x, w]: adj[node]){
            if(cyc[x] || x == parent) continue;
            up[x] = max(w + up[node], up[x]);
            if(x != options[0][1]){
                up[x] = max(w + options[0][0], up[x]);
            }
            else if(options.size() > 1){
                up[x] = max(w + options[1][0], up[x]);
            }
            dfs2(x, node);
        }
        
    }

    struct item{
        int maxiL, maxiR;
    };

    struct segtree{
        int n;
        vector<item> node;

        item default_value = {-(int)1e18};
        item merge(const item &a, const item &b){
            return {max(a.maxiL, b.maxiL), max(a.maxiR, b.maxiR)};
        }

        segtree(int na){
            int sz = 1;
            while(sz < na) sz *= 2;
            n = sz;
            node.assign(2 * n, default_value);
        }

        void build(const vector<int> &a){
            for(int i = 0; i < (int)a.size(); i++) node[i + n] = {a[i]};
            for(int i = n - 1; i >= 1; i--){
                node[i] = merge(node[i << 1], node[i << 1 | 1]);
            }
        }

        item q(int l, int r){
            item tot = default_value;
            for(l += n, r += n; l < r; l >>= 1, r >>= 1){
                if(l & 1) tot = merge(tot, node[l++]);
                if(r & 1) tot = merge(tot, node[--r]);
            }
            return tot;
        }

        void set(int i, item v){
            i += n;
            node[i] = v;
            while(i > 1){
                node[i / 2] = merge(node[i], node[i ^ 1]);
                i >>= 1;
            }
        }

    };

    int solve()
    {
        int n; cin >> n;
        adj.assign(n, {});

        cyc.assign(n, 0);

        in.assign(n, 0);
        down.assign(n, 0);
        up.assign(n, 0);

        for(int i = 0;i < n;i++){
            int u, v, w; cin >> u >> v >> w;
            u--; v--;
            adj[u].push_back({v, w}); adj[v].push_back({u, w});
            in[u]++; in[v]++;
        }

        {
            queue <int> q;
            for(int i = 0; i < n; i++) if(in[i] == 1) q.push(i);
            while(q.size()){
                int cur = q.front(); q.pop();
                for(auto [x, _]: adj[cur]){
                    in[x]--;
                    if(in[x] == 1) q.push(x);
                }
            }
            for(int i = 0;i < n;i++) if(in[i] >= 2) cyc[i] = true;
        }

        int k = 0;
        int st = -1, cur = -1;
        for(int i = 0; i < n; i++) {
            if(cyc[i]) {
                dfs1(i, -1);
                k++;
                st = i;
            }
        }


        cur = st;

        int cv = 0;
        map<int,int> cc;
        map<int,int> rcc;

        vector<array<int,2>> pr(k);
        // [x, w]

        int totLen = 0;
        int prev = -1;
        for(int i = 0; i < k; i++){
            cc[cur] = cv;
            rcc[cv] = cur;

            for(auto [x, w]: adj[cur]){
                if(cyc[x] && (x != prev || k == 2)) {
                    pr[(cv+1)%k] = {cv%k, w};
                    prev = cur;
                    cur = x;
                    totLen += w;
                    break;
                }
            }
            cv++;
        }

        vi psum(3*k);
        segtree seg(3*n);

        for(int i = 0;i < 3*k; i++){
            psum[i] += pr[i%k][1];
            if(i > 0) psum[i] += psum[i-1];
            seg.set(i, {-psum[i] + down[rcc[i%k]], psum[i] + down[rcc[i%k]]});
        }

        /* 
        value left = dist + nd
        psum[m] (- psum[l] + nd[l])


        value left = dist + nd

        psum[r] - psum[m] + down[r]
        */
        int l = 0, r = k;
        for(int mid = k; mid < 2*k; mid++){
            while(psum[mid]-psum[l] > totLen/2) l++;
            while(r < 3*k && psum[r] - psum[mid] <= totLen/2) r++;
            r--;

            up[rcc[mid%k]] = max(up[rcc[mid%k]], seg.q(l, mid).maxiL + psum[mid]);
            up[rcc[mid%k]] = max(up[rcc[mid%k]], seg.q(mid+1, r+1).maxiR - psum[mid]);
        }

    
        for(int i = 0; i < n; i++) {
            if(cyc[i]) {
                dfs2(i, -1);
            }
        }
        for(int i = 0;i < n;i++){
            cout << max(up[i], down[i]) << " ";
        }
        cout << endl;
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
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

string trash;

struct edge {
  int p;
  ld m, b;
};

void solve() {
  cout << fixed << setprecision(10);

  int PID = 0;
  map<string, int> id;
  vector<int> sz;
  vector<edge> par;

  auto get = [&](string s) -> int {
    if (id.count(s)) return id[s];
    int res = PID++;
    par.push_back(edge{res, 1.0, 0.0});
    sz.push_back(1);
    return id[s] = res;
  };

  auto find = [&](auto &&find, int u) -> int {
    if (u == par[u].p) return u;
    return find(find, par[u].p);
  };

  auto check = [&](int u, int v) -> bool {
    return find(find, u) == find(find, v);
  };

  auto unite = [&](int u, int v, ld M, ld B) -> void {
    int U = find(find, u), V = find(find, v);
    if (U == V) return;

    int at = u;
    ld fm = 1, fb = 0;
    while (at != U) {
      auto [p, m, b] = par[at];
      fb = m * fb + b;
      fm = m * fm;
      at = p;
    }

    at = v;
    ld sm = 1, sb = 0;
    while (at != V) {
      auto [p, m, b] = par[at];
      sb = m * sb + b;
      sm = m * sm;
      at = p;
    }

    fb = -fb / fm;
    fm = 1 / fm;

    M = M / fm / sm;
    B = ((B - fb) / fm) - (M * sb);
    // fm * m * sm = M
    // fm * ((m * sb) + b) + fb = B
    // (B - fb) / fm - m * sb = b
    if (sz[U] < sz[V]) {
      swap(U, V);

      // y = mx + b
      // x = (y - b) / m
      // x = 1 / m * y - b / m

      B = -B / M;
      M = 1 / M;
    }

    sz[U] += sz[V];
    par[V] = edge{U, M, B};
  };

  string t;
  cin >> t;
  while (true) {
    if (t != "K" and t != "H") {
      exit(0);
    }

    if (t == "K") {
      string _F; cin >> _F;
      cin >> trash;
      ld M; cin >> M;
      string _S; cin >> _S;
      cin >> trash;

      ld B;
      if (trash != "+" and trash != "-") {
        B = 0;
        t = trash;
      } else {
        cin >> B;
        if (trash == "-") B = -B;
        cin >> t;
      }

      int F = get(_F), S = get(_S);
      unite(F, S, M, B);
    } else {
      ld X; cin >> X;
      string _F; cin >> _F;
      cin >> trash;
      cin >> trash;
      string _S; cin >> _S;
      cin >> t;

      int F = get(_F), S = get(_S);
      if (!check(F, S)) {
        cout << "Too hard!\n";
        continue;
      }

      // y = mx + b
      // z = ny + c
      // z = n(mx + b) + c
      // z = nmx + (nb + c)

      int L = find(find, F);
      int at = F;
      ld fm = 1, fb = 0;
      while (at != L) {
        auto [p, m, b] = par[at];
        fb = m * fb + b;
        fm = m * fm;
        at = p;
      }

      at = S;
      ld sm = 1, sb = 0;
      while (at != L) {
        auto [p, m, b] = par[at];
        sb = m * sb + b;
        sm = m * sm;
        at = p;
      }

      // cerr << sm << ' ' << sb << endl;

      sb = -sb / sm;
      sm = 1 / sm;

      // cerr << F << ' ' << S << ' ' << L << endl;
      // cerr << fm << ' ' << fb << endl;
      // cerr << sm << ' ' << sb << endl;

      fb = sm * fb + sb;
      fm = sm * fm;

      cout << fm * X + fb << '\n';
    }
  }
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}

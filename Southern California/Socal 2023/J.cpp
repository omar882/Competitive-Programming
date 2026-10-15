#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;

const int ACRES = 640;
const int BLOCK = 1 << 5;
const int INF_ID = BLOCK * BLOCK * BLOCK;

struct Section {
    int id;
    vector<vector<int>> plots;
    Section(int id = -1) : id(id) {
        plots.assign(BLOCK, vector<int>(BLOCK, INF_ID));
    }

    pair<int, int> query(int r1, int c1, int r2, int c2, int pid) {
        int overlap_id = INF_ID;
        for (int r = r1; r <= r2; r++) {
            for (int c = c1; c <= c2; c++) {
                if (plots[r][c] != INF_ID) {
                    overlap_id = min(overlap_id, plots[r][c]);
                }
            }
        }

        if (overlap_id < INF_ID) {
            return {
                overlap_id,
                -1
            };
        }

        for (int r = r1; r <= r2; r++) {
            for (int c = c1; c <= c2; c++) {
                plots[r][c] = pid;
            }
        }

        return {
            INF_ID,
            (r2 - r1 + 1) * (c2 - c1 + 1)
        };
    }
};

int pid = 1;
string line, token;
Section sections[36];

void s1() {
    rep(i, 0, 36) sections[i] = Section(i);
    while (getline(cin, line)) {
        int id;
        stringstream lin(line);
        vector<array<int, 2>> commands;
        while (lin >> token) {
            if (token == "OF") continue;
            if (token == "SECTION") {
                lin >> token;
                id = stoi(token) - 1;
                break;
            } else {
                set<char> st(all(token));
                array<int, 2> command{0, 0};
                if (st.count('N')) command[0] = -1;
                if (st.count('S')) command[0] = +1;
                if (st.count('W')) command[1] = -1;
                if (st.count('E')) command[1] = +1;

                commands.push_back(command);
            }
        }

        reverse(all(commands));

        int r1 = 0, c1 = 0, r2 = BLOCK - 1, c2 = BLOCK - 1;
        for (auto &[dr, dc] : commands) {
            int rm = (r1 + r2) / 2;
            int cm = (c1 + c2) / 2;

            if (dr == -1) r2 = rm;
            if (dr == +1) r1 = rm + 1;

            if (dc == -1) c2 = cm;
            if (dc == +1) c1 = cm + 1;

            // cerr << dr << ' ' << dc << endl;
            // cerr << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
        }

        auto [overlap_id, cells] = sections[id].query(r1, c1, r2, c2, pid);
        if (overlap_id == INF_ID) {
            int num = cells * ACRES, den = BLOCK * BLOCK;
            int g = gcd(num, den);
            num /= g, den /= g;

            cout << pid++ << ' ';
            if (num / den > 0) cout << num / den << ' ';
            if (den > 1) cout << num % den << '/' << den << ' ';
            if (num / den > 0) cout << "ACRES" << endl;
            else cout << "ACRE" << endl;
        } else {
            cout << "OVERLAPS " << overlap_id << endl;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    s1();
}

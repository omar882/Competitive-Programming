#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

string line;
map<string, int> jump_table;
map<string, int> variables;

string clean_line(string s) {
    int n = sz(s);
    string t;
    for (auto &c : s) if (c == '\t') c = ' ';
    for (int i = 0; i < n;) {
        if (s[i] == ' ') {
            while (i < n and s[i] == ' ') i++;
            if (!t.empty()) t.push_back(' ');
        } else {
            t.push_back(s[i]);
            i++;
        }
    }
    return t;
}

bool is_decimal(string s) {
    for (auto &c : s) if (!isdigit(c)) return false;
    return true;
}

string get_next_token(string &s) {
    int n = sz(s);
    string left, right;
    rep(i, 0, n) {
        if (s[i] == ' ') {
            left = s.substr(0, i);
            right = s.substr(i + 1, n - i - 1);
            s = right;
            return left;
        }
    }
    
    left = s;
    right = "";
    s = right;
    return left;
}

int evaluate(string s) {
    // remove all spaces
    string t = "+"; // this will make sense i swear
    for (auto &c : s) {
        if (c == ' ') continue;
        t.push_back(c);
    }
    
    // delimit on + and - (just treat as signs)
    int result = 0, last = sz(t)-1;
    for (int i = sz(t)-1; i >= 0; i--) {
        if (t[i] == '+' or t[i] == '-') {
            int sgn = (t[i] == '+' ? +1 : -1);
            string var = t.substr(i + 1, last - i);
            int val = (is_decimal(var) ? stoi(var) : variables[var]);
            result += sgn * val;
            last = i - 1;
        }
    }
    
    return result;
}

void solve() {
    // take all commands into a buffer
    vector<string> commands;
    while (getline(cin, line)) {
        commands.push_back(line);
    }

    for (auto &command : commands) command = clean_line(command);
    
    int n = sz(commands);
    
    // pre-process location points
    rep(i, 0, n) {
        auto it = find(all(commands[i]), ':');
        if (it != commands[i].end()) {
            int j = it - commands[i].begin();
            string label = commands[i].substr(0, j);
            jump_table[label] = i;
            //~ cerr << "processing label " << label << " at " << i << ' ' << j << endl;
        }
    }
    
    // start at first command
    int p = 0;
    while (p < n) {
        string command = commands[p];
        string word = get_next_token(command);
        
        // skip location points
        if (!word.empty() and word.back() == ':') {
            word = get_next_token(command);
        }
        
        // perform the action
        if (word == "*" or word == "") {
            p++;
        } else if (word == "set") {
            string var = get_next_token(command);
            string expression = command;
            variables[var] = evaluate(expression);
            p++;
        } else if (word == "show") {
            string expression = command;
            cout << evaluate(expression) << endl;
            p++;
        } else if (word == "halt") {
            exit(0);
        } else if (word == "gotoifz") {
            string label = get_next_token(command);
            string expression = command;
            //~ cerr << label << ' ' << jump_table[label] << endl;
            if (evaluate(expression) == 0) p = jump_table[label];
            else p++;
        } else if (word == "gotoifp") {
            string label = get_next_token(command);
            string expression = command;
            //~ cerr << label << ' ' << jump_table[label] << endl;
            if (evaluate(expression) > 0) p = jump_table[label];
            else p++;
        } else if (word == "gotoifm") {
            string label = get_next_token(command);
            string expression = command;
            //~ cerr << label << ' ' << jump_table[label] << endl;
            if (evaluate(expression) < 0) p = jump_table[label];
            else p++;
        } else exit(69);
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}

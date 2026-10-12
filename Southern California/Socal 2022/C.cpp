#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

struct stack_g {
    vector<int> v;
    
    void pop() { v.pop_back(); }
    void topr() {
        int a = top();
        clear();
        push(a);
    }
    int top() { return v.back(); }
    void push(int x) { v.push_back(x); }
    void push(stack_g &o) {
        int n = o.len();
        rep(i, 0, n) {
            push(o.v[i]);
        }
    }
    void ins(int x) { v.insert(v.begin(), x); }
    int len() { return sz(v); }
    void len(stack_g &o) { push(o.len()); }
    void add() {
        int a = top(); pop();
        int b = top(); pop();
        push(b + a);
    }
    void sub() {
        int a = top(); pop();
        int b = top(); pop();
        push(b - a);
    }
    void div() {
        int a = top(); pop();
        int b = top(); pop();
        push(b / a);
    }
    void mod() {
        int a = top(); pop();
        int b = top(); pop();
        push(b % a);
    }
    void divmod() {
        int a = top(); pop();
        int b = top(); pop();
        push(b % a);
        push(b / a);
    }
    void mul() {
        int a = top(); pop();
        int b = top(); pop();
        push(b * a);
    }
    void chs() {
        int a = top(); pop();
        push(-a);
    }
    void swap() {
        int a = top(); pop();
        int b = top(); pop();
        push(a);
        push(b);
    }
    void add1() {
        int a = top(); pop();
        push(a + 1);
    }
    void sub1() {
        int a = top(); pop();
        push(a - 1);
    }
    void roll() {
        int a = top(); pop();
        ins(a);
    }
    void dup1() {
        int a = top(); pop();
        push(a); push(a);
    }
    void dup2() {
        int a = top(); pop();
        int b = top(); pop();
        push(b); push(a);
        push(b); push(a);
    }
    void rev() {
        reverse(v.begin(), v.end());
    }
    void addall() {
        int x = 0;
        
        while (len() > 0) {
            x += top(); pop();
        }
        
        push(x);
    }
    void mulall() {
        int x = 1;
        
        while (len() > 0) {
            x *= top(); pop();
        }
        
        push(x);
    }
    void clear() { v.clear(); }
    void print() {
        cout << "[";
        int n = sz(v);
        rep(i, 0, n) {
            cout << " ";
            cout << v[i];
        }
        cout << " ]\n";
    }
};

map<string, stack_g*> stack_table;

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
    
    if (!t.empty() and t.back() == ' ') t.pop_back();
    return t;
}

pair<string, stack_g*> get_next_stack(string &s) {
    // stack literal
    int n = sz(s), i = 0;
    while (i < n and s[i] == ' ') i++;
    
    // what the fuck do i do if it's a stack literal
    if (s[i] == '[') {
        int j = i;
        while (j < n and s[j] != ']') j++;
        stringstream ss(s.substr(i + 1, j - i - 1));
        
        // allocate new stack with no identifier
        stack_g *st = new stack_g;
        
        int x;
        while (ss >> x) {
            st->push(x);
        }
        
        j++;
        s = s.substr(j, n - j);
        return {"literal", st};
    } else {
        // ok otherwise we keep going until a delimiter
        // so either whitespace or a .
        int j = i;
        while (j < n and !(s[j] == ' ' or s[j] == '.')) j++;
        string label = s.substr(i, j - i);

        // we need to do something here if it's break, continue
        if (label == "break" or label == "continue") return {label, nullptr};
        
        s = s.substr(j, n - j);
        if (stack_table.count(label)) {
            stack_g *st = stack_table[label];
            return {label, st};
        } else {
            stack_g *st = new stack_g;
            stack_table[label] = st;
            return {label, st};
        }
    }
}

pair<string, string> get_next_method(string &s) {
    // the assumption here is that we will come across a .
    // then the method name, then the expression that follows if applicable
    // be careful because the delimeter can be a {
    // ok so we now have the method name
    // in the case that it is (if) or (while), we return the entire thing parsed idk
    
    int n = sz(s), i = 0;
    while (i < n and s[i] != '.') i++;
    i++;
    while (i < n and s[i] == ' ') i++;
    
    // read the identifier name
    int j = i;
    while (j < n and !(s[j] == ' ' or s[j] == '{')) j++;
    string method = s.substr(i, j - i);
    
    // run a stack approach to find open and closing brace
    int l = -1, r = -1, depth = 0;
    if (method == "if") {
        while (j < n) {
            if (s[j] == '{') {
                depth++;
                
                if (depth == 1) {
                    l = j;
                }
            }
            
            if (s[j] == '}') {
                depth--;
                
                if (depth == 0) {
                    r = j;
                    break;
                }
            }

            j++;
        }
        
        l++;
        string statement = s.substr(l, r - l);
        r++;
        s = s.substr(r, n - r);
        return {method, statement};
    } else if (method == "while") {
        while (j < n) {
            if (s[j] == '{') {
                depth++;
                
                if (depth == 1) {
                    l = j;
                }
            }
            
            if (s[j] == '}') {
                depth--;
                
                if (depth == 0) {
                    r = j;
                    break;
                }
            }

            j++;
        }
        
        l++;
        string statement = s.substr(l, r - l);
        r++;
        s = s.substr(r, n - r);
        return {method, statement};
    } else {
        s = s.substr(j, n - j);
        return {method, ""};
    }
}

pair<string, string> parse_if_else(string s) {
    int n = sz(s), j = 0, depth = 0;
    while (j < n) {
        if (s[j] == '{') {
            depth++;
        }

        if (depth == 0 and j + 4 <= n and s.substr(j, 4) == "else" and (j == 0 or s[j-1] == !isalnum(s[j-1])) and (j + 4 == n or !isalnum(s[j+4]))) {
            return {s.substr(0, j), s.substr(j + 4, n - (j + 4))};
        }
        
        if (s[j] == '}') {
            depth--;
        }

        j++;
    }

    return {s, ""};
}

const int BREAK = 0, CONTINUE = 1, NORMAL = 2;

int run(string command);

int evaluate(stack_g &stack1, string method, string expression, string &command) {
    if (method == "if") {
        auto [left, right] = parse_if_else(expression);
        if (stack1.len() > 0 and stack1.top() != 0) {
            return run(left);
        } else {
            return run(right);
        }
    } else if (method == "while") {
        while (stack1.len() > 0 and stack1.top() != 0) {
            int result = run(expression);

            if (result == BREAK) break;
            if (result == CONTINUE) continue;
        }
    } else if (method == "add") stack1.add();
    else if (method == "sub") stack1.sub();
    else if (method == "div") stack1.div();
    else if (method == "mod") stack1.mod();
    else if (method == "divmod") stack1.divmod();
    else if (method == "mul") stack1.mul();
    else if (method == "chs") stack1.chs();
    else if (method == "pop") stack1.pop();
    else if (method == "swap") stack1.swap();
    else if (method == "add1") stack1.add1();
    else if (method == "sub1") stack1.sub1();
    else if (method == "roll") stack1.roll();
    else if (method == "top") stack1.topr();
    else if (method == "dup1") stack1.dup1();
    else if (method == "dup2") stack1.dup2();
    else if (method == "rev") stack1.rev();
    else if (method == "addall") stack1.addall();
    else if (method == "mulall") stack1.mulall();
    else if (method == "clear") stack1.clear();
    else if (method == "push") {
        auto [label, stack2] = get_next_stack(command);
        stack1.push(*stack2);
    } else if (method == "len") {
        auto [label, stack2] = get_next_stack(command);
        stack1.len(*stack2);
    } else if (method == "print") stack1.print();

    return NORMAL;
}

int run(string command) {
    command = clean_line(command);
    
    while (sz(command) > 0) {
        auto [label, stack1] = get_next_stack(command);
        if (label == "break") return BREAK;
        if (label == "continue") return CONTINUE;
        auto [method, expression] = get_next_method(command);
        int result = evaluate(*stack1, method, expression, command);
        if (result != NORMAL) return result;
    }

    return NORMAL;
}

void solve() {
    string command, trash;
    while (getline(cin, trash)) {
        command += trash + " ";
    }

    run(command);
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}

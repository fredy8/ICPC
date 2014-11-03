
void output(string x) {
    cout << x << " ";
}
string readToken() {
    string t; int c;
    while((c = cin.peek()) != EOF) {
        if(isalpha(c) || isdigit(c)) t.pb((char)c), cin.get();
        else if(t != "") return t;
        else {cin.get(); if(!isspace(c)) {t.pb(c); return t;}}
    } return "";
}

#define LEFT 0
#define RIGHT 1
#define isOp(x) (prec.find(x) != prec.end())
void shunting() {
    string token;
    stack<string> ops;
    map<string, int> prec;
    prec["*"] = prec["/"] = prec["%"] = 5;
    prec["+"] = prec["-"] = 4;
    map<string, int> assoc; // default 0
    while((token = readToken()) != "") {
        if(isOp(token)) {
            while(!ops.empty() 
            && ((assoc[token] == LEFT && prec[token] <= prec[ops.top()]) 
                 || prec[token] < prec[ops.top()]))
                output(ops.top()), ops.pop();
            ops.push(token);
        } else if(token == "(") {
            ops.push(token);
        } else if(token == ")") {
            while(!ops.empty() && ops.top() != "(")
                output(ops.top()), ops.pop();
            // ops.empty() || ops.top() != "(" ====> MISMATCH
            ops.pop();
        } else // numbers vars
            output(token);
    }
    while(!ops.empty()) { // if ops.top() == ")"  || ops.top() == "(" =======> MISMATCH
        output(ops.top()), ops.pop(); 
    }
}

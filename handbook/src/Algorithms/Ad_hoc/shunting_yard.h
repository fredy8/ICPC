/* Shunting Yard
 For parsing mathematical expressions specified in infix notation
*/
void output(ostream &out, string x) {
    out << x << " ";
}
string readToken(istream &in) {
    string t; int c;
    while((c = in.peek()) != EOF) {
        if(isalpha(c) || isdigit(c)) t.pb((char)c), in.get();
        else if(t != "") return t;
        else {in.get(); if(!isspace(c)) {t.pb((char)c); return t;}}
    } return t;
}

#define LEFT 0
#define RIGHT 1
#define isOp(x) (prec.find(x) != prec.end())
void shunting(istream &in, ostream &out) {
    string token;
    stack<string> ops;
    map<string, int> prec;
    prec["^"] = 6;
    prec["*"] = prec["/"] = prec["%"] = 5;
    prec["+"] = prec["-"] = 4;
    map<string, int> assoc; // default 0
    assoc["^"] = RIGHT;
    while((token = readToken(in)) != "") {
        if(isOp(token)) {
            while(!ops.empty() && isOp(ops.top())
            && ((assoc[token] == LEFT && prec[token] <= prec[ops.top()]) 
                 || (assoc[token] == RIGHT && prec[token] < prec[ops.top()])))
                output(out, ops.top()), ops.pop();
            ops.push(token);
        } else if(token == "(") {
            ops.push(token);
        } else if(token == ")") {
            while(!ops.empty() && ops.top() != "(")
                output(out, ops.top()), ops.pop();
            // ops.empty() || ops.top() != "(" ====> MISMATCH
            ops.pop();
        } else // numbers vars
            output(out, token);
    }
    while(!ops.empty()) { // if ops.top() == ")"  || ops.top() == "(" =======> MISMATCH
        output(out, ops.top()), ops.pop(); 
    }
}

typedef int (*Operation)(int, int);
struct Operator {
    Operation operation;
    int priority;
    Operator() {}
    Operator(Operation op, int pr) { operation = op, priority = pr;}
};

int add(int a, int b) { return a+b; }
int subtract(int a, int b) { return a-b; }
int multiply(int a, int b) { return a*b; }
int divide(int a, int b) { return a/b; }

map<char, Operator> _operator;
void initOperators() {
    _operator['+'] = Operator(add, 2);
    _operator['-'] = Operator(subtract, 2);
    _operator['*'] = Operator(multiply, 3);
    _operator['/'] = Operator(divide, 3);
}

bool isOperand(char d) { return d >= '0' && d <= '9'; }
bool isOperator(char o) { return _operator.find(o) != _operator.end(); }
template<typename T> T pop(stack<T> &st) { T top = st.top(); st.pop(); return top; }
template<typename T> T pop(queue<T> &q) { T front = q.front(); q.pop(); return front; }

const int PREFIX = 0, POSTFIX = 1;
string convert(string infix, int conversionTo) {
    if(_operator.size() == 0)
        initOperators();
    string result;
    stack<char> st;
    if(conversionTo == PREFIX)
        reverse(infix.begin(), infix.end());
    for(int i=0; i<infix.length(); i++) {
        char token = infix[i];
        if(conversionTo == PREFIX) {
            if(token == '(') token = ')';
            else if(token == ')') token = '(';
        }
        if(isOperand(token)) result += token;
        else if(token == '(') st.push(token);
        else if(token == ')')
            while((token = pop(st)) != '(')
                result += token;
        else if(isOperator(token))
        {
            while(!st.empty() && isOperator(st.top()) &&
                    (_operator[st.top()].priority > _operator[token].priority ||
                    conversionTo == POSTFIX && _operator[st.top()].priority == _operator[token].priority))
                result += pop(st);
            st.push(token);
        }
    }
    while(!st.empty())
        result += pop(st);
    if(conversionTo == PREFIX)
        reverse(result.begin(), result.end());
    return result;
}

int evaluate(string postfix) {
    stack<int> st;
    for(int i=0; i<postfix.length(); i++) {
        char token = postfix[i];
        if(isOperand(token))
            st.push(token-'0');
        else if(isOperator(token))
        {
            int b = pop(st), a = pop(st);
            st.push(_operator[token].operation(a, b));
        }
    }
    return st.top();
}
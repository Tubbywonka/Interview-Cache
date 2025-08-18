//Stack Problems: DONE

//Valid Parenthesis (EASY)
class Solution {
public:
    bool isValid(string s) {
        stack<char> valstack;
        unordered_map<char, char> openclose = {{'}','{'},
                                               {')','('},
                                               {']','['}};

        for(char c : s){
            if (c == '{' || c == '(' || c == '[') {
                valstack.push(c);
            }
            else{
                if(!valstack.empty() && (valstack.top() == openclose[c])){
                    valstack.pop();
                }
                else{
                    return false;
                }
            }
        }
        return valstack.empty();
        
    }
};

//Minimum Stack (MEDIUM)
class MinStack {
private:
    stack<int> mstack;
    stack<int> minStack;

public:
    MinStack() {
    }
    
    void push(int val) {
        int push_val;
        if(mstack.empty()){
            push_val = val;
        }
        else{
            push_val = min(val,minStack.top());
        }
        mstack.push(val);
        minStack.push(push_val);
    }
    
    void pop() {
        mstack.pop();
        minStack.pop();
    }
    
    int top() {
        return mstack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

//Reverse Polish Notation (MEDIUM)
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> valstack;

        for(int i = 0; i < tokens.size(); i++){
            string token = tokens[i];
            if(token != "+" &&
               token != "-" &&
               token != "/" && 
               token != "*"){
                valstack.push(stoi(token));
            }
            else{
                int r = valstack.top(); valstack.pop();
                int l = valstack.top(); valstack.pop();
                if(token == "+"){
                    valstack.push(l + r);
                }
                else if(token == "-"){
                    valstack.push(l - r);
                }
                else if(token == "*"){
                    valstack.push(l * r);
                }
                else if(token == "/"){
                    valstack.push(l / r);
                }
            }
        }
        return valstack.top();
    }
};

//Generate Parentheses (MEDIUM)
class Solution {
public:
    void backtrack(int openN, int closedN, int n, vector<string>& res, string& stack) {
        if (openN == closedN && openN == n) {
            res.push_back(stack);
            return;
        }

        if (openN < n) {
            stack += '(';
            backtrack(openN + 1, closedN, n, res, stack);
            stack.pop_back();
        }
        if (closedN < openN) {
            stack += ')';
            backtrack(openN, closedN + 1, n, res, stack);
            stack.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string stack;
        backtrack(0, 0, n, res, stack);
        return res;
    }
};

//Daily Temperatures (MEDIUM)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        stack<pair<int, int>> stack; // pair: {temp, index}

        for (int i = 0; i < temperatures.size(); i++) {
            int t = temperatures[i];
            while (!stack.empty() && t > stack.top().first) {
                auto pair = stack.top();
                stack.pop();
                res[pair.second] = i - pair.second;
            }
            stack.push({t, i});
        }
        return res;
    }
};

//Car Fleet (MEDIUM) 
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> pair;
        for (int i = 0; i < position.size(); i++) {
            pair.push_back({position[i], speed[i]});
        }
        sort(pair.rbegin(), pair.rend());
        vector<double> stack;
        for (auto& p : pair) {
            stack.push_back((double)(target - p.first) / p.second);
            if (stack.size() >= 2 && 
                stack.back() <= stack[stack.size() - 2]) 
            {
                stack.pop_back();
            }
        }
        return stack.size();
    }
};

//Largest Rectangle in Histogram (HARD)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int max_area = 0;
        stack<pair<int,int>> stack;

        for(int i = 0; i < heights.size(); i++){
           int start = i;
           while(!stack.empty() && stack.top().second >= heights[i]){
                auto pair = stack.top();
                max_area = max(pair.second * (i-pair.first), max_area);
                start = pair.first;
                stack.pop();
           }
           stack.push({start,heights[i]});
        }

        while(!stack.empty()){
            auto pair2 = stack.top();
            max_area = max(max_area, pair2.second * ((int)(heights.size()) - pair2.first));
            stack.pop();
        }
        return max_area;
        
    }
};


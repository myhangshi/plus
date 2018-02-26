#include <vector> 
#include <string> 
#include <iostream> 
#include <stack> 

using namespace std; 

bool isOperatorToken(const string &op) { 
        return op.size() == 1 && string("+-*/").find(op) != string::npos; 
}

int evalRPN(vector<string>& tokens) {
        stack<string> stk; 
        
        for (auto token: tokens) { 
            if (!isOperatorToken(token)) { 
                stk.push(token); 
                cout<<"push"<< token << endl; 

            } else { 
                int y = stoi(stk.top());
                stk.pop(); 
                cout<<"pop"<<endl; 

                int x = stoi(stk.top());
                stk.pop(); 
                cout<<"pop"<<endl; 
                

                if (token[0] == '+') x += y; 
                else if (token[0] == '-') x -= y; 
                else if (token[0] == '*') x *= y;
                else x /= y;
                stk.push(to_string(x)); 
            }
            
        }
        
        return stoi(stk.top()); 
}



int main() 
{ 
    int N = 5; 
    vector<string> s;
    s.insert(s.begin(), "+"); 
    s.insert(s.begin(), "3"); 
    s.insert(s.begin(), "4"); 
    

    //cout<< "vector" << s << endl; 

    //int k = 100; 
    int k = evalRPN(s); 
	
    cout << "the result is " << k << endl; 


    return 0; 
} 
	

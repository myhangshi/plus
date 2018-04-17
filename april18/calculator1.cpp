
#include <iostream>
#include <vector>
#include <stack> 
 
using namespace std;


int calculate(string s) {
        int result = 0, d = 0; 
        char sign = 1; 
        int n = s.size(); 

        stack<int> nums; 
        int num = 0; 
        
        for (int i = 0; i < n; ++i) { 
            char c = s[i]; 
            cout<<i << "  "<< result << " " << num; 
            cout<<" " << c << endl;  
            if (c >= '0' && c <= '9') { 
                num = 0; 
                while (i < n && s[i] >= '0') { 
                    num = 10 * num + s[i] - '0'; 
                    i++; 
                }
                --i; //put back one char 
                cout << i << "the number is " << num << endl; 

            } else if (c == '+') { 
                result += sign * num; 
                sign = 1;      

            } else if (c == '-') { 
                result += sign * num; 
                sign = -1;             
            } else if (c == '(') { 
                nums.push(result); 
                nums.push(sign); 
                result = 0; 
                sign = 1; 
            } else if (c == ')') {
                result += sign * num;
                num = 0;
                result *= nums.top(); nums.pop(); //sign
                result += nums.top(); nums.pop(); //result
            }
            
            
        }
        
        result += sign * num; 
        return result; 
}

int main()
{
    string s = "1 + 1";
    cout <<calculate(s)<<endl; 

    return 0; 
} 
#include <iostream> 
#include <string> 
#include <vector> 
#include <climits> 
#include <cassert> 

using namespace std; 

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty()) return ""; 
        if (s.size() < t.size()) return ""; 
        if (s.size() <= 2) return ""; 
        
        const int ASCII_NUM = 256; 
        int appeared_count[ASCII_NUM]; 
        int expected_count[ASCII_NUM]; 
        fill(appeared_count, appeared_count + ASCII_NUM, 0); 
        fill(expected_count, expected_count + ASCII_NUM, 0); 
        
        for (int i = 0; i < t.size(); i++) { 
            expected_count[t[i]]++; 
        }
        
        int minWidth = INT_MAX, min_start = 0; 
        int wnd_start = 0; 
        int appeared = 0; 
        
        for (int wnd_end = 0; wnd_end < s.size(); wnd_end++) { 
            if (expected_count[s[wnd_end]] > 0) { 
                appeared_count[s[wnd_end]]++; 
                if (appeared_count[s[wnd_end]] <= expected_count[s[wnd_end]]) { 
                    appeared++; 
                }
            }
            
            if (appeared == t.size()) { 
                while (appeared_count[s[wnd_start]] > expected_count[s[wnd_start]] || 
                       expected_count[s[wnd_start]] == 0) { 
                    appeared_count[s[wnd_start]]--; 
                    wnd_start++; 
                } 
                if (minWidth > (wnd_end - wnd_start + 1)) { 
                    minWidth = wnd_end - wnd_start + 1; 
                    min_start = wnd_start; 
                }
            }
        }
        
        if (minWidth == INT_MAX) return ""; 
        else return s.substr(min_start, minWidth); 
    }
};

string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

int main() {
    string line;
    while (getline(cin, line)) {
        string s = stringToString(line);
        getline(cin, line);
        string t = stringToString(line);
        
        string ret = Solution().minWindow(s, t);

        string out = (ret);
        cout << out << endl;
    }
    return 0;
}


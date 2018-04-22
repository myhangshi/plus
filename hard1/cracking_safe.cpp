class Solution {
public:
    string crackSafe(int n, int k) {
        string result = string(n, '0'); 
        unordered_set<string> visited{{result}}; 
        
        for (int i = 0; i < n*k; ++i) { 
            string pre = result.substr(result.size()-n+1, n-1); 
            for (int j = k - 1; j > 0; --j) { 
                string cur = pre + to_string(j); 
                if (!visited.count(cur)) { 
                    visited.insert(cur); 
                    result += to_string(j); 
                    break; 
                }
            }
        }
        return result; 
    }
}; // not accepted 



    string crackSafe2(int n, int k) {
        string res = string(n, '0');
        unordered_set<string> visited{{res}};
        helper(n, k, pow(k, n), visited, res);
        return res;
    }
    void helper(int n, int k, int total, unordered_set<string>& visited, string& res) {
        if (visited.size() == total) return;
        string pre = res.substr(res.size() - n + 1, n - 1);
        for (int i = k - 1; i >= 0; --i) {
            string cur = pre + to_string(i);
            if (visited.count(cur)) continue;
            visited.insert(cur);
            res += to_string(i);
            helper(n, k, total, visited, res);
        }
    }
    


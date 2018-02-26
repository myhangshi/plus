class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> group; 
        
        //for (int i = 0; i < strs.size(); i++) { 
        //  string key = strs[i]; 
        for (const auto &s : strs) { 
            string key = s; 
            sort(key.begin(), key.end()); 
            group[key].push_back(s); 
        }
        
        vector<vector<string>> result; 
        for (auto itr = group.cbegin(); itr != group.cend(); itr++) { 
            result.push_back(itr->second); 
        }
        return result; 
    }
};


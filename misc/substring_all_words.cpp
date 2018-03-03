class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int word_len = words.front().length(); 
        int cat_len = word_len * words.size(); 
        vector<int> result; 
        
        if (s.length() < cat_len) return result; 
        unordered_map<string, int> wordCount; 
        
        for (auto const & word : words) 
            ++wordCount[word]; 
        
        for (auto i = begin(s); i <= prev(end(s), cat_len); i++) { 
            unordered_map<string, int>  unused(wordCount); 
            
            for (auto j = i; j != next(i, cat_len); j += word_len) { 
                auto pos = unused.find(string(j, next(j, word_len))); 
                if (pos == unused.end() || pos->second == 0) break; 
                
                if (--pos->second == 0) unused.erase(pos); 
            }
            if (unused.size() == 0) result.push_back(distance(begin(s), i)); 
        
        } 
        return result; 
        
        
    } 


}; 


class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int result = 0; 
        int mx = 0; 
        
        for (int i = 0; i < arr.size(); ++i) { 
            mx = max(mx, arr[i]); 
            if (mx == i) result++; 
        }
        return result; 
    }
};


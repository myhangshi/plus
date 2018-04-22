class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int xo = 0; 
        for (int n : nums) { 
            xo ^= n; 
        }
        
        return ( xo == 0) || (nums.size() % 2 == 0); 
    }
};



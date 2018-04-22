class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size(), i; 
        for (i = 0; i < n-1; ) { 
            if (bits[i] == 0) i++; 
            else i+= 2; 
        }
        return i == n-1; 
    }
};



class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        
        int sum = 0, total =0; 
        int index = 0; 
        
        for (int i = 0; i < gas.size(); i++) { 
            total += gas[i] - cost[i]; 
            sum += gas[i] - cost[i]; 
            if (sum < 0) { 
                sum = 0; 
                index = i + 1; 
            }
        
        }
        
        if (total >= 0) return index; 
        else return -1;
    }
};


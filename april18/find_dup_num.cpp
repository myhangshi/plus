

http://www.cnblogs.com/grandyang/p/4843654.html



class Solution {
public:
    int findDuplicate1(vector<int>& nums) {
        int sum = 0; 
        int N = nums.size(); 
        for (int i = 0; i < N; i++) { 
            sum += nums[i]; 
        }
        return N*(N-1)/2 - sum;  
    } 
    
    
    int findDuplicate(vector<int>& nums) {
        int lo = 1, hi = nums.size(); 
        
       while (lo < hi) { 
           int count = 0; 
           int mid = lo + (hi - lo) / 2; 
           for (int i = 0; i < nums.size(); i++) { 
               if (nums[i] <= mid) count++; 
           }
           
           if (count <= mid) lo = mid + 1; 
           else hi = mid; 
       }
       return lo;  
    }
    
};


class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0, t = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }
        while (true) {
            slow = nums[slow];
            t = nums[t];
            if (slow == t) break;
        }
        return slow;
    }
};




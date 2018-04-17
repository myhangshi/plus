#include <iostream>
#include <vector>
 
using namespace std;

    
int partition(vector<int>& nums, int lo, int hi) { 
    int i = lo;
    int v = nums[lo]; 
    int tmp;
/*
       if (hi - lo <= 1) { 
            if (nums[hi] < nums[lo]) { 
                tmp = nums[hi]; 
                nums[hi] = nums[lo]; 
                nums[lo] = tmp; 
            }
            return lo; 
            
        } 
*/         
        while (i <= hi) { 
            if (nums[i] < v) { 
                tmp = nums[i]; 
                nums[i] = nums[lo]; 
                nums[lo] = tmp; 
                lo++; i++; 
            } else if (nums[i] > v) { 
                tmp = nums[i]; 
                nums[i] = nums[hi]; 
                nums[hi] = tmp; 
                hi--; 
            } else { 
                i++; 
            }
        }
        return lo; 
    
}
    
int findKthLargest(vector<int>& nums, int k) {
        
        int lo = 0, hi = nums.size() - 1; 
        int m; 
        
        k = hi - k + 1;  
        
        while (lo <= hi) { 
            m = partition(nums, lo, hi); 
            cout<<"  Inside "<< m << lo << hi << endl; 
            if (m == k) return nums[k]; 
            else if (m < k) lo = m + 1; 
            else hi = m - 1; 
        }
        
        return -1; 
        
}

int main()
{
    vector<int> g1{3, 2, 1, 5, 6, 4};

    int  k = findKthLargest(g1, 2); 
    cout<<k<<endl; 

    return 0; 
} 

    
 

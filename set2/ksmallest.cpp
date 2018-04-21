#include <iostream> 
#include <vector> 
#include <unordered_map> 
#include <algorithm> 
#include <map> 
#include <climits> 

using namespace std; 


struct HeapNode { 
        int val; //value to be stored 
        int r;   //Row number of value in 2D array 
        int c;   //Column number of value in 2D array 
}; 
    
void swap(HeapNode *x, HeapNode *y) { 
        HeapNode z = *x; 
        *x = *y; 
        *y = z; 
}
    
//sink 
void minHeapify(HeapNode harr[], int i, int heap_size) { 
     int l = i*2 + 1; 
     int r = i*2 + 2; 
     int smallest = i; 
        
        if (l < heap_size && harr[l].val < harr[i].val) 
            smallest = l; 
        if (r < heap_size && harr[r].val < harr[smallest].val)
            smallest = r; 
        
        if (smallest != i) { 
            swap(&harr[i], &harr[smallest]); 
            minHeapify(harr, smallest, heap_size); 
        }
    
    }
    
void buildHeap(HeapNode harr[], int n) 
{
        int i = (n - 1)/2; 
        while (i >= 0) { 
            minHeapify(harr, i, n);
            i--; 
        }
}
    
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size(); 
        
        if (k <= 0 || k > n*n) 
            return INT_MAX; 
        
        HeapNode harr[n]; 
        for (int i = 0; i < n; i++) 
            harr[i] = {matrix[0][i], 0, i}; 
        buildHeap(harr, n); 
        
        HeapNode hr; 
        for (int i = 0; i < k; i++) {
            hr = harr[0]; 
            
            int nextval = (hr.r < (n-1) ? matrix[hr.r+1][hr.c]:INT_MAX); 
            
            harr[0] = {nextval, (hr.r)+1, hr.c}; 
            minHeapify(harr, 0, n); 
        }
        return hr.val; 
}


int main() 
{ 
	vector<vector<int>> mat{ {10, 20, 30, 40},
                    {15, 25, 35, 45},
                    {25, 29, 37, 48},
                    {32, 33, 39, 50},
                  };
  cout << "7th smallest element is " << kthSmallest(mat,  7) << endl;


	return 0;
} 


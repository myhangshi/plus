#include <iostream> 
#include <vector> 

using namespace std;     


int maxArea(vector<int>& height) {
        
        int start = 0; 
        int end = height.size() - 1; 
        
        int result = -1; 
	cout << "start end " << start << "  " << end << endl;         
        while (start < end) { 
            int area = min(height[end], height[start]) * (end - start); 

            cout << "area is " << area << endl; 

            result = max(result, area); 
            cout << "result is " << result << endl; 

            if (height[start] <= height[end]) { 
                start++; 
            } else { 
                end--; 
            }
        }
        return result; 
        
}

int main() 
{ 

    cout << "hello world " << endl; 
    vector<int> v; 

    v.push_back(2); 
    v.push_back(1); 

    cout << "hello " << maxArea(v) << endl; 

    return 0; 
} 




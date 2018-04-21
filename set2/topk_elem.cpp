#include <iostream> 
#include <vector> 
#include <unordered_map> 
#include <algorithm> 
#include <map> 

using namespace std; 


vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result(k+1, 0); 
        unordered_map<int, int> freq; 
        
	for (int i = 0; i < nums.size(); i++) { 
            freq[nums[i]]++; 
            result[k] = nums[i]; 
            cout << "number here "<< nums[i] << " frequency "; 
            cout << freq[nums[i]] <<endl; 
            auto it = find(result.begin(), result.end() - 1, result[k]);
	for (int i = 0; i < result.size(); ++i) { 
	    cout << " R " << result[i] << " L " << freq[result[i]] << endl; 
	} 
       	
            int dist = k; 
            if (it == result.end() - 1) {
		cout<<"Found No "<<endl; 
		dist = k -1; 
	    } else { 
		
		dist = distance(result.begin(), it) - 1;
		cout<<"Found YES "<< dist << endl; 
	    }   	 	
            cout<< "Distance" << dist<<endl; 

            // iterate from the position of element to zero
            for (int i = dist; i >= 0; --i) {
           	// compare the frequency and swap if higher
            	// frequency element is stored next to it
           	if (freq[result[i]] < freq[result[i + 1]])
                	swap(result[i], result[i + 1]);
            	// if frequency is same compare the elements
            	// and swap if next element is high
            	else if ((freq[result[i]] == freq[result[i + 1]])
                     && (result[i] > result[i + 1]))
                	swap(result[i], result[i + 1]);
            	else break;
            }            
                
        }

	cout<<"all finished "<<endl; 


        for (int i = 0; i < result.size(); ++i) { 
	        cout << " R " << result[i] << " L " << freq[result[i]] << endl; 
	    }

        vector<int> top; 
        top.assign(result.begin(), result.end()-1);
        return top;         
}


vector<int> topKFrequent3(vector<int>& nums, int k) {
        vector<int> result(k+1, 0); 
        unordered_map<int, int> freq; 
        
        for (int i = 0; i < nums.size(); i++) { 
            freq[nums[i]]++; 
            result[k] = nums[i]; 
            cout << "number here "<< nums[i] << " frequency "; 
            cout << freq[nums[i]] <<endl; 
            for (int i = 0; i < result.size(); ++i) { 
                cout << " R " << result[i] << " L " << freq[result[i]] << endl; 
            }
 
            auto it = find(result.begin(), result.end() - 1, result[k]);
            int dist = distance(result.begin(), it) - 1;
            cout<< "Distance   " << dist<<endl; 
                        
            for (int j = distance(result.begin(), it) -1; j >= 0; --j) { 
                if (freq[result[j+1]] > freq[result[j]])
                    swap(result[j+1], result[j]); 
            }
        }

        cout<<"all finished "<<endl; 

        for (int i = 0; i < result.size(); ++i) { 
            cout << " R " << result[i] << " L " << freq[result[i]] << endl; 
        }

        vector<int> top; 
        top.assign(result.begin(), result.end()-1);
        return top;         
}


// Accepted 
vector<int> topKFrequent4(vector<int>& nums, int k) {        
        unordered_map<int, int> count;
        int max_freq = 1;
        for (const int num : nums)
            max_freq = max(max_freq, ++count[num]);
        
        map<int, vector<int>> buckets;
        for (const auto& kv : count)
            buckets[kv.second].push_back(kv.first);
        
        vector<int> ans;
        for (int i = max_freq; i >= 1; --i) {
            auto it = buckets.find(i);
            if (it == buckets.end()) continue;
            ans.insert(ans.end(), it->second.begin(), it->second.end());
            if (ans.size() == k) return ans;
        }
        
        return ans;  
}


int main() 
{ 
	vector<int> vect{1,1,1,2,2,3}; 
	

    //auto it = find(vect.begin(), vect.end() , 4);
    //int dist = distance(vect.begin(), it) - 1;
    //cout << " dist  " << dist << endl; 

    //return 0; 

    vector<int> v = topKFrequent4(vect, 2); 

	for (int i=0; i<v.size(); i++)
        	cout << v[i] << " ";
    	cout << endl;


	return 0;
} 


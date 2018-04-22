class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0; 
        
        unordered_map<int, vector<int>> m; 
        for (int i = 0; i < routes.size(); ++i) { 
            for (const int stop: routes[i]) { 
                m[stop].push_back(i); 
            }
        }
        
        vector<int> visited(routes.size(), 0); 
        queue<int> q; 
        q.push(S); 
        int result = 0; 
        
        while (!q.empty()) { 
            result++; 
            int size = q.size(); 
            while (size--) { 
                int cur = q.front(); q.pop(); 
                for (int bus : m[cur]) { 
                    if (visited[bus]) continue; 
                    visited[bus] = 1; 
                    for (int stop: routes[bus]) { 
                        if (stop == T) return result; 
                        if (m.count(stop)) 
                            q.push(stop); 
                    
                    }
                
                }
            
            }
        
        }
        return -1; 
    }
};



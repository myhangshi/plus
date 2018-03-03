/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> mp;     
        queue<const UndirectedGraphNode *> q; 
        
        if (node == nullptr) return nullptr; 
        
        q.push(node); 
        mp[node] = new UndirectedGraphNode(node->label); 
        
        while (!q.empty()) { 
            const UndirectedGraphNode *cur = q.front(); 
            q.pop(); 
            
            for (auto nbr: cur->neighbors) { 
                if (mp.find(nbr) != mp.end()) { 
                    mp[cur]->neighbors.push_back(mp[nbr]); 
                } else { 
                    UndirectedGraphNode *next = new UndirectedGraphNode(nbr->label); 
                    mp[nbr] = next; 
                    mp[cur]->neighbors.push_back(mp[nbr]); 
                    q.push(nbr); 
                }
            }   
        }
        
        return mp[node];         
    }
};


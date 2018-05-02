
http://www.cnblogs.com/grandyang/p/8716597.html


//union find 
//stuff 
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int res = 0, n = row.size(), cnt = n / 2;
        vector<int> root(n, 0);
        for (int i = 0; i < n; ++i) root[i] = i;
        for (int i = 0; i < n; i += 2) {
            int x = find(root, row[i] / 2);
            int y = find(root, row[i + 1] / 2);
            if (x != y) {
                root[x] = y;
                --cnt;
            }
        }
        return n / 2 - cnt;
    }
    int find(vector<int>& root, int i) {
        return (i == root[i]) ? i : find(root, root[i]);
    }
};


class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int res = 0, n = row.size();
        for (int i = 0; i < n; i += 2) {
            if (row[i + 1] == (row[i] ^ 1)) continue;
            ++res;
            for (int j = i + 1; j < n; ++j) {
                if (row[j] == (row[i] ^ 1)) {
                    row[j] = row[i + 1];
                    row[i + 1] = row[i] ^ 1;
                    break;
                }
            }
        }
        return res;
    }
};



class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        
        vector<int> pos(row.size(), 0); 
        
        for (int i = 0; i < row.size(); i++) { 
            pos[row[i]] = i; 
        }
        
        int result = 0; 
        
        for (int i = 0; i < row.size(); i += 2) { 
            
            if (row[i]/2 == row[i+1]/2) continue; 
            
            int partner = 0; 
            
            if (row[i] % 2 == 0) partner = pos[row[i]+1];
            else partner = pos[row[i]-1];
            
            result++; 
            pos[row[i+1]] = partner; 
            swap(row[i+1], row[partner]); 
        
        }
        return result; 
    }
};



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *p1 = head; 
        ListNode *p2 = nullptr; 
        
        if (!p1 || !p1->next) return false; 
        
        p2 = p1->next; 
        while (p1 && p2) { 
            p1 = p1->next; 
            
            if (!p2->next) return false; 
            p2 = p2->next->next; 
            
            if (p1 == p2) return true; 
        }
        
        return false; 
        
        
    }
};


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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head; 
        
        for (ListNode *prev = head, *cur = head->next; cur; ) { 
            if (cur->val == prev->val) { 
                prev->next = cur->next; 
                delete(cur); 
            } else { 
                prev = cur; 
            }
            cur = cur->next; 
        
        }
        return head; 
    }
};



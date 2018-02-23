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
    ListNode* partition(ListNode* head, int x) {
        ListNode r_dummy(-1), l_dummy(-1); 
        ListNode *r_tail, *l_tail; 
        
        r_tail = &r_dummy; 
        l_tail = &l_dummy; 
        for (ListNode *cur = head; cur; cur = cur->next) { 
            if (cur->val < x) { 
                l_tail->next = cur; 
                l_tail = cur; 
            }  else { 
                r_tail->next = cur; 
                r_tail = cur;         
            }
        }
        
        l_tail->next = r_dummy.next; 
        r_tail->next = nullptr; 
        return l_dummy.next; 
    }
};



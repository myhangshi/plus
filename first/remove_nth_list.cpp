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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(-1); 
        ListNode *p = &dummy, *q = &dummy; 
        
        dummy.next = head; 
        for (int i = 0; i < n; i++) 
            q = q->next; 
        
        while (q->next) { 
            p = p->next; 
            q = q->next; 
        }
        
        ListNode *tmp = p->next; 
        p->next = p->next->next; 
        delete tmp; 
        return dummy.next; 
    }
};



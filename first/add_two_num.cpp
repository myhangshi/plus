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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1), *pa, *pb; 
        int carry = 0; 
        
        
        ListNode *prev = &dummy; 
        
        pa = l1; 
        pb = l2; 
        
        while (pa || pb) { 
            const int v1 = pa ? pa->val : 0; 
            const int v2 = pb ? pb->val : 0; 
            
            int s = v1 + v2 + carry; 
            prev-> next = new ListNode(s % 10); 
            prev = prev->next; 
            
            carry = s / 10; 
            if (pa) pa = pa->next; 
            if (pb) pb = pb->next; 
        }
        
        if (carry > 0)
            prev->next = new ListNode(carry); 
        
        return dummy.next; 
    }
};



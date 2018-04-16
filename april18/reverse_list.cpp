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
    ListNode* reverseList(ListNode* head) {
        
      
        ListNode* newHead = NULL; 
        
        while (head) { 
            ListNode* tmp = head->next; 
            head->next = newHead; 
            newHead = head; 
            head = tmp; 
        }
        return newHead;         
    }
};




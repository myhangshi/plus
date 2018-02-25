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
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head; 
        
        while (slow && fast->next) { 
            slow = slow->next; 
            fast = fast->next->next; 
            if (!fast) break; 
            
            if (slow == fast) { 
                ListNode *slow2 = head; 
                while (slow2 != slow) { 
                    slow2 = slow2->next; 
                    slow = slow->next;
                }
                return slow; 
            }
        }
        
        return nullptr; 
    }
};


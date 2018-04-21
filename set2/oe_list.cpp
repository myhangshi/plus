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
    ListNode* oddEvenList(ListNode* head) {
        ListNode OddDummy(0),  *od = &OddDummy; 
        ListNode EvenDummy(0), *ed = &EvenDummy; 
        
        if (head == NULL || head->next == NULL) return head; 
        bool flag = true; 
        
        while (head) { 
            ListNode *runner = head->next; 
            if (flag) { 
                od->next = head; 
                od = head; 
            } else { 
                ed->next = head; 
                ed = head; 
            }
            flag = !flag; 
            head = runner; 
        }
        
        od->next = EvenDummy.next; 
        ed->next = NULL; 
        return OddDummy.next; 
    }
};



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
    
    ListNode *reverse(ListNode *head) { 
        if (head == nullptr || head->next == nullptr) return head; 
        
        ListNode *prev = head, *next; 
        for (ListNode *curr = head->next; curr; ) { 
            next = curr->next; 
            curr->next = prev; 
            prev = curr; 
            curr = next; 
            //next = next ? next->next : nullptr; 
        }
        head->next = nullptr; 
        return prev; 
    }
    
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return; 
        
        ListNode *slow = head, *fast = head, *prev = nullptr; 
    
        while (fast && fast->next) { 
            prev = slow; 
            slow = slow->next; 
            fast = fast->next->next; 
        }
    
        prev->next = nullptr; 
        slow = reverse(slow); 
        
        ListNode *curr = head;
        ListNode dummy(-1), *new_list = &dummy; 
        
        while (curr) { 
            new_list->next = curr; 
            new_list = curr; 
            curr = curr->next; 
           
            
            new_list->next = slow; 
            new_list = slow; 
            slow = slow->next; 
        }
      
        
        
/* 
        
        while (curr->next) { 
            ListNode *tmp = curr->next; 
            curr->next = slow; 
            slow = slow->next; 
            
            curr->next->next = tmp; 
            curr = tmp; 
        
        }
        curr->next = slow; 
 */       
    }
};


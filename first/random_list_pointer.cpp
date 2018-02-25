/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *node = nullptr; 
        RandomListNode *cur = nullptr, *new_cur = nullptr; 
        
        for (cur = head; cur;) { 
            node = new RandomListNode(cur->label); 
            node->next = cur->next; 
            cur->next = node; 
            cur = node->next; 
        }
        
        for (cur = head; cur;) { 
            if (cur->random) {
                cur->next->random = cur->random->next; 
            } 
            cur = cur->next->next; 
        }
        
        RandomListNode dummy(-1); 
        for (cur = head, new_cur = &dummy; cur;) { 
            new_cur->next = cur->next; 
            new_cur = cur->next; 
            cur->next = cur->next->next; 
            cur = cur->next; 
        }
        return dummy.next; 
    }
};



#include <iostream>
#include <vector>
#include <cstddef>

 
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void deleteNode(ListNode* node, int val) {
     ListNode dummy(-1); 
     
     ListNode *prev = &dummy; 
     prev->next = node;    
     while (prev->next) { 
         if (prev->next->val == val) { 
  		        ListNode *tmp = prev->next; 
                prev->next = prev->next->next; 
                //delete tmp;   //static storage, no need to delete
         } else { 
                prev = prev->next; 
         }
      
    }
} 

void printList(ListNode *node) { 
    while (node) { 
	   cout << node->val << endl; 
       node = node->next; 
    } 
} 
 
int main()
{
    ListNode n1(2), n2(3), n3(4), n4(5); 

    n1.next = &n2; 
    n2.next = &n3; 
    n3.next = &n4; 
    n4.next = nullptr; 

    printList(&n1); 
    cout << endl << endl; 

    deleteNode(&n1, 3); 
    printList(&n1); 
    cout << endl << endl; 

    deleteNode(&n1, 5); 
    printList(&n1); 

 
    return 0;
 
}



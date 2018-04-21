#include <iostream> 

using namespace std; 


struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

ListNode* oddEvenList(ListNode* head) {
        ListNode OddDummy(0),  *od = &OddDummy; 
        ListNode EvenDummy(0), *ed = &EvenDummy; 
        
        if (head == NULL || head->next == NULL) return head; 
        
        while (head) { 
            ListNode *runner = head->next; 
	    cout<<"Inserted value is " << head->val << endl; 
            if (head->val % 2 == 1) { 
                od->next = head; 
                od = head; 
            } else { 
                ed->next = head; 
                ed = head; 
            } 
	    head->next = NULL; 
            head = runner; 
        }
        
        od->next = EvenDummy.next; 
        return OddDummy.next; 
}

int main() 
{ 
	ListNode n1(1); 
	ListNode n2(2); 
	ListNode n3(3); 

	n1.next = &n2; 
	n2.next = &n3; 
	ListNode *p1 = &n1; 

	while (p1) { 
	    cout << p1->val << endl; 
	    p1 = p1->next; 
	} 
	cout << " Invocation starts "<<endl;  

	p1 = oddEvenList(&n1); 

	// return 0;
	while (p1) { 
	    cout << p1->val << endl; 
	    p1 = p1->next; 
	} 

	return 0;
} 


//============================================================================
// Name        : reorder-list.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printList(ListNode *head){
	ListNode* curr = head;
	while(curr)
	{
		cout<<curr->val<<":";
		curr = curr->next;
	}
	cout<<endl;
}

void reverseList(ListNode **head) {
    if(*head==NULL) return;
    ListNode *curr = *head;
    ListNode *prev = NULL;
    while(curr!=NULL)
    {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    printList(prev);
    *head = prev;
}

void reorderList(ListNode *head) {
    if(head == NULL || head->next == NULL) return;
    ListNode *slow = head;
    ListNode *fast = head;
    ListNode *prev = slow;

    while(fast!=NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next;
        if(fast!=NULL) fast = fast->next;
    }
    ListNode *it1 = prev->next;
    prev->next = NULL;
    reverseList(&it1);
    ListNode *it2 = head;

    while(it1!=NULL && it2!=NULL)
    {
        ListNode* it2next = it2->next;
        ListNode* it1next = it1->next;
        it2->next = it1;
        it1->next = it2next;
        it2 = it2next;
        it1 = it1next;
    }
}

int main() {
	ListNode *node = new ListNode(1);
	node->next = new ListNode(2);
	node->next->next = new ListNode(3);
	node->next->next->next = new ListNode(4);

	reorderList(node);
	printList(node);
	return 0;
}

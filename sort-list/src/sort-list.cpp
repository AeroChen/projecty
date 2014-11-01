//============================================================================
// Name        : sort-list.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printList(ListNode *head)
{
	while(head)
	{
		cout<<head->val<<":";
		head = head->next;
	}
	cout<<endl;
}

ListNode *fillList(vector<int> input)
{
	if(input.empty()) return NULL;
	ListNode *head = new ListNode(input[0]);
	ListNode *last = head;
	for(int i=1; i<input.size();i++)
	{
		ListNode *curr = new ListNode(input[i]);
		last->next = curr;
		last = curr;
	}
	return head;
}

ListNode *splitList(ListNode *head)
{
    if(head == NULL || head->next == NULL) return head;
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *prev = slow;

    while(fast)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next ? fast->next->next : NULL;
    }
    prev->next = NULL;
    return slow;
}

ListNode *mergeList(ListNode *l1, ListNode *l2)
{
    ListNode dummy(-1);
    ListNode *curr = &dummy;
    while(l1 && l2)
    {
        if(l1->val >= l2->val)
        {
            curr->next = l2;
            l2 = l2->next;
        }
        else
        {
            curr->next = l1;
            l1 = l1->next;
        }
        curr = curr->next;
    }
    curr->next = l1? l1:l2;
    return dummy.next;
}

ListNode *sortList(ListNode *head) {
    if(head == NULL || head->next == NULL) return head;
    ListNode *headref = head;
    ListNode *halfref = splitList(headref);
    headref = sortList(headref);
    halfref = sortList(halfref);
    return mergeList(headref, halfref);
}

ListNode *insertionSortList(ListNode *head) {
    if(head==NULL) return NULL;
    ListNode dummy(0);
    dummy.next = head;
    ListNode *ptr1 = head;
    ListNode *prev = &dummy;
    while(ptr1)
    {
        ListNode *ptr2 = &dummy;
        while(ptr2!=prev)
        {
            if(ptr1->val >= ptr2->next->val) {
                ptr2 = ptr2->next;
                continue;
            }
            else {
            	prev->next = ptr1->next;
            	ptr1->next = ptr2->next;
            	ptr2->next = ptr1;
                break;
            }
        }
        if(ptr1==prev->next) prev = prev->next;
        ptr1 = prev->next;
    }
    return dummy.next;
}

int main() {
	int list[] = {4,3,2,1};
	ListNode* head = fillList(vector<int>(list, list + sizeof(list)/sizeof(int)));
	//printList(sortList(head));
	printList(insertionSortList(head));
	return 0;
}

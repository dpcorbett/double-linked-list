#include <stdlib.h>
#include "COMMON.H"
#include "DLLIST.H"
// Prototype for function pointer.
ListNode *MakeListNode(ListEntry x);
// Initialise list.
void CreateList(List *list) {
	list->count = 0;
	list->current = NULL;
	list->CurrentPos = -1;
}
// Create new node and return pointer.
ListNode *MakeListNode(ListEntry x) {
	ListNode *p;
	// Obtain space from system.
	p = (ListNode *)malloc(sizeof(ListNode));
	if (p) {
		p->entry = x;
		// Set pointer fields as a precaution.
		p->next = NULL;
		p->prev = NULL;
	} else {
		Error("No space for additional node can be obtained.")
	}
	return p;
}
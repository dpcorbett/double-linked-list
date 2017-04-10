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
// Clear list of nodes from start to finish.
void ClearList(List *list) {
	ListNode *temp;
	// Return to start of list.
	while ((list->current)->prev) {
		list->current = (list->current)->prev;
	}
	// Clear nodes until there is only one left.
	while (list->current != NULL) {
		temp = list->current;
		list->current = (list->current)->next;
		free(temp);
	}
	list->count = 0;
	list->CurrentPos = 0;
	free(list);
	CreateList(list);
}
// Returns false if list contains nodes.
Boolean ListEmpty(const List *list) {
	return (list->count == 0);
}

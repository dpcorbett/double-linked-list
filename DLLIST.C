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
		Error("No space for additional node can be obtained.");
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
// Always returns false as when malloc returns NULL when there is no memory.
Boolean ListFull(const List *list) {
	// TODO Needs to attempt to create a node and then free it, 
	// returning TRUE if malloc returns NULL.
	return (FALSE);
}
// Return the number of nodes in list.
Position ListSize(const List *list) {
	return (list->count);
}
// Insert new node at front of list. 
void InsertFirst(ListEntry x, List *list) {
	InsertList(0, x, list);
}
// Remove entry from specified index.
void DeleteList(Position p, ListEntry *x, List * list) {
	ListNode *temp;
	if (p < 0 || p > ListSize(list)) {
		Error("Attempt to delete in a position not in the list.");
	}
	else {
		SetPosition(0, list);
		if (p == 0) {
			temp = list->current;
			list->current = temp->next;
			// When there is more tham one node.
			if (temp->next) {
				temp->next->prev = NULL;
			}
		}
		else {
			// Position at node to left of target.
			SetPosition(p - 1, list);
			// Point to node to remove.
			temp = list->current->next;
			// Set current to node after target.
			list->current->next = temp->next;
			// Check if there are nodes to reattach.
			if (temp->next) {
				temp->next->prev = list->current;
			}
		}
		list->count--;
		*x = temp->entry;
		free(temp);
	}
}
// Point list entry parameter to index of plist.
void RetrieveList(Position p, ListEntry *x, List *list) {
	if (p < 0 || p > list->count) {
		Error("Attempt to retrieve from a position not in the list.");
	}
	else {
		SetPosition(p, list);
		(list->current)->entry = x;
	}
}
// Perform specified function on each node in list.
void TraverseList(List *list, void(*Visit)(ListEntry)) {
	ListEntry x;
	Position i = 0;
	do {
		RetrieveList(i, &x, list);
		(*Visit)(x);
		i++;
	} while (i < list->count);
}
// Insert new node at end of list. 
void InsertLast(ListEntry x, List *list) {
	InsertList(ListSize(list), x, list);
}
// Set current position in list.
void SetPosition(Position p, List *list) {
	if (p < 0 || p > list->count) {
		Error("Attempt to set position not in list.");
	}
	// Move up to position.
	else if (list->CurrentPos < p) {
		for (; list->CurrentPos != p; list->CurrentPos++) {
			list->current = list->current->prev;
		}
	}
	// Move down to position.
	else if (list->CurrentPos > p) {
		for (; list->CurrentPos != p; list->CurrentPos--) {
			list->current = (list->current)->prev;
		}
	}
}
// Insert into given index of list, other nodes are repositioned.
void InsertList(Position p, ListEntry x, List *list) {
	ListNode *newnode, *following;
	if (p < 0 || p > ListSize(list)) {
		Error("Attempt in a position not in the list.");
	}
	else {
		newnode = MakeListNode(x);
		// Insert at beginning of list.
		if (p == 0) {
			newnode->prev = NULL;
			// The list is empty.
			if (list->count == 0) {
				newnode->next = NULL;
			}
			// Insert at the start of existing list.
			else {
				SetPosition(0, list);
				newnode->next = list->current;
				(list->current)->prev = newnode;
			}
		}
		// Insert later in the list.
		else {
			SetPosition(p - 1, list);
			following = (list->current)->next;
			// Insert between current and following.
			newnode->next = following;
			newnode->prev = list->current;
			(list->current)->next = newnode;
			if (following) {
				following->prev = newnode;
			}
		}
		list->current = newnode;
		list->CurrentPos = p;
		list->count++;
	}
}
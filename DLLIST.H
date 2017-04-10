// Type Definitions.
typedef char ListEntry;
typedef struct listnode {
	ListEntry entry;
	struct listnode *next;
	struct listnode *prev;
} ListNode;
typedef int Position;
typedef struct list {
	int count;
	ListNode *current;
	Position CurrentPos;
} List;
// Function prototypes.
void CreateList(List *);
void ClearList(List *);
Boolean ListEmpty(const List *);
Boolean ListFull(const List *);
int ListSize(const List *);
void InsertList(Position p, ListEntry x, List *list);
void DeleteList(Position p, ListEntry *x, List *list);
void RetrieveList(Position p, ListEntry *x, List *list);
void ReplaceList(Position p, ListEntry x, List *list);
void TraverseList(List *, void(*)(ListEntry));
void SetPosition(Position p, List *list);
void InsertLast(Position p, List *list);
void InsertFirst(Position p, List *list);

#include "RBTTypes.h"

RBTPtr Initialize(void);
RBTNodePtr InsertKey(RBTNodePtr, Key);
RBTNodePtr RemoveKey(RBTNodePtr, Key);
int EmptyRBT(RBTNodePtr);
RBTNodePtr CreateNode(Key, NodeColor);
RBTNodePtr RestoreRBTProperties(RBTNodePtr);
void PrintRBT(RBTNodePtr, int);

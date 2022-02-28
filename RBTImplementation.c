#include <stdio.h>
#include <stdlib.h>
#include "RBTInterface.h"


RBTPtr Initialize(void) {
  RBTPtr tree = malloc (sizeof(RBT));
  if (tree == NULL) {
    printf("Memory allocation failed!\n");
  }
  tree->Root = NULL;
  return tree;
}

RBTNodePtr InsertKey(RBTNodePtr root, Key key) {
  RBTNodePtr temp, nodeptr, sibling;
  if (EmptyRBT(root)) {
    root = CreateNode(key, BLACK);
    return root;
  }
  temp = root;
  while (temp->LChild != NULL || temp->RChild != NULL ) {
    if (key <= temp->Data) {
      temp = temp->LChild;
    }
    else {   /* key > temp->Data */
      temp = temp->RChild;
    }
  }
  nodeptr = CreateNode(key, RED);
  if (key <= temp->Data) {
    temp->LChild = nodeptr;
  }
  else {   /* key > temp->Data */
    temp->RChild = nodeptr;
  }
  nodeptr->Parent = temp;
  root = RestoreRBTProperties(nodeptr);
  return root;
}

RBTNodePtr RemoveKey(RBTNodePtr root, Key key) {
/* Not implemented */
}

int EmptyRBT(RBTNodePtr root) {
  if (root == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

RBTNodePtr CreateNode(Key key, NodeColor color) {
  RBTNodePtr nodeptr;
  nodeptr = malloc(sizeof(RBTNode));
  if (nodeptr == NULL) {
    printf("Memory allocation failed!\n");
    return NULL;
  }
  nodeptr->Data = key;
  nodeptr->Color = color;
  nodeptr->Parent = NULL;
  nodeptr->LChild = NULL;
  nodeptr->RChild = NULL;
  return(nodeptr);
}

RBTNodePtr RestoreRBTProperties(RBTNodePtr nodeptr) {
  RBTNodePtr sibling;
  if(nodeptr->Parent != NULL && nodeptr->Parent->Color == RED && nodeptr->Parent->Parent != NULL) {
    if (nodeptr->Parent->Parent->LChild == nodeptr->Parent) {
      sibling = nodeptr->Parent->Parent->RChild;
    }
    else {   /* nodeptr->Parent->Parent->RChild == nodeptr->Parent */
      sibling = nodeptr->Parent->Parent->LChild;
    }
    if (sibling == NULL ||sibling->Color == BLACK) {    /* Rotations and colorfix */
      if (nodeptr->Parent->Parent->LChild == nodeptr->Parent) {
        if (nodeptr->Parent->LChild == nodeptr) {   /* Right rotation */
          nodeptr->Parent->Parent->LChild = nodeptr->Parent->RChild;
          nodeptr->Parent->RChild = nodeptr->Parent->Parent;
          nodeptr->Parent->Parent = nodeptr->Parent->Parent->Parent;
          if (nodeptr->Parent->RChild->Parent != NULL) {
            if (nodeptr->Parent->RChild->Parent->LChild == nodeptr->Parent->RChild) {
              nodeptr->Parent->RChild->Parent->LChild = nodeptr->Parent;
            }
            else {
              nodeptr->Parent->RChild->Parent->RChild = nodeptr->Parent;
            }
          }
          nodeptr->Parent->RChild->Parent = nodeptr->Parent;
          /* Colorfix */
          nodeptr->Parent->Color = BLACK;
          nodeptr->Parent->LChild->Color = RED;
          nodeptr->Parent->RChild->Color = RED;
        }
        else {   /* Left-Right rotation */
          nodeptr->Parent->Parent->LChild = nodeptr->RChild;
          nodeptr->RChild = nodeptr->Parent->Parent;
          nodeptr->Parent->RChild = nodeptr->LChild;
          nodeptr->LChild = nodeptr->Parent;
          nodeptr->Parent = nodeptr->RChild->Parent;
          if (nodeptr->RChild->Parent != NULL) {
            if (nodeptr->RChild->Parent->LChild == nodeptr->RChild) {
              nodeptr->RChild->Parent->LChild = nodeptr;
            }
            else {
              nodeptr->RChild->Parent->RChild = nodeptr;
            }
          }
          nodeptr->LChild->Parent = nodeptr;
          nodeptr->RChild->Parent = nodeptr;
          /* Colorfix */
          nodeptr->Color = BLACK;
          nodeptr->LChild->Color = RED;
          nodeptr->RChild->Color = RED;
        }
      }
      else {
        if (nodeptr->Parent->LChild == nodeptr) {   /* Right-Left rotation */
          nodeptr->Parent->Parent->RChild = nodeptr->LChild;
          nodeptr->LChild = nodeptr->Parent->Parent;
          nodeptr->Parent->LChild = nodeptr->RChild;
          nodeptr->RChild = nodeptr->Parent;
          nodeptr->Parent = nodeptr->LChild->Parent;
          if (nodeptr->LChild->Parent != NULL) {
            if (nodeptr->LChild->Parent->LChild == nodeptr->LChild) {
              nodeptr->LChild->Parent->LChild = nodeptr;
            }
            else {
              nodeptr->LChild->Parent->RChild = nodeptr;
            }
          }
          nodeptr->LChild->Parent = nodeptr;
          nodeptr->RChild->Parent = nodeptr;
          /* Colorfix */
          nodeptr->Color = BLACK;
          nodeptr->LChild->Color = RED;
          nodeptr->RChild->Color = RED;
        }
        else {   /* Left rotation */
          nodeptr->Parent->Parent->RChild = nodeptr->Parent->LChild;
          nodeptr->Parent->LChild = nodeptr->Parent->Parent;
          nodeptr->Parent->Parent = nodeptr->Parent->Parent->Parent;
          if (nodeptr->Parent->LChild->Parent != NULL) {
            if (nodeptr->Parent->LChild->Parent->LChild == nodeptr->Parent->LChild) {
              nodeptr->Parent->LChild->Parent->LChild = nodeptr->Parent;
            }
            else {
              nodeptr->Parent->LChild->Parent->RChild = nodeptr->Parent;
            }
          }
          nodeptr->Parent->LChild->Parent = nodeptr->Parent;
          /* Colorfix */
          nodeptr->Parent->Color = BLACK;
          nodeptr->Parent->LChild->Color = RED;
          nodeptr->Parent->RChild->Color = RED;
        }
      }
    }
    else {   /* sibling->Color == RED then recoloring and check again */
      if (nodeptr->Parent != NULL) {
        nodeptr->Parent->Color = BLACK;
        if (nodeptr->Parent->Parent != NULL) {
          if (nodeptr->Parent->Parent->LChild == nodeptr->Parent) {
            sibling = nodeptr->Parent->Parent->RChild;
          }
          else {   /* nodeptr->Parent->Parent->RChild == nodeptr->Parent */
            sibling = nodeptr->Parent->Parent->LChild;
          }
          if (sibling != NULL) {
            sibling->Color = BLACK;
          }
          if (nodeptr->Parent->Parent->Parent != NULL) {
            nodeptr->Parent->Parent->Color = RED;
          }
        }
      }
      nodeptr = RestoreRBTProperties(nodeptr->Parent->Parent);   /* Recursive call in case of double-red problem propagation */
    }
  }
  while (nodeptr->Parent != NULL) {
    nodeptr = nodeptr->Parent;
  }
  return nodeptr;
}

void PrintRBT(RBTNodePtr root, int space) {
  int i;
  if (EmptyRBT(root)) {  // Base case
    return;
  }
  space += 10;  // Increase distance between levels
  PrintRBT(root->RChild, space);  // Process right child first
  printf("\n");
  for (i = 10; i < space; i++) {
    printf(" ");
  }
  printf("%d", root->Data);  // Print current node after spaces
  if (root->Color == RED) {
    printf("R\n");
  }
  else if (root->Color == BLACK) {
    printf("B\n");
  }
  else {
    printf("DB\n"); //Double black
  }
  PrintRBT(root->LChild, space);  // Process left child
}

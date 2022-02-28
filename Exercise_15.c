#include <stdio.h>
#include "RBTInterface.h"
#define K 9   /* Some keys to insert */
#define I 5   /* Spaces between trees*/

int main(void) {
	RBTPtr tree;
  Key k;
  int i;
  tree = Initialize();
	for (k = 1; k <= K; k++) {
    tree->Root = InsertKey(tree->Root, k);
	  printf("Insert %d:", k);
    PrintRBT(tree->Root, 20);
	  for (i = 1; i <= I; i++) {
	    printf("\n");
    }
  }
  return 0;
}

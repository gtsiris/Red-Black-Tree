#ifndef RBTTypes_h
#define RBTTypes_h

enum colors {RED, BLACK, DOUBLEBLACK};

typedef int Key;

typedef char NodeColor;

typedef struct RBTNodeTag *RBTNodePtr;

typedef struct RBTNodeTag {
  Key Data;
  NodeColor Color;
  RBTNodePtr Parent;
  RBTNodePtr LChild;
  RBTNodePtr RChild;
} RBTNode;

typedef struct RBTTag *RBTPtr;

typedef struct RBTTag {
  RBTNodePtr Root;
}RBT;

#endif   /* RBTTypes_h */

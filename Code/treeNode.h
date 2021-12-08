#ifndef TREENODE_H
#define TREENODE_H__DATE__ " " __TIME__

typedef struct ASTreeNode ASTreeNode;
struct ASTreeNode {
    char* val;          // the value printed when identifying this node

    ASTreeNode* child0;   // the leftmost child
    ASTreeNode* child1;
    ASTreeNode* child2;   // rightmost child

    ASTreeNode* sibling;  // each node has just one sibling pointing a right node @ same level
};
#endif

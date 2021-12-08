#ifndef MEMLOC_H
#define MEMLOC_H__DATE__ " " __TIME__
#include <vector>
#include <utility>
#include <iostream>
//#include "symbolTable.cpp"

// Utils for allocating and assigning memory in the program
class Memloc {
    private:
        int loc;
        int goffset;    // global offset
        int foffset;    // frame offset
        int comp_count = 0;

        bool ignore_next_comp; // set this flag when funDec is seen so that parameters are included in function scope, remove after entering first compStmt

        SymbolTable st;

        // construct compound statements in layers like an onion with the last element in stack
        // as the inner most layer of the onion
        std::vector<std::pair<ASTreeNode*, int>> compoundStack;
        void init();   // set initial values for loc, goffset, and foffset

    public:
        Memloc();
        int enterVariable(ASTreeNode*);
        int enterParameter(ASTreeNode*);
        int enterArray(ASTreeNode*, int);
        int enterID(ASTreeNode*);               // lookup the variable in the symbol table and get location info
        int enterConstString(ASTreeNode*);
        int enterFunction(ASTreeNode*, int);
        void leaveFunction();   // reset frame offset
        int enterScope(ASTreeNode*);
        void leaveScope(ASTreeNode*);
        int incrementCompound(int); // increment the size of the current compound by int

        bool isGlobal(VarKind vk); // return true if should be allocated in global space
        bool hasScope(ASTreeNode*); // return true if a scope has or will be created on the symbol table for this node

        int traverseTree(ASTreeNode*); // pre-order traversal that resolves relative location of nodes
        void resolveNode(ASTreeNode*);  // calculate the offset of this node

};
#endif

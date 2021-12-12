#ifndef SEMANTIC_H
#define SEMANTIC_H__DATE__ " " __TIME__
#include <iostream>
#include <vector>
//#include "symbolTable.cpp"
#include "TreeUtils.cpp"


class SemanticAnalyzer {
    private:
        SymbolTable st;

        std::vector<char*> errorStack;
        std::vector<char*> warningStack;

        // create an empty map with linenumber keys and storing vectors of string errors/warnings
        std::map<int, std::vector<std::string>> semanticErrors;
        std::map<int, std::vector<std::string>> semanticWarnings;
        bool hasMain = 0;

        ASTreeNode* currFunction = NULL; // when we enter a function store the root here

        // start points for traversals
        void preOrderTraversal(ASTreeNode* root);
        void postOrderTraversal(ASTreeNode* root);
        //void addNode(ASTreeNode* n);

        // add language libraries to symbol table
        ASTreeNode* buildIOAST();

        // helper functions for pre-order checks
        void checkForMain(ASTreeNode* n);
        void scopeCleanup(ASTreeNode*);
        void copyData(ASTreeNode*, ASTreeNode*);            // copy flags and details from one node to another
        void checkVarsUsed(std::map<std::string, void*>);
        // pre-order checks
        void preOrderCheck(ASTreeNode*);
        void preCheckDecl(ASTreeNode*);
        void preCheckStmt(ASTreeNode*);
        void preCheckExp(ASTreeNode*);
        // declaration handlers, enter into symbol table, set flags
        bool declareVar(ASTreeNode*);
        void declareFunction(ASTreeNode*);
        // initializers for variables, set usage flags
        void initializeVar(ASTreeNode*);
        void initializeLeftMostVar(ASTreeNode*);
        // check functions to get references and check/set flags
        bool isIDandArray(ASTreeNode*);
        void checkRange(ASTreeNode*);
        void checkCall(ASTreeNode*, int);
        void checkSideInitialized(ASTreeNode*);
        void checkVarInitialized(ASTreeNode*);
        void checkIsInitialized(ASTreeNode*, ASTreeNode*, std::string);

        // helper functions for post-order checks
        void postCheck(ASTreeNode*);
        void postCheckStmt(ASTreeNode*);
        void postCheckExp(ASTreeNode*);
        void checkCallPost(ASTreeNode*, int);
        ExpType checkActionTypes(ASTreeNode*, ExpKind);
        ExpType checkBinaryOp(ASTreeNode*, std::string);
        ExpType checkUnaryOp(ASTreeNode*, std::string);
        void checkAgainstExpected(ExpType, ExpType, ExpType, int, std::string);
        ExpType checkAgainstEachother(ASTreeNode*, ASTreeNode*, int, std::string);

        // error and warning handlers
        void printSemanticMsg(std::vector<std::string>);    // print a set of errors in order
        void addError(std::string errorMsg, int line);      // add error to print queue by line and increment number of errors
        void addWarning(std::string warning, int line);      // add warning and increment number of errors

        int numErrors;
        int numWarnings;

    public:
        SemanticAnalyzer();
        void printSemanticOutput(void);                     // print warnings and errors
        void semanticCheck(ASTreeNode*, bool);

        int getWarnings();
        int getErrors();
        SymbolTable getST();
};

#endif

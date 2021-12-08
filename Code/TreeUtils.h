#ifndef TREEUTILS_H
#define TREEUTILS_H__DATE__ " " __TIME__

class TreePrinter {
    private:
        // printing normal tree here
        static void printTree(ASTreeNode* root, int childnum, int level);
        static void printSTree(ASTreeNode* root, int level, int siblingOrder);
        static void printNodeTest(ASTreeNode* n);
        static void printTerminal(ASTreeNode* n);
        static void printDecl(ASTreeNode* n);
        static void printExp(ASTreeNode* n);
        static void printStmt(ASTreeNode* n);

        // printing annotated tree here
        static void printATree(ASTreeNode* root, int childnum, int level);
        static void printASTree(ASTreeNode* root, int level, int siblingOrder);
        static void printANodeTest(ASTreeNode* n);
        static void printATerminal(ASTreeNode* n);
        static void printADecl(ASTreeNode* n);
        static void printAExp(ASTreeNode* n);
        static void printAStmt(ASTreeNode* n);

        // printing augmented tree here
        static void printAugTree(ASTreeNode* root, int childnum, int level);
        static void printAugSTree(ASTreeNode* root, int level, int siblingOrder);
        static void printAugNodeTest(ASTreeNode* n);
        static void printAugTerminal(ASTreeNode* n);
        static void printAugDecl(ASTreeNode* n);
        static void printAugExp(ASTreeNode* n);
        static void printAugStmt(ASTreeNode* n);

        static std::string to_string(ASTreeNode*);
        static void printMemloc(ASTreeNode*, bool);

    public:
        static void printAnnotatedNode(ASTreeNode* n);
        static void printAugmentedNode(ASTreeNode* n);
        static void printNode(ASTreeNode* n);
        static void printTree(ASTreeNode* root);
        static void printAnnotatedTree(ASTreeNode* root);
        static void printAugmentedTree(ASTreeNode* root);
};

// node creation functions
static ASTreeNode* tokenToNode(struct Token* tkn); // convert a token to an AST node
static ASTreeNode* createNode(NodeKind nk);
static ASTreeNode* createOpNode(const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2);
static ASTreeNode* createStmtNode(StmtKind k, const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2);
static ASTreeNode* createDeclNode(DeclKind k, ExpType type, const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2);

// convert enum to string functions
static const char* typeToStr(ExpType type);
static const char* varToStr(VarKind k);

#endif

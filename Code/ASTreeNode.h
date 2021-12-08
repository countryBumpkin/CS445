#ifndef TREENODE_H
#define TREENODE_H__DATE__ " " __TIME__

// Kinds of Operators
// these are the token numbers for the operators same as in flex
typedef int OpKind;
// Kinds of Statements
//typedef enum {DeclK, StmtK, ExpK} NodeKind;
enum NodeKind {DeclK, StmtK, ExpK, TerminalK};
// Subkinds of Declarations
enum DeclKind {VarK, FuncK, ParamK};
// Subkinds of Statements
enum StmtKind {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK};
// Subkinds of Expressions
enum ExpKind {OpK, ConstantK, IdK, AssignK, InitK, CallK};
// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
enum ExpType {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType};
// What kind of scoping is used?  (decided during typing)
enum VarKind {None, Local, Global, Parameter, LocalStatic};
// What type of terminal is it?
enum TermKind {IDK, NUMC, DECL};

typedef struct ASTreeNode ASTreeNode;
struct ASTreeNode {

    NodeKind nodekind;    // DeclK, StmtK, ExpK or TerminalK
    union subkind {       // define kind more specifically
      DeclKind decl;
      StmtKind stmt;
      ExpKind exp;
      TermKind term;
    } subkind;

    union attrib {        // attributes of this node, metadata
      OpKind op;
      int value;
      unsigned char cvalue;
      char* name;
    } attrib;

    // memory info
    VarKind varkind = None;
    int size = 0; // value size in words
    int loc = 1; // the location of this symbol in the stack, 1 is uninitialized

    // content info
    int num_params = 0; // store (0)number of parameters, (2)is used
    std::map<int, std::pair<ExpType, bool>> params;
    char* str;
    ExpType type;
    int linenum;
    int numCVal; //  holder for numconstants

    // state info
    bool isStatic = false;
    bool isArray = false;
    bool isInitialized = false;
    bool isUsed = false;
    bool hasReturn = false;
    bool hasInit = true;
    ASTreeNode* declaration = NULL; // reference to first declaration

    // relative nodes
    ASTreeNode* children[3];
    ASTreeNode* sibling;  // each node has just one sibling pointing a right node @ same level
};
#endif

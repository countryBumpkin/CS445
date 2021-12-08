#include "TreeUtils.h"

// create a new ASTreeNode that will have the token information for printing
ASTreeNode* tokenToNode(Token* tkn) // convert a token to an AST node
{
  ASTreeNode* newN = new ASTreeNode;
  newN->sibling = NULL;
  newN->children[0] = NULL;
  newN->children[1] = NULL;
  newN->children[2] = NULL;
  newN->nodekind = ExpK;  // enum in ASTreeNode for print stuff
  //newN->attrib.op = tkn->tokenclass;    // RETURN etc
  if(tkn->tokenclass == 12)
  {
    newN->numCVal = tkn->numValue;
  }
  if(strcmp(tkn->token_str, "\'\\0\'") == 0) tkn->token_str = strdup("\' \'");
  newN->attrib.name = strdup(tkn->token_str);   // terminal character or string value, eg 'return' or ';'
  newN->linenum = tkn->linenum;

  return newN;
}

// create a new ASTreeNode and set the general type of node
ASTreeNode* createNode(NodeKind nk)
{
    ASTreeNode* newN = new ASTreeNode;
    newN->sibling = NULL;
    newN->children[0] = NULL;
    newN->children[1] = NULL;
    newN->children[2] = NULL;
    newN->nodekind = nk;
    return newN;
}

// create a ExpK node of type OpK
ASTreeNode* createOpNode(const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2)
{
    ASTreeNode* newN = new ASTreeNode;
    newN->nodekind = ExpK;
    newN->subkind.exp = OpK;
    newN->sibling = NULL;
    newN->children[0] = c0;
    newN->children[1] = c1;
    newN->children[2] = c2;
    newN->linenum = linenum;

    if(strcmp(s, "=") == 0 || strcmp(s, "><") == 0)
      newN->type = Equal;

    //printf("CREATING NODE FOR OP %s: on line number = %d\n", s, linenum);
    newN->attrib.name = strdup(s);

    return newN;
}

// create a StmtK node
ASTreeNode* createStmtNode(StmtKind k, const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2)
{
    ASTreeNode* newN = new ASTreeNode;
    newN->nodekind = StmtK;
    newN->subkind.stmt = k;
    newN->sibling = NULL;
    newN->children[0] = c0;
    newN->children[1] = c1;
    newN->children[2] = c2;
    newN->linenum = linenum;
    newN->attrib.name = strdup(s);

    return newN;
}

ASTreeNode* createDeclNode(DeclKind k, ExpType type, const char* s, int linenum, ASTreeNode* c0, ASTreeNode* c1, ASTreeNode* c2)
{
    ASTreeNode* newN = new ASTreeNode;
    newN->nodekind = DeclK;
    if(k == ParamK){newN->varkind = Parameter;}
    newN->subkind.decl = k;
    newN->sibling = NULL;
    newN->children[0] = c0;
    newN->children[1] = c1;
    newN->children[2] = c2;
    newN->linenum = linenum;
    newN->attrib.name = strdup(s);
    newN->type = type;

    return newN;
}

// print an expression type
const char* typeToStr(ExpType type)
{
    switch(type)
    {
        case Void:
            return "void";
            break;
        case Integer:
            return "int";
            break;
        case Boolean:
            return "bool";
            break;
        case Char:
            return "char";
            break;
        case CharInt:
            return "charInt";
            break;
        case Equal:
            return "Equal";
            break;
        case UndefinedType:
            return "Undefined Type";
            break;
        default:
            return "Error unknown type";
            break;
    }
}

// print out the string for the variable type
const char* varToStr(VarKind k)
{
    switch(k)
    {
        case None:
            return "None";
            break;
        case Local:
            return "Local";
            break;
        case Global:
            return "Global";
            break;
        case Parameter:
            return "Parameter";
            break;
        case LocalStatic:
            return "LocalStatic";
            break;
        default:
            return "Error unknown variable type here\n";
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  PRINT NORMAL TREE                                                         //
////////////////////////////////////////////////////////////////////////////////
void TreePrinter::printNodeTest(ASTreeNode* n)
{
  printf("\nNODE TEST DATA\n");
  printNode(n);
  if(n->sibling != NULL)
  {
    printf("  has sibling\n");
    printf("  ");
    printNode(n->sibling);
  }

  for(int i = 0; i < 3; i++)
  {
    if(n->children[i] != NULL)
    {
      printf("  has child %i\n\n", i);
    }
  }
}

void TreePrinter::printNode(ASTreeNode* n)
{
    if(n == NULL) return;
    switch(n->nodekind)
    {
        case TerminalK:
            printTerminal(n);
            break;
        case DeclK:
            printDecl(n);
            break;
        case StmtK:
            printStmt(n);
            break;
        case ExpK:
            printExp(n);
            break;
        default:
            printf("ERROR: UNKNOWN NodeKind\n");
            break;
    }
}

void TreePrinter::printTerminal(ASTreeNode* n)
{
    switch(n->subkind.term)
    {
        case IDK:
            printf("Id: %s", n->attrib.name);
            break;

        default:
            printf("ERROR UNKNOWN TermKind\n");
            break;
    }
}

void TreePrinter::printDecl(ASTreeNode* n)
{
    switch(n->subkind.decl)
    {
        case FuncK:
            printf("Func: %s returns type %s", n->attrib.name, typeToStr(n->type));
            break;

        case VarK:
            if(n->isArray) printf("Var: %s of array of type %s", n->attrib.name, typeToStr(n->type));
            else if(n->isStatic) printf("Var: %s of static type %s", n->attrib.name, typeToStr(n->type));
            else printf("Var: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case ParamK:
            if(n->isArray) {printf("Parm: %s of array of type %s", n->attrib.name, typeToStr(n->type));}
            else {printf("Parm: %s of type %s", n->attrib.name, typeToStr(n->type));}
            break;
        default:
            printf("ERROR unknown subtype of DECL\n");
            break;
    }
}

void TreePrinter::printStmt(ASTreeNode* n)
{
    switch(n->subkind.stmt)
    {
        case ReturnK:
            printf("Return");
            break;
        case BreakK:
            printf("Break");
            break;
        case CompoundK:
            printf("Compound");
            break;
        case IfK:
            printf("If");
            break;
        case WhileK:
            printf("While");
            break;
        case ForK:
            printf("For");
            break;
        case RangeK:
            printf("Range");
            break;
        default:
            printf("ERROR UNKOWN StmtKind\n");
    }
}

void TreePrinter::printExp(ASTreeNode* n)
{
    switch(n->subkind.exp)
    {
        case ConstantK:
            printf("Const %s", n->attrib.name);
            break;
        case IdK:
            printf("Id: %s", n->attrib.name);
            break;
        case AssignK:
            printf("Assign: %s", n->attrib.name);
            break;
        case OpK:
            printf("Op: %s", n->attrib.name);
            break;
        case CallK:
            printf("Call: %s", n->attrib.name);
            break;
        case InitK:
            break;
        default:
            printf("1ERROR unknown ExpKind");
            break;
    }
}

// print all nodes in the tree, should traverse the tree in prefix order
void TreePrinter::printTree(ASTreeNode* root, int childnum, int level)
{
    if(root == NULL) return;
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    if(childnum >= 0) printf("Child: %i  ", childnum);
    printNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
      if(root->children[i] != NULL){
          printTree(root->children[i], i, level+1);
      }
    }

    if(root->sibling != NULL)
    {
        printSTree(root->sibling, level, 1); // if there is a sibling print it
    }
}

// print sibling tree
void TreePrinter::printSTree(ASTreeNode* root, int level, int siblingOrder)
{
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    // print sibling index
    printf("Sibling: %i  ", siblingOrder);
    printNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
      if(root->children[i] != NULL){
        printTree(root->children[i], i, level+1);
      }
    }

    if(root->sibling != NULL)
    {
        printSTree(root->sibling, level, ++siblingOrder); // if there is a sibling print it
    }
}

// start printing the tree here
void TreePrinter::printTree(ASTreeNode* root)
{
    printTree(root, -1, 0);
}


////////////////////////////////////////////////////////////////////////////////
//  ANNOTATED TREE PRINTING                                                   //
////////////////////////////////////////////////////////////////////////////////
void TreePrinter::printANodeTest(ASTreeNode* n)
{
    printf("\nNODE TEST DATA\n");
    printAnnotatedNode(n);
    if(n->sibling != NULL)
    {
        printf("  has sibling\n");
        printf("  ");
        printAnnotatedNode(n->sibling);
    }

    for(int i = 0; i < 3; i++)
    {
        if(n->children[i] != NULL)
        {
            printf("  has child %i\n\n", i);
        }
    }
}

void TreePrinter::printAnnotatedNode(ASTreeNode* n)
{
    switch(n->nodekind)
    {
        case TerminalK:
        printATerminal(n);
        break;
        case DeclK:
        printADecl(n);
        break;
        case StmtK:
        printAStmt(n);
        break;
        case ExpK:
        printAExp(n);
        break;
        default:
        printf("ERROR: UNKNOWN NodeKind\n");
        break;
    }
}

void TreePrinter::printATerminal(ASTreeNode* n)
{
    switch(n->subkind.term)
    {
        case IDK:
        printf("Id: %s of type %s", n->attrib.name, typeToStr(n->type));
        break;

        default:
        printf("ERROR UNKNOWN TermKind\n");
        break;
    }
}

void TreePrinter::printADecl(ASTreeNode* n)
{
    switch(n->subkind.decl)
    {
        case FuncK:
        printf("Func: %s returns type %s", n->attrib.name, typeToStr(n->type));
        break;

        case VarK:
        if(n->isArray) printf("Var: %s of array of type %s", n->attrib.name, typeToStr(n->type));
        else if(n->isStatic) printf("Var: %s of type %s", n->attrib.name, typeToStr(n->type));
        else printf("Var: %s of type %s", n->attrib.name, typeToStr(n->type));
        break;
        case ParamK:
        if(n->isArray) {printf("Parm: %s of array of type %s", n->attrib.name, typeToStr(n->type));}
        else {printf("Parm: %s of type %s", n->attrib.name, typeToStr(n->type));}
        break;
        default:
        printf("ERROR unknown subtype of DECL\n");
        break;
    }
}

void TreePrinter::printAStmt(ASTreeNode* n)
{
    switch(n->subkind.stmt)
    {
        case ReturnK:
        printf("Return");
        break;
        case BreakK:
        printf("Break");
        break;
        case CompoundK:
        printf("Compound");
        break;
        case IfK:
        printf("If");
        break;
        case WhileK:
        printf("While");
        break;
        case ForK:
        printf("For");
        break;
        case RangeK:
        printf("Range");
        break;
        default:
        printf("ERROR UNKOWN StmtKind\n");
    }
}

void TreePrinter::printAExp(ASTreeNode* n)
{
    switch(n->subkind.exp)
    {
        case ConstantK:
            if(n->isArray) printf("Const is array %s of type %s", n->attrib.name, typeToStr(n->type));
            else printf("Const %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case IdK:
            printf("Id: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case AssignK:
            printf("Assign: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case OpK:
            printf("Op: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case CallK:
            printf("Call: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case InitK:
            break;
        default:
            printf("2ERROR unknown ExpKind %s\n", n->attrib.name);
            break;
    }
}

// print all nodes in the tree, should traverse the tree in prefix order
void TreePrinter::printATree(ASTreeNode* root, int childnum, int level)
{
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    if(childnum >= 0) printf("Child: %i  ", childnum);
    printAnnotatedNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
        if(root->children[i] != NULL){
            printATree(root->children[i], i, level+1);
        }
    }

    if(root->sibling != NULL)
    {
        printASTree(root->sibling, level, 1); // if there is a sibling print it
    }
}

// print sibling tree
void TreePrinter::printASTree(ASTreeNode* root, int level, int siblingOrder)
{
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    // print sibling index
    printf("Sibling: %i  ", siblingOrder);
    printAnnotatedNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
        if(root->children[i] != NULL){
            printATree(root->children[i], i, level+1);
        }
    }

    if(root->sibling != NULL)
    {
        printASTree(root->sibling, level, ++siblingOrder); // if there is a sibling print it
    }
}

// start printing the tree here
void TreePrinter::printAnnotatedTree(ASTreeNode* root)
{
    printATree(root, -1, 0);
}

////////////////////////////////////////////////////////////////////////////////
//  PRINT AUGMENTED TREE (memory information)                                 //
////////////////////////////////////////////////////////////////////////////////
void TreePrinter::printAugNodeTest(ASTreeNode* n)
{
    printf("\nNODE TEST DATA\n");
    printAnnotatedNode(n);
    if(n->sibling != NULL)
    {
        printf("  has sibling\n");
        printf("  ");
        printAnnotatedNode(n->sibling);
    }

    for(int i = 0; i < 3; i++)
    {
        if(n->children[i] != NULL)
        {
            printf("  has child %i\n\n", i);
        }
    }
}

void TreePrinter::printAugmentedNode(ASTreeNode* n)
{
    switch(n->nodekind)
    {
        case TerminalK:
            printAugTerminal(n);
            break;
        case DeclK:
            printAugDecl(n);
            break;
        case StmtK:
            printAugStmt(n);
            break;
        case ExpK:
            printAugExp(n);
            break;
        default:
            printf("ERROR: UNKNOWN NodeKind\n");
            break;
    }
}

void TreePrinter::printAugTerminal(ASTreeNode* n)
{
    switch(n->subkind.term)
    {
        case IDK:
        printf("Id: %s of type %s", n->attrib.name, typeToStr(n->type));
        break;

        default:
        printf("ERROR UNKNOWN TermKind\n");
        break;
    }
}

void TreePrinter::printAugDecl(ASTreeNode* n)
{
    std::string stat = n->isStatic ? "static " : "";
    switch(n->subkind.decl)
    {
        case FuncK:
            printf("Func: %s returns type %s", n->attrib.name, typeToStr(n->type));
            break;

        case VarK:
            if(n->isArray) printf("Var: %s of %sarray of type %s", n->attrib.name, stat.c_str(), typeToStr(n->type));
            else if(n->isStatic) printf("Var: %s of %stype %s", n->attrib.name, stat.c_str(), typeToStr(n->type));
            else printf("Var: %s of %stype %s", n->attrib.name, stat.c_str(), typeToStr(n->type));
            break;
        case ParamK:
            if(n->isArray) {printf("Parm: %s of array of type %s", n->attrib.name, typeToStr(n->type));}
            else {printf("Parm: %s of type %s", n->attrib.name, typeToStr(n->type));}
            break;
        default:
            printf("ERROR unknown subtype of DECL\n");
            break;
    }

    // print memory info before line number
    printMemloc(n, false);
}

void TreePrinter::printAugStmt(ASTreeNode* n)
{
    switch(n->subkind.stmt)
    {
        case ReturnK:
            printf("Return");
            break;
        case BreakK:
            printf("Break");
            break;
        case CompoundK:
            printf("Compound");
            printMemloc(n, false);
            break;
        case IfK:
            printf("If");
            break;
        case WhileK:
            printf("While");
            break;
        case ForK:
            printf("For %s", to_string(n).c_str());
            break;
        case RangeK:
            printf("Range");
            break;
        default:
            printf("ERROR UNKOWN StmtKind\n");
    }
}

void TreePrinter::printAugExp(ASTreeNode* n)
{
    std::string stat = n->isStatic ? "static " : "";
    std::string arr = n->isArray ? "array of " : "";
    std::string mem_info_for_const = n->isArray ? to_string(n) : "";

    switch(n->subkind.exp)
    {
        case ConstantK:
            printf("Const %s of %stype %s%s", n->attrib.name, arr.c_str(), typeToStr(n->type), mem_info_for_const.c_str());
            break;
        case IdK:
            printf("Id: %s of %s%stype %s", n->attrib.name, stat.c_str(), arr.c_str(), typeToStr(n->type));
            printMemloc(n, false);
            break;
        case AssignK:
            printf("Assign: %s of %stype %s", n->attrib.name, arr.c_str(), typeToStr(n->type));
            break;
        case OpK:
            printf("Op: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case CallK:
            printf("Call: %s of type %s", n->attrib.name, typeToStr(n->type));
            break;
        case InitK:
            break;
        default:
            printf("ERROR unknown ExpKind %s\n", n->attrib.name);
            break;
    }
}

// print all nodes in the tree, should traverse the tree in prefix order
void TreePrinter::printAugTree(ASTreeNode* root, int childnum, int level)
{
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    if(childnum >= 0) printf("Child: %i  ", childnum);
    printAugmentedNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
        if(root->children[i] != NULL){
            printAugTree(root->children[i], i, level+1);
        }
    }

    if(root->sibling != NULL)
    {
        printAugSTree(root->sibling, level, 1); // if there is a sibling print it
    }
}

// print sibling tree
void TreePrinter::printAugSTree(ASTreeNode* root, int level, int siblingOrder)
{
    // print indent level
    for(int i = 0; i < level; i++)
    {
        printf(".   ");
    }
    // print sibling index
    printf("Sibling: %i  ", siblingOrder);
    printAugmentedNode(root);  // print root on same line
    printf(" [line: %i]\n", root->linenum);
    for(int i = 0; i < 3; i++)  // print trees below children
    {
        if(root->children[i] != NULL){
            printAugTree(root->children[i], i, level+1);
        }
    }

    if(root->sibling != NULL)
    {
        printAugSTree(root->sibling, level, ++siblingOrder); // if there is a sibling print it
    }
}

// start printing the tree here
void TreePrinter::printAugmentedTree(ASTreeNode* root)
{
    printAugTree(root, -1, 0);
}

// convert memory information into a string that can be printed
std::string TreePrinter::to_string(ASTreeNode* n){
    std::string str = " [mem: "+std::string(varToStr(n->varkind))+" loc: "+std::to_string(n->loc)+" size: "+std::to_string(n->size)+"]";
    return str;
}

// prints the string form of a node's memory information, add a newline if second param is true
void TreePrinter::printMemloc(ASTreeNode* n, bool print_nl){
    std::cout << to_string(n);
    if(print_nl) std::cout << std::endl;
}

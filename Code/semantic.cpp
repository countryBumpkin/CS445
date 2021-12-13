#include "semantic.h"

SemanticAnalyzer::SemanticAnalyzer(){
    // build the IO reference tree for semantic checking
    ASTreeNode* ioroot = buildIOAST();
    preOrderTraversal(ioroot);

    numErrors = 0;
    numWarnings = 0;
}

// traverse all nodes in the tree, generate the semantic tree and peform semantic checks
void SemanticAnalyzer::semanticCheck(ASTreeNode* root, bool st_debug)
{
    if(st_debug) st.debug(true); // print symbol table debug information
    preOrderTraversal(root);
    checkVarsUsed(st.getSymbols());
    postOrderTraversal(root);

    if(!hasMain){numErrors++; printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");}
}

void SemanticAnalyzer::checkForMain(ASTreeNode* n){
    if(strcmp(n->attrib.name,"main") == 0){
        if((n->type == Integer || n->type == Void) && n->num_params == 0){
            hasMain = true;
            // set memory info on this node, though size should already be known
            n->loc = 0;
        }
    }
}

// iterate through all lines in map and print all errors/warnings by line
void SemanticAnalyzer::printSemanticOutput()
{
    bool e_atEnd = semanticErrors.empty();
    bool w_atEnd = semanticWarnings.empty();
    std::map<int,std::vector<std::string>>::iterator e_iter = semanticErrors.begin();
    std::map<int,std::vector<std::string>>::iterator w_iter = semanticWarnings.begin();

    while(!e_atEnd || !w_atEnd)
    {
        if(!e_atEnd)
        {
            if(!w_atEnd && w_iter->first < e_iter->first) // print the w_iter because it isn't at end and has lower line num
            {
                printSemanticMsg(w_iter->second);
                w_iter++;
                w_atEnd = (w_iter == semanticWarnings.end());
                continue;
            }

            printSemanticMsg(e_iter->second);
            e_iter++;
            e_atEnd = (e_iter == semanticErrors.end());

        }else if(!w_atEnd)
        {
            printSemanticMsg(w_iter->second);
            w_iter++;
            w_atEnd = (w_iter == semanticWarnings.end());
        }
    }
}

// print all messages in a vector
void SemanticAnalyzer::printSemanticMsg(std::vector<std::string> msgs)
{
    for(std::vector<std::string>::iterator it=msgs.begin(); it != msgs.end(); ++it)
    {
        std::cout << *it;
    }
}

void SemanticAnalyzer::addError(std::string errorMsg, int line)
{
    semanticErrors[line].push_back(errorMsg);
    numErrors++;
}

void SemanticAnalyzer::addWarning(std::string warning, int line){
    semanticWarnings[line].push_back(warning);
    numWarnings++;
}

int SemanticAnalyzer::getErrors(){
    return numErrors;
}

int SemanticAnalyzer::getWarnings(){
    return numWarnings;
}

SymbolTable SemanticAnalyzer::getST(){
    return st;
}

// pre-order traversal of the tree, handles all scope checking of this node
void SemanticAnalyzer::preOrderTraversal(ASTreeNode* root)
{
    if(root == NULL) return;
    preOrderCheck(root);

    for(int i = 0; i < 3; i++)
    {
        if(root->children[i] != NULL) preOrderTraversal(root->children[i]);
    }

    // if scope was created for this node and children, leave it
    scopeCleanup(root);

    // add sibling
    if(root->sibling != NULL) preOrderTraversal(root->sibling);

}

// look at a node, do scope creation, symbol checking, initialization setting
void SemanticAnalyzer::preOrderCheck(ASTreeNode* n)
{
    switch(n->nodekind){
        case DeclK:
            preCheckDecl(n);
            break;
        case StmtK:
            preCheckStmt(n);
            break;
        case ExpK:
            preCheckExp(n);
            break;
        default:
            break;
    }
}

// check if there is a scope associated with this node, leave if there is
void SemanticAnalyzer::scopeCleanup(ASTreeNode* n){
    if(n->nodekind == StmtK){ // leave for-loop and compound scopes
        StmtKind stmtk = n->subkind.stmt;

        if((stmtk == ForK || stmtk == WhileK || stmtk == CompoundK) && !strcmp(n->attrib.name, "skip") == 0){
            checkVarsUsed(st.getSymbols()); // before leaving, check if any symbols are not used
            st.leave();
        }

    }else if(n->nodekind == DeclK && n->subkind.decl == FuncK){ // leave function scope
        checkVarsUsed(st.getSymbols()); // before leaving, check if any symbols are not used
        st.leave();
    }

    if(currFunction == n){ // remove reference to this function since we are about to not be in it
        if(!currFunction->hasReturn && currFunction->type != Void){
          std::string warn = "WARNING("+std::to_string(n->linenum)+"): Expecting to return type "+typeToStr(currFunction->type)+" but function '"+std::string(currFunction->attrib.name)+"' has no return statement.\n";
          addWarning(warn, n->linenum);
        }
        currFunction = NULL;
    }
}

// transfer state flags and information from one node to another
// direction: from -> to
void SemanticAnalyzer::copyData(ASTreeNode* from, ASTreeNode* to){
    if(from == NULL || to == NULL){
        std::cout << "ERROR: argument to SemanticAnalyzer::copyData(ASTreeNode*, ASTreeNode*) is NULL.\n";
        return;
    }

    // copy state information
    to->isStatic = from->isStatic;
    to->isArray = from->isArray;
    to->isInitialized = from->isInitialized;
    to->isUsed = from->isUsed;
    to->hasReturn = from->hasReturn;
    to->type = from->type;

    // memory information
    to->varkind = from->varkind;
    to->size = from->size;
    to->loc = from->loc;
}

// iterate through map and throw error if any var is declared but not used
void SemanticAnalyzer::checkVarsUsed(std::map<std::string, void*> symbols){
    for(std::map<std::string, void*>::iterator it = symbols.begin(); it != symbols.end(); ++it){
        ASTreeNode* n = (ASTreeNode*)it->second;
        if(!n->isUsed){
            std::string name = std::string(n->attrib.name);
            std::string line = std::to_string(n->linenum);
            std::string warn;
            if(n->subkind.decl == VarK) warn = "WARNING("+line+"): The variable '"+name+"' seems not to be used.\n";
            else if(n->subkind.decl == ParamK) warn = "WARNING("+line+"): The parameter '"+name+"' seems not to be used.\n";
            else if(n->subkind.decl == FuncK && strcmp(n->attrib.name, "main") != 0) warn = "WARNING("+line+"): The function '"+name+"' seems not to be used.\n";
            else continue;
            addWarning(warn, n->linenum);
        }
    }
}

void SemanticAnalyzer::preCheckDecl(ASTreeNode* n)
{
    DeclKind deck = n->subkind.decl;

    if(deck == VarK){ // VarK: declare variable and set Global, Local, or LocalStatic
        declareVar(n);

    }else if(deck == FuncK){ // FuncK: set as a global, create scope, insert symbol in global
        currFunction = n; // save reference to this function so we can come back and compare return types
        declareFunction(n);

    }else{ // ParamK: set as parameter, add to scope
        n->varkind = Parameter;
        n->isInitialized = true; // parameters are initialized by default
        declareVar(n);
    }
}

void SemanticAnalyzer::preCheckStmt(ASTreeNode* n)
{
    StmtKind stmtk = n->subkind.stmt;

    if(stmtk == IfK){


    }else if(stmtk == ForK){
        // create for scope and ignore creation of following comp scope
        st.enter("for scope");
        if(n->children[2] != NULL && n->children[2]->subkind.stmt == CompoundK) strcpy(n->children[2]->attrib.name, "skip");

    }else if(stmtk == WhileK){
        // create while scope called while scope
        st.enter("while scope");
        if(n->children[1] != NULL && n->children[1]->subkind.stmt == CompoundK) n->children[1]->attrib.name = strdup("skip");

    }else if(stmtk == BreakK){
        std::string sName = st.getScopeName();
        if(sName != "while scope" && sName != "for scope"){
            std::string err = "ERROR("+std::to_string(n->linenum)+"): Cannot have a break statement outside of loop.\n";
            addError(err, n->linenum);
        }

    }else if(stmtk == CompoundK){
        // setup a new scope
        if(strcmp(n->attrib.name, "skip") != 0){ st.enter(n->attrib.name); }

    }else if(stmtk == ReturnK && currFunction != NULL){
        int line = n->linenum;
        std::string name = currFunction->attrib.name;
        // TODO check against currFunction to see if return type matches
        if(currFunction->type == Void && n->children[0] != NULL){
            std::string err = "ERROR("+std::to_string(line)+"): Function '"+name+"' at line "+std::to_string(currFunction->linenum)+" is expecting no return value, but return has a value.\n";
            addError(err, line);
        }else if(n->children[0] == NULL && currFunction->type != Void){
            std::string err = "ERROR("+std::to_string(line)+"): Function '"+name+"' at line "+std::to_string(currFunction->linenum)+" is expecting to return type "+typeToStr(currFunction->type)+" but return has no value.\n";
            addError(err, line);
        }
        n->type = currFunction->type; // store the expected return type for checkCallPost
        n->attrib.name = strdup(currFunction->attrib.name);
        currFunction->hasReturn = true;
    }
}

void SemanticAnalyzer::preCheckExp(ASTreeNode* n)
{
    OpKind expk = n->subkind.exp;
    std::string name = std::string(n->attrib.name);
    int line = n->linenum;

    if(expk == OpK){
        // check initialization of children
        checkIsInitialized(n->children[0], n->children[1], n->attrib.name);

    }else if(expk == IdK){
        // check against using function as var, use of undeclared var
        ASTreeNode* global = (ASTreeNode*)st.lookupGlobal(name);
        ASTreeNode* local = (ASTreeNode*)st.lookup(name);
        ASTreeNode* tmp = (ASTreeNode*)st.lookupGlobal(name);
        if(local != NULL /*&& local->isArray == n->isArray*/) tmp = local;
        else tmp = global;

        if(tmp != NULL && tmp->subkind.decl == FuncK){ // throw error for using function as variable
            std::string err = "ERROR("+std::to_string(line)+"): Cannot use function '"+name+"' as a variable.\n";
            addError(err, line);

        }else if(tmp != NULL){ // if global exists, get type
            copyData(tmp, n);
            /*n->type = tmp->type;
            n->isArray = tmp->isArray;
            n->isStatic = tmp->isStatic;*/
            tmp->isUsed = n->isUsed = true;

        }else{ // check most recent scope for previous declaration
            tmp = (ASTreeNode*)st.lookup(name);
            if(tmp == NULL){ // throw error for using undeclared var
                n->isInitialized = true; // if not declared, impossible to check if initialized
                //std::cout << "initialized " << n->attrib.name << " on line " << n->linenum << " to prevent cascading errors " <<  std::endl;
                std::string err = "ERROR("+std::to_string(line)+"): Symbol '"+name+"' is not declared.\n";
                addError(err, line);

                n->type = UndefinedType;
                n->isArray = false;
                n->isStatic = false;
                n->isUsed = true;
            }else{
                /*n->type = tmp->type;
                n->isArray = tmp->isArray;
                n->isStatic = tmp->isStatic;*/
                copyData(tmp, n);
                tmp->isUsed = n->isUsed = true;
                n->declaration = tmp;
            }
        }

        //if(!n->isInitialized) checkSideInitialized(n);

    }else if(expk == AssignK){ // initialize left side of expression
        // check rhs is initialized first, then initialize lhs
        if(n->children[1] != NULL) checkSideInitialized(n->children[1]);
        initializeLeftMostVar(n);

    }else if(expk == InitK){
        initializeVar(n);

    }else if(expk == CallK){
        checkCall(n, line);
    }

}

// check that all features of call are correct
void SemanticAnalyzer::checkCall(ASTreeNode* n, int line){
    std::string name = n->attrib.name;
    ASTreeNode* tmp = (ASTreeNode*)st.lookup(name); // check if declared
    if(tmp != NULL){ // check against using a simple variable
        n->type = tmp->type;
        n->declaration = tmp;
        if(tmp->nodekind == DeclK && tmp->subkind.decl != FuncK){
            std::string err = "ERROR("+std::to_string(line)+"): '"+name+"' is a simple variable and cannot be called.\n";
            addError(err, line);
        }else{
            copyData(tmp, n);
            tmp->isUsed = true;
        }


    }else{ // throw error because not declared
        std::string err = "ERROR("+std::to_string(line)+"): Symbol '"+name+"' is not declared.\n";
        addError(err, line);
    }

    // check that children are not uninitialized
    ASTreeNode* l = n->children[0];
    while(l != NULL){
        checkSideInitialized(l);
        l = l->sibling;
    }
}

// check for previous declaration of a symbol
bool SemanticAnalyzer::declareVar(ASTreeNode* n)
{
    std::string name = std::string(n->attrib.name);
    int line = n->linenum;

    bool success;
    if(n->isStatic) success = st.insertGlobal(name, n);
    else success = st.insert(name, n);

    if(!success) // symbol already in most recent scope
    {
        ASTreeNode* tmp = (ASTreeNode*)(st.lookup(name));
        std::string err = "ERROR(" + std::to_string(line) +"): Symbol '" + name + "' is already declared at line " + std::to_string(tmp->linenum) + ".\n";
        addError(err, line);
    }else{ // added successfully, now check if should be global, local, or localstatic
        ASTreeNode* global = (ASTreeNode*)st.lookupGlobal(name); // if this is not null, our variable ended up in global
        ASTreeNode* most_recent = (ASTreeNode*)st.lookupRecent(name);

        if(most_recent != NULL && most_recent != global){ // if there is a recent declaration that is not in global...
            if(most_recent->isStatic) n->varkind = LocalStatic;
            else n->varkind = Local;
        }else if(global != NULL){ // if there is a global declaration...
            n->varkind = Global;
            n->isInitialized = true;
        }
        if(n->children[0] != NULL){n->children[0]->varkind = Global;} // finally set the memory space for the initializer
        /*
        // WARNING incomplete check for match
        if(global != NULL && global->isArray == n->isArray){ // if in global and has same subkind, must be same
            printf("Setting %s on line %d to GLOBAL\n", n->attrib.name, n->linenum);
            n->varkind = Global;
            n->isInitialized = true; // we don't check if a global is initialized or used

            if(n->children[0] != NULL){n->children[0]->varkind = Global;}
        }else if(n->isStatic){
            //printf("Setting %s on line %d to LOCALSTATIC\n", n->attrib.name, n->linenum);
            n->varkind = LocalStatic;
            if(n->children[0] != NULL){n->children[0]->varkind = Global;}
        }else{
            //printf("Setting %s on line %d to LOCAL\n", n->attrib.name, n->linenum);
            n->varkind = Local;
            if(n->children[0] != NULL){n->children[0]->varkind = Global;}
        }
        */
    }

    return success;
}

// check function declaration and store information
void SemanticAnalyzer::declareFunction(ASTreeNode* n){
    // check number of params in declaration
    int paramC = 0;
    if(n->children[0] != NULL){
        ASTreeNode* l = n->children[0];
        while(l != NULL){
            n->params[paramC] = {l->type, l->isArray};
            paramC++;
            l = l->sibling;
        }
    }
    n->num_params = paramC; // store in node
    n->size = 2 + paramC;   // set the size of the function

    // check if this is a valid main function
    checkForMain(n);

    // create scope and check for previous declarations
    n->varkind = Global;
    st.enter(n->attrib.name); // create scope
    if(n->children[1] != NULL) n->children[1]->attrib.name = strdup("skip"); // don't create a second scope for the compound stmt
    bool success = st.insertGlobal(n->attrib.name, n); // function names cannot be used as variables anywhere in the program unless it is a call
    if(!success){
        ASTreeNode* tmp = (ASTreeNode*)st.lookupGlobal(n->attrib.name);
        std::string err = "ERROR(" + std::to_string(n->linenum) +"): Symbol '" + std::string(n->attrib.name) + "' is already declared at line " + std::to_string(tmp->linenum) + ".\n";
        addError(err, n->linenum);
    }
}

// set this as initialized
void SemanticAnalyzer::initializeVar(ASTreeNode* n){
    // initialize left side of expression and check against using uninitialized stuff on right
    ASTreeNode* cL = n->children[0]; // id on left side
    std::string lname = std::string(cL->attrib.name);
    ASTreeNode* cR = n->children[1]; // whatever is on the right side

    // check if rhs is initialized
    checkIsInitialized(cL, cR, n->attrib.name);

    // check if left side is an expression
    if(lname == "["){
        cL = cL->children[0];
        lname = cL->attrib.name;
    }

    // check if id is valid and set initialization
    ASTreeNode* tmp = (ASTreeNode*)st.lookup(lname);
    if(tmp != NULL){
        //std::cout << "initialized " << tmp->attrib.name << " on line " << tmp->linenum << std::endl;
        //std::cout << "initialized " << cL->attrib.name << " on line " << cL->linenum << std::endl;
        tmp->isInitialized = true;
        cL->isInitialized = true;
    }
}

// goes left until finds IdK and initializes that
void SemanticAnalyzer::initializeLeftMostVar(ASTreeNode* n){
    ASTreeNode* lhs = n->children[0];
    while(lhs != NULL && lhs->subkind.exp != IdK){
        lhs = lhs->children[0];
    }
    //std::cout << "initialized " << lhs->attrib.name << " on line " << lhs->linenum << std::endl;
    lhs->isInitialized = true;
    ASTreeNode* tmp = (ASTreeNode*)st.lookup(lhs->attrib.name);
    if(tmp != NULL){
        tmp->isInitialized = true;
    }
}

// throw warnings for variables that haven't been initialized yet
void SemanticAnalyzer::checkIsInitialized(ASTreeNode* lhs, ASTreeNode* rhs, std::string op){

    if(op == "and" || op == "or" || op == "=" || op == "><" || op == "<" || op == "<=" || op == ">" || op == ">="){
        checkSideInitialized(lhs);
        checkSideInitialized(rhs);
    }else if(op == ":=" || op == "+=" || op == "-=" || op == "*=" || op == "/="){
        checkSideInitialized(rhs);
    }else if(op == "+" || op == "-" || op == "*" || op == "/" || op == "%"){
        checkSideInitialized(lhs);
        checkSideInitialized(rhs);
    }else if(op == "[" || op == "sizeof" || op == "chsign" || op == "++" || op == "--"){
        checkSideInitialized(lhs);
    }
}

// check if all variables on this side of the tree are initialized
// use preorder traversal
void SemanticAnalyzer::checkSideInitialized(ASTreeNode* n){

    if(n->nodekind == ExpK && n->subkind.exp == AssignK) initializeLeftMostVar(n);

    for(int i = 2; i >= 0; i--){
        if(n->children[i] != NULL) checkSideInitialized(n->children[i]);
    }

    if(n->nodekind == ExpK && n->subkind.exp == IdK) checkVarInitialized(n);
    // don't check siblings, because expressions don't have them
}

// check if single variable is initialized
void SemanticAnalyzer::checkVarInitialized(ASTreeNode* n){
    //std::cout << "checking symbol " << n->attrib.name << " on line " << n->linenum << std::endl;
    if(strcmp(n->attrib.name, "[") == 0){
        n = n->children[0]; // shift to find id for indexing arrays
        n->isArray = true;
    }

    ASTreeNode* global = (ASTreeNode*)st.lookupGlobal(n->attrib.name);
    ASTreeNode* local = (ASTreeNode*)st.lookup(n->attrib.name);
    if(global != NULL && global->isArray == n->isArray){
        //std::cout << "\tSymbol " << n->attrib.name << " is global on line " << n->linenum << " so..." << std::endl;
        n->declaration = global;
        return; // is initialized by default
    }

    ASTreeNode* tmp = local;
    if(tmp != NULL && tmp->isStatic) n->isStatic = true;
    if(tmp != NULL && tmp->isInitialized){
        //std::cout << "\tset symbol " << n->attrib.name << " to initialized from local dec on line " << tmp->linenum << std::endl;
        //std::cout << "initialized " << n->attrib.name << " on line " << n->linenum << std::endl;
        n->isInitialized = true;
        n->declaration = tmp;
    }

    // conditions:
    //      1) var must be declared
    //      2) must be id expression
    //      3) must not be initialized
    //      4) must not be static
    if(tmp != NULL && n->nodekind == ExpK && !n->isInitialized && !n->isStatic){
        std::string line = std::to_string(n->linenum);
        std::string name = std::string(n->attrib.name);
        std::string warn = "WARNING("+line+"): Variable '"+name+"' may be uninitialized when used here.\n";
        addWarning(warn, n->linenum);

        // initialize so that we don't have cascading errors
        n->isInitialized = true;
        //std::cout << "initialized " << n->attrib.name << " on line " << n->linenum << " to prevent cascading errors" << std::endl;
        if(tmp != NULL) tmp->isInitialized = true;  // if symbol exists, make sure is initialized to prevent cascading errors
    }
}

// traverse tree in post order and add stuff to symbol table
void SemanticAnalyzer::postOrderTraversal(ASTreeNode* root)
{
    if(root == NULL) return;

    ExpType cTypes[] = {UndefinedType, UndefinedType, UndefinedType};
    for(int i = 0; i < 3; i++)
    {
        if(root->children[i] != NULL) postOrderTraversal(root->children[i]);
    }

    // add sibling
    if(root->sibling != NULL) postOrderTraversal(root->sibling);

    // check type against root type
    postCheck(root);
}

// split to check node based on nodekind
void SemanticAnalyzer::postCheck(ASTreeNode* n){
    NodeKind nk = n->nodekind;
    switch(nk){
        case StmtK:
        postCheckStmt(n);
        break;
        case ExpK:
        postCheckExp(n);
        break;
        default:
        break;
    }
}

// check statements for errors
void SemanticAnalyzer::postCheckStmt(ASTreeNode* n){
    StmtKind stmtk = n->subkind.stmt;
    std::string name = n->attrib.name;
    int line = n->linenum;

    if(stmtk == NullK){
        // check NullK
    }else if(stmtk == IfK){
        // check if test condition is an unindexed array
        // if the simple expression of the if statement is an IdK and an array, throw error
        ASTreeNode* simpleExp = n->children[0];
        if(isIDandArray(simpleExp)){
            std::string err = "ERROR("+std::to_string(line)+"): Cannot use array as test condition in if statement.\n";
            addError(err, line);
        }
        if(simpleExp->type != Boolean){
            std::string err = "ERROR("+std::to_string(line)+"): Expecting Boolean test condition in if statement but got type "+typeToStr(simpleExp->type)+".\n";
            addError(err, line);
        }

    }else if(stmtk == WhileK){
        // check for array used as test condition
        ASTreeNode* simpleExp = n->children[0];
        if(isIDandArray(simpleExp)){
            std::string err = "ERROR("+std::to_string(line)+"): Cannot use array as test condition in while statement.\n";
            addError(err, line);
        }

        if(simpleExp->type != Boolean){
            std::string err = "ERROR("+std::to_string(line)+"): Expecting Boolean test condition in while statement but got type "+typeToStr(simpleExp->type)+".\n";
            addError(err, line);
        }

    }else if(stmtk == ForK){
        // check ForK
    }else if(stmtk == CompoundK){
        // check CompoundK
    }else if(stmtk == ReturnK){
        // check against returning an array
        ASTreeNode* child = n->children[0];
        if(child != NULL && child->isArray){
            std::string err = "ERROR("+std::to_string(line)+"): Cannot return an array.\n";
            addError(err, line);
        }

        /*if(n->children[0] != NULL && n->type != n->children[0]->type){
            ASTreeNode* tmp = (ASTreeNode*)st.lookupGlobal(n->attrib.name);
            std::string err = "ERROR("+std::to_string(line)+"): Function '"+std::string(n->attrib.name)+"' at line "+std::to_string(tmp->linenum)+" is expecting to return type "+typeToStr(n->type)+" but returns type "+typeToStr(n->children[0]->type)+".\n";
            addError(err, line);
        }else if(n->children[0] != NULL){
          //std::cout << "line " << n->linenum << " expected type was " << typeToStr(n->type) << " and got type " << typeToStr(n->children[0]->type) << std::endl;
      }*/

    }else if(stmtk == BreakK){
        // check BreakK
    }else if(stmtk == RangeK){
        checkRange(n);
    }
}

void SemanticAnalyzer::checkRange(ASTreeNode* n){
    // check for array used in one of three range positions
    int line = n->linenum;
    ASTreeNode* from = n->children[0]; // from x
    ASTreeNode* to = n->children[1]; // to x
    ASTreeNode* by = n->children[2]; // by x

    // check for arrays
    if(isIDandArray(from)){
        std::string err = "ERROR("+std::to_string(line)+"): Cannot use array in position 1 in range of for statement.\n";
        addError(err, line);
    }
    if(isIDandArray(to)){
        std::string err = "ERROR("+std::to_string(line)+"): Cannot use array in position 2 in range of for statement.\n";
        addError(err, line);
    }
    if(isIDandArray(by)){
        std::string err = "ERROR("+std::to_string(line)+"): Cannot use array in position 3 in range of for statement.\n";
        addError(err, line);
    }

    ASTreeNode* c;
    for(int i = 0; i < 3; i++){
        c = n->children[i];
        if(c == NULL){
            //std::cout << "NULL took early out at i = " << i << " on line " << n->linenum <<  std::endl;
            continue; // early exit
        }else if(c->nodekind == ExpK && (c->subkind.exp == IdK || c->subkind.exp == CallK) && (ASTreeNode*)st.lookup(c->attrib.name) != NULL){
            //std::cout << "took early out at i = " << i << " on line " << n->linenum << std::endl;
            continue; // exit because not declared
        }

        if(i == 0){
            // check for non-integer types
            if(c->subkind.exp == AssignK){
                if(!c->children[1]->isInitialized){
                    std::string warn = "WARNING("+std::to_string(n->linenum)+"): Variable '"+std::string(c->children[1]->attrib.name)+"' may be uninitialized when used here.\n";
                    addWarning(warn, n->linenum);
                }else{
                    //std::cout << c->children[1] << " is already initialized on line " << c->linenum << std::endl;
                }

                if(c->children[1]->type != Integer){
                    std::string err = "ERROR("+std::to_string(line)+"): Expecting type int in position "+std::to_string(i+1)+" in range of for statement but got type "+typeToStr(c->type)+".\n";
                    addError(err, line);
                }
            }else if(c->type != Integer){
                // check is assign
                std::string err = "ERROR("+std::to_string(line)+"): Expecting type int in position "+std::to_string(i+1)+" in range of for statement but got type "+typeToStr(c->type)+".\n";
                addError(err, line);
            }else if(c->subkind.exp == IdK && !c->isInitialized){
                std::string warn = "WARNING("+std::to_string(n->linenum)+"): Variable '"+std::string(c->attrib.name)+"' may be uninitialized when used here.\n";
                addWarning(warn, n->linenum);
            }
        }else if(i == 1 && c->type != Integer){
            if(!c->isInitialized){
                std::string warn = "WARNING("+std::to_string(n->linenum)+"): Variable '"+std::string(c->attrib.name)+"' may be uninitialized when used here.\n";
                addWarning(warn, n->linenum);
            }else{
                //std::cout << c->children[1] << " is already initialized on line " << c->linenum << std::endl;
            }
            std::string err = "ERROR("+std::to_string(line)+"): Expecting type int in position "+std::to_string(i+1)+" in range of for statement but got type "+typeToStr(to->type)+".\n";
            addError(err, line);
        }else if(c != NULL && c->type != Integer){
            if(!c->isInitialized){
                std::string warn = "WARNING("+std::to_string(n->linenum)+"): Variable '"+std::string(c->attrib.name)+"' may be uninitialized when used here.\n";
                addWarning(warn, n->linenum);
            }else{
                //std::cout << c->children[1] << " is already initialized on line " << c->linenum << std::endl;
            }
            std::string err = "ERROR("+std::to_string(line)+"): Expecting type int in position "+std::to_string(i+1)+" in range of for statement but got type "+typeToStr(by->type)+".\n";
            addError(err, line);
        }
    }
}

// for a node, check if it is not null, ExpK, IdK, and Array
bool SemanticAnalyzer::isIDandArray(ASTreeNode* n){
    return (n != NULL && n->nodekind == ExpK && n->subkind.exp == IdK && n->isArray);
}

// check expressions for errors
void SemanticAnalyzer::postCheckExp(ASTreeNode* n){
    StmtKind expk = n->subkind.stmt;
    std::string name = n->attrib.name;
    int line = n->linenum;

    // "expected type"
    // this is the type that will be assigned to n at the end of this function
    ExpType exType = UndefinedType;

    switch(expk){
        case OpK:
            // check operation for errors
            exType = checkActionTypes(n, OpK);
            n->type = exType;
            break;
        case ConstantK:
            // don't think we need to do anything here yet
            break;
        case IdK:
        // get the type from the declaration
        {
            ASTreeNode* tmp = (ASTreeNode*)st.lookup(n->attrib.name);
            if(tmp != NULL) exType = tmp->type;
            break;
        }
        case InitK:
        {
            //std::cout << "CHECKING INITK on line " << n->linenum << std::endl;
            // TODO so check if right side is ConstantK
            if(n->children[0] != NULL && n->children[0]->subkind.exp != ConstantK){
                std::string err = "ERROR("+std::to_string(n->linenum)+"): Initializer for variable '"+std::string(n->attrib.name)+"' is not a constant expression.\n";
                addError(err, n->linenum);
            }else if(n->type != n->children[0]->type){
                std::string err = "ERROR("+std::to_string(n->linenum)+"): Initializer for variable '"+std::string(n->attrib.name)+"' of type "+typeToStr(n->type)+" is of type "+typeToStr(n->children[0]->type)+"\n";
                addError(err, n->linenum);
            }

            // TODO check if one of the sides is an array
            if(n->isArray != n->children[0]->isArray && n->children[0]->type != Char){
                std::string rhs = "";
                std::string lhs = "";
                if(n->isArray){ rhs = " not"; }
                else{ lhs = " not"; }
                std::string err = "ERROR("+std::to_string(n->linenum)+"): Initializer for variable '"+std::string(n->attrib.name)+"' requires both operands be arrays or not but variable is"+lhs+" an array and rhs is"+rhs+" an array.\n";
                addError(err, n->linenum);
            }

            break;
        }
        case AssignK:
            {
                // check types for assignops
                exType = checkActionTypes(n, AssignK);
                n->type = exType;
                n->isArray = n->children[0]->isArray;
                break;
            }
        case CallK:
            checkCallPost(n, line);
            break; // don't think we need to check anything here yet
        default:
            std::cout << "passed funky type to post check exp\n";
            break;
    }
}

// check a callk in post order traversal to check types
void SemanticAnalyzer::checkCallPost(ASTreeNode* n, int line){
    ASTreeNode* tmp = (ASTreeNode*)st.lookupGlobal(n->attrib.name);

    if(tmp != NULL){
        // check number of params
        //std::cout << "Line(" << line << ") declaration has " << tmp->num_params << " parameters vs " << n->num_params << " passed" << std::endl;
        if(tmp->num_params > n->num_params){
            std::string err = "ERROR("+std::to_string(line)+"): Too few parameters passed for function '"+std::string(n->attrib.name)+"' declared on line "+std::to_string(tmp->linenum)+".\n";
            addError(err, line);

        }else if(tmp->num_params < n->num_params){
            std::string err = "ERROR("+std::to_string(line)+"): Too many parameters passed for function '"+std::string(n->attrib.name)+"' declared on line "+std::to_string(tmp->linenum)+".\n";
            addError(err, line);
        }
        // if number of params matches -> check types
        ASTreeNode* l = n->children[0];
        for(int i = 0; i < tmp->num_params && l != NULL; i++){
            // check types
            if(tmp->params[i].first != l->type && tmp->params[i].first != UndefinedType && l->type != UndefinedType){
                std::string err = "ERROR("+std::to_string(line)+"): Expecting type "+typeToStr(tmp->params[i].first)+
                " in parameter "+std::to_string(i+1)+" of call to '"+std::string(n->attrib.name)+"' declared on line "+std::to_string(tmp->linenum)+
                " but got type "+typeToStr(l->type)+".\n";
                addError(err, line);
            }else{
                //std::cout << "skipped because " << typeToStr(tmp->params[i].first) << " and " << typeToStr(l->type) << std::endl;
            }
            // check for array where none was expected
            if(tmp->params[i].second != l->isArray){
                if(tmp->params[i].second){
                    std::string err = "ERROR("+std::to_string(line)+"): Expecting array in parameter "+std::to_string(i+1)+
                    " of call to '"+std::string(n->attrib.name)+"' declared on line "+std::to_string(tmp->linenum)+".\n";
                    addError(err, line);
                }else{
                    std::string err = "ERROR("+std::to_string(line)+"): Not expecting array in parameter "+std::to_string(i+1)+
                    " of call to '"+std::string(n->attrib.name)+"' declared on line "+std::to_string(tmp->linenum)+".\n";
                    addError(err, line);
                }
            }
            l = l->sibling;
        }
    }
}

// evaluate an OpK or AssignK expression, return the output type and throw errors if needed
ExpType SemanticAnalyzer::checkActionTypes(ASTreeNode* n, ExpKind expT){
    ExpType outputT = UndefinedType;
    std::string name = n->attrib.name;

    // check if this is a constant expression
    bool isConst = true;
    for(int i = 0; i < 3; i++){
      if(n->children[i] != NULL && n->children[i]->subkind.exp != ConstantK) isConst = false;
    }

    if(expT == OpK){
        // get the expected return types and compare to expression elements
        if(n->children[1] == NULL){
            // check unary op types
            outputT = checkUnaryOp(n, name);
            if(strcmp("?", n->attrib.name) == 0) isConst = false;
        }else{
            // check binary op types
            outputT = checkBinaryOp(n, name);
        }
    }else if(expT == AssignK){
        // get the types of children then return expected output
        if(name == "++" || name == "--") outputT = checkUnaryOp(n, name);
        else outputT = checkBinaryOp(n, name);
    }

    // set as constant expression at end of checks
    if(isConst){
        //std::cout << "setting " << n->attrib.name << " to constant" << std::endl;
        //n->subkind.exp = ConstantK;
    }

    return outputT;
}

// do type checking for binary expressions
ExpType SemanticAnalyzer::checkBinaryOp(ASTreeNode* n, std::string op){
    std::map<std::string, std::pair<ExpType, bool>> typeMap{
        {"+", {Integer, false}},       // lhs and rhs must be integers
        {"-", {Integer, false}},
        {"*", {Integer, false}},
        {"/", {Integer, false}},
        {"%", {Integer, false}},
        {"*=", {Integer, false}},
        {"/=", {Integer, false}},
        {"+=", {Integer, false}},
        {"-=", {Integer, false}},
        {"<", {Boolean, true}},       // requires booleans on both sides
        {">", {Boolean, true}},
        {"<=", {Boolean, true}},
        {">=", {Boolean, true}},
        {"or", {Boolean, false}},
        {"and", {Boolean, false}},
        {"=", {Equal, true}},         // only requires that both sides be same type
        {"><", {Equal, true}},
        {"[", {UndefinedType, false}}, // returns the type associated with first child, requires int in brackets
        {":=", {UndefinedType, true}} // this one depends on the lhs which must match rhs
    };

    ExpType outputT = typeMap[op].first;    // the type expected for both sides
    bool acceptsArr = typeMap[op].second;   // if both sides can be arrays or not
    std::string name = n->attrib.name;
    std::string lineStr = std::to_string(n->linenum);

    // reference left and right sides
    ASTreeNode* lhs = n->children[0];
    ASTreeNode* rhs = n->children[1];

    // throw error if operation cannot be done with array but at least one side is an array
    if((lhs->isArray || rhs->isArray) && !acceptsArr && op != "["){
        std::string err = "ERROR("+lineStr+"): The operation '"+op+"' does not work with arrays.\n";
        addError(err, n->linenum);
    }else{
        // TODO: the line below causes more errors than it fixes
        //n->isArray = true;
    }

    if(outputT == Integer){
        checkAgainstExpected(lhs->type, rhs->type, outputT, n->linenum, op);

    }else if(outputT == Boolean){
        if(op == "and" || op == "or") checkAgainstExpected(lhs->type, rhs->type, outputT, n->linenum, op);
        else checkAgainstEachother(lhs, rhs, n->linenum, op);

    }else if(outputT == Equal){
        outputT = Boolean;
        checkAgainstEachother(lhs, rhs, n->linenum, op);

    }else if(outputT == UndefinedType){
        outputT = lhs->type; // type of id
        if(op == "["){
            if(!lhs->isArray){ // check that lhs is an array
                //lhs->isArray = true; // prevent cascading errors
                std::string err = "ERROR("+lineStr+"): Cannot index nonarray '"+std::string(lhs->attrib.name)+"'.\n";
                addError(err, n->linenum);
            }

            // find type
            bool isFine = true;
            ASTreeNode* l = rhs;
            if(l->children[0] != NULL && strcmp(l->attrib.name, "[") == 0){
                l = l->children[0];
            }
            if(l->nodekind == ExpK && l->subkind.exp == IdK){
                isFine = l->declaration != NULL;
                //std::cout << "\tset id fine\n";
                //st.print(pointerPrintStr);
            }else{
                //std::cout << "\twasn't an ExpK "<< (l->nodekind == ExpK) << " or IdK " <<  (l->subkind.exp == IdK) << std::endl;
            }

            if(l->type != Integer && isFine){ // check that rhs is int
                std::string err = "ERROR("+lineStr+"): Array '"+std::string(lhs->attrib.name)+"' should be indexed by type int but got type "+typeToStr(rhs->type)+".\n";
                addError(err, n->linenum);
            }//else{std::cout << "isFine = " << isFine << ", missed index by type int on line " << n->linenum << " for symbol "<< l->attrib.name << std::endl;}
            if(rhs->isArray){ // check that rhs is not an unindexed array
                std::string err = "ERROR("+lineStr+"): Array index is the unindexed array '"+std::string(rhs->attrib.name)+"'.\n";
                addError(err, n->linenum);

            }
        }else if(op == ":="){
            outputT = checkAgainstEachother(lhs, rhs, n->linenum, op);
        }else{
            //std::cout << "fell through\n";
        }
    }

    //std::cout << "BINARY expression "<< op << " evaluates to " << typeToStr(outputT) << std::endl;
    return outputT;
}

// do type checking for unary expressions and throw errors for bad types
ExpType SemanticAnalyzer::checkUnaryOp(ASTreeNode* n, std::string op){
    std::map<std::string, ExpType> opsMap = {
        {"--", Integer},
        {"++", Integer},
        {"not", Boolean},
        {"sizeof", Integer},
        {"chsign", Integer},
        {"?", Integer}
    };
    ExpType outputT = opsMap[op];

    std::string lineStr = std::to_string(n->linenum);

    ASTreeNode* c = n->children[0];
    if(outputT != c->type && op != "sizeof"){ // throw error because type doesn't match
    std::string err = "ERROR("+lineStr+"): Unary '"+op+"' requires an operand of type "+typeToStr(outputT)+" but was given type "+typeToStr(c->type)+".\n";
    addError(err, n->linenum);
}

if(op == "sizeof"){ // right side should be array
    if(!c->isArray){
        // throw error because only works on arrays
        std::string err = "ERROR("+lineStr+"): The operation '"+op+"' only works with arrays.\n";
        addError(err, n->linenum);
    }
}else{
    if(c->isArray){
        // throw error because does not work on arrays
        std::string err = "ERROR("+lineStr+"): The operation '"+op+"' does not work with arrays.\n";
        addError(err, n->linenum);
    }
}
//std::cout << "UNARY expression evaluates to " << typeToStr(outputT) << std::endl;
return outputT;
}

// check that both sides match the expected type and throw errors if not
void SemanticAnalyzer::checkAgainstExpected(ExpType lhs, ExpType rhs, ExpType expected, int line, std::string op){
    if(lhs != expected && lhs != UndefinedType){
        // throw error for unexpected type on lhs
        std::string err = "ERROR("+std::to_string(line)+"): '"+op+"' requires operands of type "+typeToStr(expected)+" but lhs is of type "+typeToStr(lhs)+".\n";
        addError(err, line);
    }

    if(rhs != expected && rhs != UndefinedType){
        // throw error for unexpected type on rhs
        std::string err = "ERROR("+std::to_string(line)+"): '"+op+"' requires operands of type "+typeToStr(expected)+" but rhs is of type "+typeToStr(rhs)+".\n";
        addError(err, line);
    }
}

// check that both sides are the same type and throw error if not
ExpType SemanticAnalyzer::checkAgainstEachother(ASTreeNode* lhs, ASTreeNode* rhs, int line, std::string op){
    bool notVoid = (lhs->type != Void && rhs->type != Void);
    bool notUD = (lhs->type != UndefinedType && rhs->type != UndefinedType);

    if(lhs->type != rhs->type && notUD && notVoid){
        std::string err = "ERROR("+std::to_string(line)+"): '"+op+"' requires operands of the same type but lhs is type "+typeToStr(lhs->type)+" and rhs is type "+typeToStr(rhs->type)+".\n";
        addError(err, line);
    }

    if((lhs->isArray || rhs->isArray) && (lhs->isArray != rhs->isArray)){
        std::string lhs_str = lhs->isArray ? "" : " not";
        std::string rhs_str = rhs->isArray ? "" : " not";
        std::string err = "ERROR("+std::to_string(line)+"): '"+op+"' requires both operands be arrays or not but lhs is"+lhs_str+" an array and rhs is"+rhs_str+" an array.\n";
        addError(err, lhs->linenum);
    }
    return lhs->type;
}

ASTreeNode* SemanticAnalyzer::buildIOAST(){
    // build nodes
    ASTreeNode* input = createDeclNode(FuncK, Integer, "input", -1, NULL, NULL, NULL);
    input->isUsed = true;
    input->hasReturn = true;
    ASTreeNode* inputb = createDeclNode(FuncK, Boolean, "inputb", -1, NULL, NULL, NULL);
    inputb->isUsed = true;
    inputb->hasReturn = true;
    ASTreeNode* inputc = createDeclNode(FuncK, Char, "inputc", -1, NULL, NULL, NULL);
    inputc->isUsed = true;
    inputc->hasReturn = true;
    ASTreeNode* output = createDeclNode(FuncK, Void, "output", -1, NULL, NULL, NULL);
    output->isUsed = true;
    ASTreeNode* outputb = createDeclNode(FuncK, Void, "outputb", -1, NULL, NULL, NULL);
    outputb->isUsed = true;
    ASTreeNode* outputc = createDeclNode(FuncK, Void, "outputc", -1, NULL, NULL, NULL);
    outputc->isUsed = true;
    ASTreeNode* outnl = createDeclNode(FuncK, Void, "outnl", -1, NULL, NULL, NULL);
    outnl->isUsed = true;

    // create sibling structure
    input->sibling = inputb;
    inputb->sibling = inputc;
    inputc->sibling = output;
    output->sibling = outputb;
    outputb->sibling = outputc;
    outputc->sibling = outnl;

    // create children
    ASTreeNode* dummy1 = createDeclNode(ParamK, Integer, "*dummy*", -1, NULL, NULL, NULL);
    dummy1->isUsed = true;
    output->children[0] = dummy1;
    ASTreeNode* dummy2 = createDeclNode(ParamK, Boolean, "*dummy*", -1, NULL, NULL, NULL);
    dummy2->isUsed = true;
    outputb->children[0] = dummy2;
    ASTreeNode* dummy3 = createDeclNode(ParamK, Char, "*dummy*", -1, NULL, NULL, NULL);
    dummy3->isUsed = true;
    outputc->children[0] = dummy3;

    return input;
}

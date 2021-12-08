#include "memloc.h"

Memloc::Memloc(){
    init();
}

// init all values for the memory location tracker
void Memloc::init(){
    loc = 0;
    goffset = 0;
    foffset = 0;
}

/*
    Put variable on stack, add offset to node, and return new offset
    note: only use with simple variables, not arrays

    SIZE TABLE
    +------------------------------------------------------------+
    | array[n] = n + 1 | array[n]:init_val = n+1 + len(init_val) |
    | var = 1          | var:n = 1                               |
    +------------------------------------------------------------+
*/
int Memloc::enterVariable(ASTreeNode* n){
    //std::cout << "enterVariable() on line " << n->linenum << std::endl;
    if(n->isArray){
        if(n->children[0] != NULL) return enterArray(n, n->children[0]->size);
        return enterArray(n, 0);
    }

    if(isGlobal(n->varkind)){
        // insert into global symbol table
        st.insert(std::string(n->attrib.name), n);
        // allocate in global space
        n->loc = goffset; // assign to goffset then decrement
        goffset -= n->size;
        //printf("goffset = %d after entering %s on line %d\n", goffset, n->attrib.name, n->linenum);
        return goffset;
    }else{
        //printf("entering %s on line %d\n", n->attrib.name, n->linenum);
        // insert into local symbol table
        st.insert(std::string(n->attrib.name), n);
        // allocate in local space
        n->loc = foffset;
        foffset -= n->size;

        // increment compound size
        incrementCompound(1);
        return foffset;
    }
}

/*
    Calculates the location of a parameter on the stack. All parameters are:
        1. Local
        2. Size 1 because arrays are only passed by reference so there is no size stored
*/
int Memloc::enterParameter(ASTreeNode* n){
    //printf("set %s as Parameter\n", n->attrib.name);
    st.insert(n->attrib.name, n); // add parameter to symbol table
    n->varkind = Parameter;
    n->loc = foffset--;
    return foffset;
}

/*
    Set offset location of a new array on the stack. Accounts for initializer values in this function according to
    the table in the comment above enterVariable()

    init_size = 0 means there is no init
*/
int Memloc::enterArray(ASTreeNode* n, int init_size){
    if(init_size < 0) init_size = 0; // set to zero so it isn't a factor in location determination
    if(isGlobal(n->varkind)){
        // insert into global symbol table
        st.insert(std::string(n->attrib.name), n);
        if(init_size > 0){ n->children[0]->loc = goffset - 1;} // if there is an init, place it one below the size loc
        goffset -= init_size;   // move goffset down for initializer
        n->loc = (goffset - 1); // offset 1 to point below size
        goffset -= n->size;     // move goffset down for the array
        return goffset;
    }else{
        st.insert(std::string(n->attrib.name), n);
        if(init_size > 0){  // if there is an init, place it in next open goffset
            n->children[0]->loc = goffset-1;    // move goffset down one afterwards
            goffset -= init_size;               // offset by init size
        }
        n->loc = foffset-1; // offset 1 to point below size
        foffset -= n->size; // offset for size
        incrementCompound(n->size); // being local guarantees that there we are in a compound
        return foffset;
    }
}

/*
    When an Id is encountered, find it in the symbol table and retrieve its size and location
    information
*/
int Memloc::enterID(ASTreeNode* n){
    //st.print(pointerPrintStr);
    //printf("looking for %s on line %d\n", n->attrib.name, n->linenum);
    ASTreeNode* st_recent = (ASTreeNode*)st.lookupRecent(n->attrib.name);
    ASTreeNode* st_all = (ASTreeNode*)st.lookup(n->attrib.name);

    // copy information from the declaration
    if(st_recent != NULL){
        //printf("Using values from %s on line %d for ID %s on line %d\n", st_recent->attrib.name, st_recent->linenum, n->attrib.name, n->linenum);
        n->varkind = st_recent->varkind;
        n->loc = st_recent->loc;
        n->size = st_recent->size;
    }else if(st_all != NULL){
        //printf("Using values from %s on line %d for ID %s on line %d\n", st_all->attrib.name, st_all->linenum, n->attrib.name, n->linenum);
        n->varkind = st_all->varkind;
        n->loc = st_all->loc;
        n->size = st_all->size;
    }else{
            printf("ERROR: could not find id %s on line %d in symbol table using enterID\n", n->attrib.name, n->linenum);
            return -1;
    }

    return 0;
}

/*
    Constant character strings such as "xxx" are located in global memory. They should have a length that
    includes the NUL character
*/
int Memloc::enterConstString(ASTreeNode* n){
    //std::cout << "enterConstString() on line " << n->linenum << std::endl;
    if(n->loc != 1){
        //printf("    breaking early\n");
        //printf("    loc = %d\n", n->loc);
        //printf("    size = %d\n", n->size);
        //printf("    goffset = %d\n", goffset);
        return goffset;
    }
    //std::cout << "      setting const string\n";
    n->loc = goffset - 1;   // size stored at beginning of block
    goffset -= n->size; // include the size in the block offset
    /*printf("    loc = %d\n", n->loc);
    printf("    size = %d\n", n->size);
    printf("    goffset = %d\n", goffset);*/
    return goffset;
}

/*
    Functions are global, but all at location 1
        1. set foffset below function
        2. set n->location
        2. return new foffset
*/
int Memloc::enterFunction(ASTreeNode* n, int param_size){
    //printf("param_size = %d\n", param_size);
    foffset = -2; // reset local frame pointer to param start location
    n->loc = 0;   // all functions appear to be declared at location 0
    n->size = -1 * n->size; // function size is -2, plus (negative)size of params

    // add function scope to the symbol table
    //printf("Entering Scope %s via enterFunction() on line %d\n", n->attrib.name, n->linenum);
    st.enter(n->attrib.name);

    // create a dummy to hold incremented sizes and things
    ASTreeNode* tmp = new ASTreeNode;
    tmp->attrib.name = strdup("dummy");
    tmp->size = param_size;
    tmp->loc = 0;
    // add dummy and foffset to the stack of compound statements
    compoundStack.push_back(std::make_pair(tmp, foffset));

    // set compStmt ignore flag. since all funtions must be follwed by a compStmt, this will make sure parameters are entered into scope
    ignore_next_comp = true;
    comp_count++;

    return foffset;
}

// call when tree traversal leaves a function
void Memloc::leaveFunction(){
    //printf("LEAVING FUNCTION\n");
    foffset = 0; // reset local frame pointer
    st.leave(); // remove the function scope from the table

    // access saved memory location information
    comp_count--;
    std::pair<ASTreeNode*, int> tmp = compoundStack.back(); // get memory info from node on the stack
    compoundStack.pop_back(); // remove node from stack
    ASTreeNode* n = tmp.first;
    //printf("taking locations from %s\n", n->attrib.name);
    n->children[3]->size = (-1 * n->size) + tmp.second; // size is the original foffset + size of memory for variables in function
    n->children[3]->loc = 0;
}

/*
    Compound statements are interesting. Since their memory can be reclaimed on leaving the scope,
    variables inside are given a new offset starting at the foffset before entering the statement.

    1. All compund statements get a location of 0 since their memory is reclaimed on leaving the scope.
    2. Their size stores the location we return to when leaving the scope and the size of the variables
        inside the scope.

        example:
        loc -2: {   // foffset counts up starting at -2
                    int a; // loc -2
                    int b; // loc -3
                    int d[2]; // loc -5, size 3
                }
                // on exit foffset returns to -2, compound size was -2 (starting loc) + -5 (mem size inside)
                int a; // loc -2
*/
int Memloc::enterScope(ASTreeNode* n){
    // ignore_next_comp flags whether we have just entered a function, if so then the function scope is already created so don't create
    // a new scope for this compound
    if(ignore_next_comp){
        ignore_next_comp = !ignore_next_comp;
        return 0;
    }
    //printf("Entering Scope %s via enterScope() on line %d\n", n->attrib.name, n->linenum);
    // add compound into symbol table
    st.enter(std::string("scope"+std::to_string(comp_count)));
    comp_count++;
    // init memory/location
    n->loc = 0;
    n->size = 0;    // initially use size to count memory used
    // save this compound on our stack of compounds so that we can track size
    compoundStack.push_back(std::make_pair(n, foffset)); // save foffset to reset to when reclaiming memory

    return 1;
}

/*
    Leave a compound statement by setting the statement's size, reseting foffset, etc
*/
void Memloc::leaveScope(ASTreeNode* n){
    //printf("Left Scope %s which started on line %d\n", n->attrib.name, n->linenum);
    // leave the compound scope
    st.leave();
    comp_count--;
    std::pair<ASTreeNode*, int> tmp = compoundStack.back(); // get memory info from node on the stack
    compoundStack.pop_back(); // remove node from stack
    /*printf("    taking locations from %s\n", tmp.first->attrib.name);
    printf("        size = %d\n", tmp.first->size);
    printf("        loc = %d\n", tmp.first->loc);
    printf("        foffset = %d\n", tmp.second);*/
    n->size = (-1 * tmp.first->size) + tmp.second; // size is the original foffset + size of memory for variables in function
    n->loc = 0;
    // reset foffset
    foffset = tmp.second--;
}

/*
    Accesses the last compound statement on the stack and increases the size by some amount
*/
int Memloc::incrementCompound(int size){
    //printf("incrementing %s\n", n->attrib.name);
    ASTreeNode* n = compoundStack.back().first;
    n->size += size;
    return n->size;
}

// returns true if should be allocated in global space(Local, Parameter, Global, LocalStatic)
bool Memloc::isGlobal(VarKind vk){
    if(vk == Local || vk == Parameter){return false;}
    else if(vk == None){printf("ERROR varkind is None\n"); return false;}
    else{ return true;} // statics and globals
}

// checks if this node comes with a scope
bool Memloc::hasScope(ASTreeNode* n){
    switch(n->nodekind){
        case DeclK:
            //if(n->subkind.decl == FuncK) return true;
            //else return false;
            return false;
            break;
        case StmtK:
            if(n->subkind.stmt == CompoundK || n->subkind.stmt == ForK || n->subkind.stmt == WhileK) return true;
            else return false;
            break;
        case ExpK:
            return false;
            break;
        default:
            return false;
            break;
    }
}

// traverse the tree in pre-order traversal to carry out location initialization for nodes
int Memloc::traverseTree(ASTreeNode* root){
    if(root == NULL) return goffset;
    else resolveNode(root);

    for(int i = 0; i < 3; i++){
        traverseTree(root->children[i]);
    }

    // check if memory can be reclaimed by leaving a scope
    if(hasScope(root) && strcmp(root->attrib.name, "dummy") != 0){
        leaveScope(root);
    }

    traverseTree(root->sibling);
    return goffset;
}

// enter node onto the stack
void Memloc::resolveNode(ASTreeNode* n){
    switch(n->nodekind){
        case DeclK:
            if(n->subkind.decl == VarK){enterVariable(n);}
            else if(n->subkind.decl == FuncK){enterFunction(n, n->num_params);}
            else if(n->subkind.decl == ParamK){enterParameter(n);}
            break;
        case StmtK:
            if(n->subkind.stmt == CompoundK){enterScope(n);}
            else if(n->subkind.stmt == ForK){enterScope(n);}
            else if(n->subkind.stmt == WhileK){enterScope(n);}
            break;
        case ExpK:
            if(n->subkind.exp == ConstantK){enterConstString(n);}
            else if(n->subkind.exp == IdK){enterID(n);}
            break;
        case TerminalK:
            break;
    }
}

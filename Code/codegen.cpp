#include "codegen.h"

////////////////////////////////////////////////////////////////////////////////
//  TMInstruction                                                             //
////////////////////////////////////////////////////////////////////////////////
/*
 *  Construct a new TMInstruction
 */
TMInstruction::TMInstruction(int line, Instruction ins, int addr1, int addr2, int addr3, std::string comment){
    this->address = line;
    this->instruction = ins;
    this->addrs[0] = addr1;
    this->addrs[1] = addr2;
    this->addrs[2] = addr3;
    this->comment = comment;

    this->head = NULL;
    this->tail = NULL;

}

/*
 *  Construct a new LIT TMInstruction
 */
TMInstruction::TMInstruction(int line, Instruction ins, LType ltype, void* lit_ptr, std::string comment){
    this->address = line;
    this->instruction = ins;
    this->ltype = ltype;
    this->addrs[0] = 0; // these aren't used so default vals
    this->addrs[1] = 0;
    this->addrs[2] = 0;

    if(this->ltype == STR_LIT){
        this->literal.str_lit = (std::string*)lit_ptr;
    }else if(this->ltype == NUM_LIT){
        this->literal.int_lit = (int*)lit_ptr;
    }else{
        this->literal.bool_lit = (bool*)lit_ptr;
    }

    this->comment = comment;
    this->head = NULL;
    this->tail = NULL;

}

/*
 *  Create an instruction which prints only as a new comment line
 */
TMInstruction::TMInstruction(std::string comment){
    this->address = -1;
    this->instruction = NONE;
    this->addrs[0] = -1;
    this->addrs[1] = -1;
    this->addrs[2] = -1;
    this->comment = comment;
    this->head = NULL;
    this->tail = NULL;
}

/*
 *  Create a new TMInstruction with default/invalid values
 */
TMInstruction::TMInstruction(){
    this->address = -1;
    this->instruction = NONE;
    this->addrs[0] = -1;
    this->addrs[1] = -1;
    this->addrs[2] = -1;
    this->comment = "DEFAULT INSTRUCTION";
    this->head = NULL;
    this->tail = NULL;
}

/*
 *  Convert a TMInstruction to a string output
 */
std::string TMInstruction::to_string(){
    switch(this->instruction){
        case NONE:
            return "* " + this->comment;
        case LDC: // REGISTER TO MEMORY
        case LDA:
        case LD:
        case ST:
        case JNZ:
        case JZR:
        case JMP:
            {
                std::string tag = std::to_string(this->address) + ":\t" + instructionToStr();
                std::string addresses = std::to_string(addrs[0]) + ", " + std::to_string(addrs[1]) + "(" + std::to_string(addrs[2]) + ")";
                std::string lit;
                return tag + "\t" + addresses + " " + this->comment;
            }
        case LIT:
            {
                std::string tag = std::to_string(this->address) + ": " + instructionToStr();
                std::string lit;
                if(this->ltype == STR_LIT) lit = *(this->literal.str_lit);
                else if(this->ltype == NUM_LIT) lit = std::to_string(*(this->literal.int_lit));
                else if(this->ltype == BOOL_LIT) lit = std::to_string(*(this->literal.bool_lit));
                else lit = "ERROR: no lit value stored here";
                return tag + " " + lit + " " + this->comment;
            }
        default: // all others
            std::string tag = std::to_string(this->address) + ":\t" + instructionToStr();
            return tag + "\t" + std::to_string(this->addrs[0]) + ", " + std::to_string(this->addrs[1]) + ", " + std::to_string(this->addrs[1]) + " " + this->comment;
    }
}

void CodeGenerator::printCode(){
    std::cout   << "--------------------------------------------------------------\n"
                << "                          PROGRAM\n"
                << "--------------------------------------------------------------\n";

    TMInstruction* tmp = this->prog_head;
    while(tmp != NULL){
        std::cout << tmp->to_string() << std::endl;
        tmp = tmp->tail;
    }
}

/*
 *  Convert an Instruction enum member into a string
 */
std::string TMInstruction::instructionToStr(){
    switch(this->instruction){
        case NONE: // Defaultcase not a valid instruction
            return "NONE";
        case LDC:
            return "LDC";
        case LDA:
            return "LDA";
        case LD:
            return "LD";
        case ST:
            return "ST";
        case JNZ:
            return "JNZ";
        case JZR:
            return "JNZ";
        case JMP:           // REGISTER TO MEMORY INSTRUCTIONS (RA)
            return "JMP";
        case HALT:
            return "HALT";
        case NOP:
            return "NOP";
        case IN:
            return "IN";
        case INB:
            return "INB";
        case INC_tm:
            return "INC";
        case OUT:
            return "OUT";
        case OUTB:          // REGISTER ONLY INSTRUCTIONS (RO)
            return "OUTB";
        case OUTC:
            return "OUTC";
        case OUTNL:
            return "OUTNL";
        case ADD_tm:
            return "ADD";
        case SUB_tm:
            return "SUB";
        case MUL:
            return "MUL";
        case DIV_tm:
            return "DIV";
        case MOD_tm:
            return "MOD";
        case AND_tm:
            return "AND";
        case OR_tm:
            return "OR";
        case XOR:
            return "XOR";
        case NOT_tm:
            return "NOT";
        case NEG:
            return "NEG";
        case SWP:
            return "SWP";
        case RND:
            return "RND";
        case TLT:
            return "TLT";
        case TLE:
            return "TLE";
        case TEQ:
            return "TEQ";
        case TNE:
            return "TNE";
        case TGE:
            return "TGE";
        case TGT:
            return "TGT";
        case SLT:
            return "SLT";
        case SGT:           // TEST INSTRUCTIONS (RO)
            return "SGT";
        case MOV:
            return "MOV";
        case SET:
            return "SET";
        case CO:
            return "CO";
        case COA:
            return "COA";
        case LIT:           // BLOCK MEMORY TO MEMORY INSTRUCTIONS (RO)
            return "LIT";
    }
    return "ERROR: not an instruction";
}

/* TEST FUNCTIONS FOR TMINSTRUCTION and CODEGENERATOR LINKED LIST*/
void CodeGenerator::testCGEN_REMOVE(){
	std::cout << "------------------------------------------------------------\n"
			  << "TEST: removeLine()\n"
			  << "------------------------------------------------------------\n";

	CodeGenerator* cg = new CodeGenerator(NULL);
	TMInstruction* a = new TMInstruction(0, LDA, 0, 0, 0, "dummy line");
	TMInstruction* b = new TMInstruction();
	TMInstruction* c = new TMInstruction();

	cg->addLine(a);
	cg->addLine(b);
	cg->addLine(c);

	cg->printCode();

	cg->removeLine(a);
	cg->removeLine(b);

	cg->printCode();
	cg->removeLine(c);
	cg->printCode();

	std::cout << "-------------------------------------------------------------\n"
			  << "END TEST\n"
			  << "*\n*\n*\n";
}

void CodeGenerator::testCGEN_INSERT(){
	std::cout << "------------------------------------------------------------\n"
			  << "TEST: insertLine()\n"
			  << "-------------------------------------------------------------\n";

	CodeGenerator* cg = new CodeGenerator(NULL);
	TMInstruction* a = new TMInstruction(0, LDA, 0, 0, 0, "dummy line");
	std::string str("\"str literal\"");
	TMInstruction* b = new TMInstruction(2, LIT, STR_LIT, &str, "LIT instruction");
	TMInstruction* c = new TMInstruction(1, CO, 1, 3, 4, "CO instruction");
	TMInstruction* d = new TMInstruction(3, CO, 1, 3, 4, "CO instruction");

	cg->addLine(a);
	cg->addLine(b);
	cg->insertLine(c, a); // insert c after a

	cg->printCode();

	cg->insertLine(d, b);

	cg->printCode();

	std::cout << "-------------------------------------------------------------\n"
			  << "END TEST\n"
			  << "*\n*\n*\n";
}

////////////////////////////////////////////////////////////////////////////////
//  CODEGENERATOR                                                             //
////////////////////////////////////////////////////////////////////////////////
/*
 *  Constructs a CodeGenerator objectcase parses the output file namecase and creates a new
 *  *.tm file for the 3 address code to be output to
*/
CodeGenerator::CodeGenerator(ASTreeNode* root){
    // set defaults for doubly linked list
    this->prog_head = NULL;
    this->prog_tail = NULL;
    // create output testfile.tm file
    init();
    // attach pointer to code so we can use emitcode.h
    code = fopen("testfile.tm", "a");
    generateCode(root);
    generateInit();
    appendToFile();
}

/*
 *  Creates and opens a new output file and writes the header comments and C- I/O libraries into it. Also performs any
 *  useful setup of static code that can be done prior to tree traversal.
 */
void CodeGenerator::init(){
    std::ofstream tm("testfile.tm");
    this->tm_output = &tm;

    addLine("*************************************");
    addLine("C- Compiler version 1.0");
    addLine("Author: Garrett Wells");
    addLine("*************************************");
    addLine("");

    addLine("FUNCTION input");
    addLine(1, ST, 3, -1, 1, "Store return address");
    addLine(2, IN, 2,2,2, "Grab int input");
    addLine(3,LD,3,-1,1,"Load return address");
    addLine(4,LD,1,0,1,"Adjust");
    addLine(5,JMP,7,0,3, "Return");
    addLine("END FUNCTION input");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("END FUNCTION inputb");
    addLine(6, ST, 3,-1,1, "Store return address");
    addLine(7, INB, 2,2,2, "Grab bool input");
    addLine(8, LD, 3,-1,1, "Load return address");
    addLine(9, LD, 1,0,1, "Adjust fp");
    addLine(10, JMP, 7,0,3, "Return");
    addLine("END FUNCTION inputb");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION inputc");
    addLine(11, ST, 3,-1,1, "Store return address");    // INPU
    addLine(12, INC_tm, 2,2,2, "Grab char input");
    addLine(13, LD, 3,-1,1, "Load return address");
    addLine(14, LD, 1,0,1, "Adjust");
    addLine(15, JMP, 7,0,3, "Return");
    addLine("END FUNCTION inputc");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION output");
    addLine(16, ST, 3,-1,1, "Store return address");     // OUTPUT
    addLine(17, LD, 3,-2,1, "Load parameter");
    addLine(18, OUT, 3,3,3, "Output integer");
    addLine(19, LD, 3,-1,1, "Load return address");
    addLine(20, LD, 1,0,1, "Adjust");
    addLine(21, JMP, 7,0,3, "Return");
    addLine("END FUNCTION output");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outputb");
    addLine(22, ST, 3,-1,1, "Store return address");     // OUTPUTB
    addLine(23, LD, 3,-2,1, "Load parameter");
    addLine(24, OUTB, 3,3,3, "Output bool");
    addLine(25, LD, 3,-1,1, "Load return address");
    addLine(26, LD, 1,0,1, "Adjust");
    addLine(27, JMP, 7,0,3, "Return");
    addLine("END FUNCTION outputb");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outputc");
    addLine(28, ST, 3,-1,1, "Store return address");     // OUTPUTC
    addLine(29, LD, 3,-2,1, "Load parameter");
    addLine(30, OUTC, 3,3,3, "Output char");
    addLine(31, LD, 3,-1,1, "Load return address");
    addLine(32, LD, 1,0,1, "Adjust");
    addLine(33, JMP, 7,0,3, "Return");
    addLine("END FUNCTION outputc");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outnl");
    addLine(34, ST, 3,-1,1, "Store return address");     // OUTNL
    addLine(35, OUTNL, 3,3,3, "Output a newline");
    addLine(36, LD, 3,-1,1, "Load return address");
    addLine(37, LD, 1,0,1, "Adjust");
    addLine(38, JMP, 7,0,3, "Return");
    addLine("END FUNCTION outnl");

    // set start value for PC
    pmem = 39;
    // set offsets to invalid values
    goffset = 1;
    loffset = 1;
    toffset = 0;
}

/*
 *  Insert code to jump to load return, jump to main, and call halt
 */
void CodeGenerator::generateInit(){
    addLine(0, JMP, 7, main_ret_loc, 7, "JMP to init");

    // INIT
    addLine("INIT");
    addLine(pmem++, LDA, 3, 1, 7, "return address in ac");
    addLine(pmem++, ST, 1, 0, 1, "store old ");

    // INIT GLOBALS AND STATICS
    // TODO: init globals and statics

    addLine(pmem++, LDA, 3, 1, 7, "return address in ac");
    // Jump to main in pmem
    addLine(pmem++, JMP, 7, (main_loc - 1) - pmem, 7, "jump to main");
    addLine(pmem++, HALT, 0, 0, 0, "END EXECUTION");
    addLine("END INIT");
}

/*
 *  Writes a single line to a file, file returns to state it was in before
 *  writing so if it was closed it will be closed after appending
 */
void CodeGenerator::writeToFile(std::ofstream& file, std::string line){
    bool was_open = true;
    if(!file.is_open()) {file.open("testfile.tm", std::ofstream::app); was_open = false;}
    file << line << std::endl;
    if(!was_open) file.close();
}

/*
 *  Write all lines of code in LL to the output file in order of program memory address
 */
void CodeGenerator::appendToFile(){
    std::ofstream file("testfile.tm", std::ofstream::app);
    TMInstruction* tmp = this->prog_head;
    while(tmp != NULL){
        writeToFile(file, tmp->to_string());
        tmp = tmp->tail;
    }
    file.close();
}

// LL Functions ////////////////////////////////////////////////////////////////
/*
 *  Add a line to the end of the doubly linked list
 */
void CodeGenerator::addLine(TMInstruction* tm_ins){
    if(this->prog_head == NULL) this->prog_head = this->prog_tail = tm_ins;
    else{
        this->prog_tail->tail = tm_ins; // previous tail stores ref to this node as its tail
        tm_ins->head = this->prog_tail; // store ref to previous tail as above this line
        this->prog_tail = tm_ins;      // new ref to end of list points to this line
    }
}

void CodeGenerator::addLine(std::string comment){
    addLine(new TMInstruction(comment));
}

void CodeGenerator::addLine(int mem, Instruction ins, int addr, int addr1, int addr2, std::string comment){
    addLine(new TMInstruction(mem, ins, addr, addr1, addr2, comment));
}

void CodeGenerator::addLine(int mem, Instruction ins, LType ltype, void* cVal, std::string comment){
    addLine(new TMInstruction(mem, ins, ltype, cVal, comment));
}

/*
 *  Insert a new line after some other specified node
 */
void CodeGenerator::insertLine(TMInstruction* new_line, TMInstruction* target_line){
    if(target_line == NULL) {printf("ERROR: NULL ptr passed to insertLine()\n"); return;}
    else if(target_line == this->prog_head){

    }
    // init values for inserted line
    new_line->tail = target_line->tail;
    new_line->head = target_line;
    // setup the tail's references
    target_line->tail = new_line;
    if(target_line->tail != NULL){
        TMInstruction* tmp = target_line->tail;
        tmp->head = new_line;
    }
}

/*
 *  Removes a line from anywhere in the list and returns the pointer to it with all its references broken
 *  Also rearanges the pointers in the list to maintain valid structure
 */
TMInstruction* CodeGenerator::removeLine(TMInstruction* target){
    if(target == NULL){printf("ERROR: NULL ptr passed to removeLine()\n"); return NULL;}

    if(target != this->prog_head && target != this->prog_tail){
        target->head->tail = target->tail;
    }else{
        if(this->prog_head == target){
            this->prog_head = target->tail;
            // this->prog_head->head = NULL;
        }

        if(this->prog_tail == target){
            this->prog_tail = target->head;
            this->prog_tail->tail = NULL;
        }
    }


    target->head = NULL;
    target->tail = NULL;
    return target;
}

// Tree Traversal Functions ////////////////////////////////////////////////////
/*
 *  Traverse the tree for the first time and generate as much code for the tree
 *  as possible
 */
void CodeGenerator::generateCode(ASTreeNode* root){
    // if location is valid for this node, update loffset
    if(root->loc < 0) loffset = root->loc;
    // generate prep code for this node
    generateInitCode(root); // generate comments, header code, and as much reusable code as possible for this node type

    for(int i = 0; i < 3; i++){
        // TODO: generate prep code for ith child
        if(root->children[i] != NULL){
            generateCode(root->children[i]);
        }
    }

    // TODO: generate post proc code, like return from function
    generatePostProc(root);
    // reset any flags here
    if(isCallChild == true && root->nodekind == ExpK && root->subkind.exp == CallK) isCallChild = false; // reset the flag

    if(root->sibling != NULL) generateCode(root->sibling);
}

/*
 *  Generate code that does not change between programs such as the code for the I/O library,
 *  functions, compound statements, etc
 */
void CodeGenerator::generateInitCode(ASTreeNode* n){
    switch(n->nodekind){
        case DeclK:
            if(n->subkind.decl == FuncK) generateFunc(n);
            else if(n->subkind.decl == VarK) generateVar(n);
            else if(n->subkind.decl == ParamK){ printf("generating for param\n"); generateParam(n);}
        case StmtK:
            switch(n->subkind.stmt){
                case NullK:
                    return;

                case IfK:
                    return;

                case WhileK:
                    return;

                case ForK:
                    return;

                case CompoundK:
                    printf("generating for compound\n");
                    generateCompound(n);
                    return;

                case ReturnK:
                    generateReturn(n);
                    return;
                case BreakK:
                    return;
                case RangeK:
                    return;
            }
        case ExpK:
            switch(n->subkind.exp){
                case ConstantK:
                    //TODO: RESUME and add parameterize here
                    if(isCallChild) addLine("PARAM");
                    // load the constant
                    if(n->type == Integer) addLine(pmem++, LDC, 3, atof(n->attrib.name), 0, "load constant");
                    else if(n->type == Boolean) addLine(pmem++, LDC, 3, strcmp(n->attrib.name, "true") == 0, 0, "Load Boolean constant");
                    else if(n->type == Char) addLine(pmem++, LDC, 3, *(n->attrib.name), 0, "load const char");
                    else if(n->type == CharInt) addLine(pmem++, LDC, 3, *(n->attrib.name), 0, "load const string");
                    if(isCallChild){
                        // generate the ST command
                        addLine(pmem++, ST, 3, --toffset, 1, "Push parameter"); // TODO: should be loc + current offset
                        addLine("END PARAM");
                    }
                    break;
                case CallK:
                    generateCall(n);
                    isCallChild = true;
                    break;
            }
    }
}

void CodeGenerator::generateFunc(ASTreeNode* n){
    std::ofstream file;
    addLine("\n* ** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION " + std::string(n->attrib.name));
    loffset = -2 - n->num_params;
    addLine("TOFF dec: "+ std::to_string(loffset));
    addLine(pmem++, ST, 3, -1, 1, "Store return address");
    // if this is the main function, store it's location so we can go back
    if(strcmp(n->attrib.name, "main") == 0 && n->num_params == 0) main_loc = pmem;
}

void CodeGenerator::generateVar(ASTreeNode* n){
}

// code for params in a function definition
void CodeGenerator::generateParam(ASTreeNode* n){
    addLine(pmem++, LD, 3, n->loc, 1, "Load param " + std::string(n->attrib.name));
}

// generate the code for arguments passed to a function call
void CodeGenerator::generateArg(ASTreeNode* n, int i){
    addLine("PARAM" + atof(i));
    // load the constant
    if(n->type == Integer) addLine(pmem++, LDC, 3, atof(n->attrib.name), 0, "load constant");
    else if(n->type == Boolean) addLine(pmem++, LDC, 3, strcmp(n->attrib.name, "true") == 0, 0, "Load Boolean constant");
    else if(n->type == Char) addLine(pmem++, LDC, 3, *(n->attrib.name), 0, "load const char");
    else if(n->type == CharInt) addLine(pmem++, LDC, 3, *(n->attrib.name), 0, "load const string");

    // generate the ST command
    addLine(pmem++, ST, 3, --toffset, 1, "Push parameter"); // TODO: should be loc + current offset
    addLine("END PARAM");

    if(n->sibling != NULL) generateArg(n->sibling);
    else{isCallChild = false;} // stop generating code for the params
}

void CodeGenerator::generateCompound(ASTreeNode* n){
    addLine("Compound");
}

void CodeGenerator::generateReturn(ASTreeNode* n){
    if(n->children[0] == NULL){
        // generate default
        addLine(pmem++, LD, 3, -1, 1, "recover old pc");

        addLine(pmem++, LD, 1, 0, 1, "pop the frame");

        addLine(pmem++, JMP, 7, 0, 3, "Return");
    }
}

void CodeGenerator::generateCall(ASTreeNode* n){
    addLine("CALLING " + std::string(n->attrib.name));
    // set toffset relative to loffset, then all decrements for params are done to toffset
    toffset = loffset;
    // Save the frame pointer(loffset) in data memory
    addLine("TOFF dec: " + std::to_string(toffset - 1));
    addLine(pmem++, ST, 1, loffset, 1, "store frame pointer in dmem");
}

void CodeGenerator::generatePostProc(ASTreeNode* n){
    if(n->nodekind == DeclK){
        if(n->subkind.decl == FuncK){
            genFunCleanup(n);
        }
    }else if(n->nodekind == StmtK){
        if(n->subkind.stmt == CompoundK){
            addLine("END COMPOUND");
        }else if(n->subkind.stmt == ReturnK){
            // A default return is included for main in case there is no return statement
            if(strcmp(n->attrib.name, "main") == 0 && n->num_params == 0){
                genReturnCleanup(n);
            }
        }
    }else if(n->nodekind == ExpK){
        if(n->subkind.exp == CallK) genCallCleanup(n);
    }
}

/*
 *  Adds the code to return from a call
 */
void CodeGenerator::genFunCleanup(ASTreeNode* n){
    // TODO: this needs to be changed to return an actual meaningful value
    addLine(pmem++, LDA, 2, 0, 6, "load function return with a value in register xxx");
    addLine(pmem++, LD, 3, -1, 1, "recover old pc");
    addLine(pmem++, LD, 1, 0, 1, "pop the frame");
    addLine(pmem++, JMP, 7, 0, 3, "jump to old pc");
    addLine("END FUNCTION " + std::string(n->attrib.name));
    addLine("");
}

void CodeGenerator::genReturnCleanup(ASTreeNode* n){
    TMInstruction* new_ins;
    addLine("Add default return in case there is no return statement");
    addLine(pmem++, LDC, 2, 0, 0, "save return value");
    addLine(pmem++, LD, 3, -1, 1, "recover old pc");
    addLine(pmem++, LD, 1, 0, 1, "pop the frame");
    addLine(pmem++, JMP, 7, 0, 3, "Return");
}

void CodeGenerator::genCallCleanup(ASTreeNode* n){
    // load the parameters using the form below
    addLine(pmem++, LDA, 1, loffset, 1, "Ghost frame becomes new active frame");
    addLine(pmem++, LDA, 3, 1, 7, "Return address in ac");
    addLine(pmem++, JMP, 7, -27, 7, "Call " + std::string(n->attrib.name));
    addLine(pmem++, LDA, 3,0,2, "Save result in ac");
    addLine("END CALL " + std::string(n->attrib.name));
}

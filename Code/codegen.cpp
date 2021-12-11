#include "codegen.h"
using namespace std;

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
            return tag + "\t" + std::to_string(this->addrs[0]) + ", " + std::to_string(this->addrs[1]) + ", " + std::to_string(this->addrs[2]) + " " + this->comment;
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
    goffset = 1;
    genCode(root, 0, true);
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
    pmem = 1;
    functionMap["input"] = addLine(ST, 3, -1, 1, "Store return address");
    addLine(IN, 2,2,2, "Grab int input");
    addLine(LD,3,-1,1,"Load return address");
    addLine(LD,1,0,1,"Adjust");
    addLine(JMP,7,0,3, "Return");
    addLine("END FUNCTION input");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION output");
    functionMap["output"] = addLine(ST, 3,-1,1, "Store return address");     // OUTPUT
    addLine(LD, 3,-2,1, "Load parameter");
    addLine(OUT, 3,3,3, "Output integer");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION output");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("END FUNCTION inputb");
    functionMap["inputb"] = addLine(ST, 3,-1,1, "Store return address");
    addLine(INB, 2,2,2, "Grab bool input");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust fp");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION inputb");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outputb");
    functionMap["outputb"] = addLine(ST, 3,-1,1, "Store return address");     // OUTPUTB
    addLine(LD, 3,-2,1, "Load parameter");
    addLine(OUTB, 3,3,3, "Output bool");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION outputb");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION inputc");
    functionMap["inputc"] = addLine(ST, 3,-1,1, "Store return address");    // INPU
    addLine(INC_tm, 2,2,2, "Grab char input");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION inputc");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outputc");
    functionMap["outputc"] = addLine(ST, 3,-1,1, "Store return address");     // OUTPUTC
    addLine(LD, 3,-2,1, "Load parameter");
    addLine(OUTC, 3,3,3, "Output char");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION outputc");
    addLine("");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
    addLine("FUNCTION outnl");
    functionMap["outnl"] = addLine(ST, 3,-1,1, "Store return address");     // OUTNL
    addLine(OUTNL, 3,3,3, "Output a newline");
    addLine(LD, 3,-1,1, "Load return address");
    addLine(LD, 1,0,1, "Adjust");
    addLine(JMP, 7,0,3, "Return");
    addLine("END FUNCTION outnl");
    addLine("** ** ** ** ** ** ** ** ** ** ** **");
}

/*
 *  Insert code to jump to load return, jump to main, and call halt
 */
void CodeGenerator::generateInit(){
    int tmp = pmem;
    pmem = 0;
    addLine(JMP, 7, main_ret_loc, 7, "JMP to init");
    pmem = tmp;
    // INIT
    addLine("INIT");
    // set frame at end of globals
    addLine(LDA, 1, --goffset, 0, "set first frame at end of globals");
    addLine(ST, 1, 0, 1, "store old ");

    addLine("INIT GLOBALS AND STATICS");
    // TODO: init globals and statics
    addLine("END INIT GLOBALS AND STATICS");

    addLine(LDA, 3, 1, 7, "return address in ac");
    // Jump to main in pmem
    addLine(JMP, 7, (main_loc) - pmem - 1, 7, "jump to main");
    addLine(HALT, 0, 0, 0, "END EXECUTION");
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

TMInstruction* CodeGenerator::addLine(std::string comment){
    TMInstruction* ins = new TMInstruction(comment);
    addLine(ins);
    return ins;
}

TMInstruction* CodeGenerator::addLine(Instruction ins, int addr, int addr1, int addr2, std::string comment){
    TMInstruction* instruct = new TMInstruction(pmem++, ins, addr, addr1, addr2, comment);
    addLine(instruct);
    return instruct;
}

TMInstruction* CodeGenerator::addLine(Instruction ins, LType ltype, void* cVal, std::string comment){
    TMInstruction* instruct = new TMInstruction(pmem++, ins, ltype, cVal, comment);
    addLine(instruct);
    return instruct;
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

    // update PC for all nodes to make sure they are in order
    int pc = new_line->head->address;
    TMInstruction* tmp = new_line;
    while(tmp != NULL){
        tmp->address = pc++;
    }
    pmem = pc;
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

void CodeGenerator::genCode(ASTreeNode* n, int offset, bool genSibling){
    if(n == NULL) return; // protect against disaster
    cout << "gen code for " << n->attrib.name << endl;
    int reset_pt;
    switch(n->nodekind){
        case DeclK:
            switch(n->subkind.decl){
                case FuncK:
                    offset = -2 - n->num_params;
                    if(n->num_params == 0 && !strcmp(n->attrib.name, "main")) main_loc = pmem;
                    addLine("FUNCTION " + string(n->attrib.name));
                    offset -= n->num_params;
                    addLine("TOFF set: " + to_string(offset));
                    functionMap[n->attrib.name] = addLine(ST, 3, -1, 1, "Store return address");
                    genCode(n->children[1], offset, true); // generate compound
                    addLine("Add standard closing in case there is no return statement");
                    addLine(LDC, 2, 0, 6, "Set return value 0");
                    genReturn(n);
                    break;
                case ParamK:
                    break;
                case VarK:
                    if(n->varkind == Global){
                        goffset = n->loc;
                    }
                    break;
            }
            break;
        case StmtK:
            switch(n->subkind.stmt){
                case CompoundK:
                    reset_pt = offset; // store toff for when we leave it again
                    offset = n->size;
                    addLine("COMPOUND");
                    addLine("TOFF set: " + to_string(offset));
                    addLine("Compound Body");
                    genCode(n->children[1], offset, true);
                    offset = reset_pt;
                    addLine("TOFF set: " + to_string(offset));
                    addLine("END COMPOUND");
                    break;
                case ReturnK:
                    addLine("RETURN");
                    genCode(n->children[0], offset, true);
                    addLine(LDA, 2, 0, 3, "Copy result to return register");
                    addLine(LD, 3, -1, 1, "Load return address");
                    addLine(LD, 1, 0, 1, "Adjust fp");
                    addLine(JMP, 7, 0, 3, "Return");
                    addLine("END RETURN");
                    genSibling = false;
                    break;
            }
            break;
        case ExpK:
            switch(n->subkind.exp){
                case OpK:
                    {
                        string op = string(n->attrib.name);
                        cout << "gen lhs" << endl;
                        genCode(n->children[0], offset, true);
                        // UNARY OPs
                        if(op == "chsign") addLine(NEG, 3, 3, 3, "Op unary -");
                        else if(op == "sizeof") addLine("sizeof here");
                        else if(op == "?") addLine(RND, 3, 3, 6, "Op ?");
                        else if(op == "not"){
                            addLine(LDC, 4, 1, 6, "Load 1");
                            addLine(XOR, 3, 3, 4, "Op XOR to get logical not");
                        }else{ // BINARY OPs
                            // gen binary
                            addLine(ST, 3, offset, 1, "Push left side"); // store lhs
                            addLine("TOFF dec: " + to_string(--offset));
                            cout << "gen rhs" << endl;
                            genCode(n->children[1], offset, true); // gen rhs
                            addLine("TOFF inc: " + to_string(++offset));
                            addLine(LD, 4, offset, 1, "Pop left into ac1");
                            //  mathematical operations
                            if(op == "*")       addLine(MUL, 3, 4, 3, "Op *");
                            else if(op == "+")  addLine(ADD_tm, 3, 3, 4, "Op +");
                            else if(op == "-")  addLine(SUB_tm, 3, 4, 3, "Op -");
                            else if(op == "/")  addLine(DIV_tm, 3, 4, 3, "Op /");
                            else if(op == "%")  addLine(MOD_tm, 3, 4, 3, "Op %");
                            //  boolean operations
                            else if(op == "and")    addLine(AND_tm, 3,4,3, "Op AND");
                            else if(op == "or")     addLine(OR_tm, 3,4,3, "Op OR");
                            else if(op == "=")      addLine(TEQ, 3, 4, 3, "Op =");
                            else if(op == "<")      addLine(TLT, 3, 4, 3, "Op <");
                            else if(op == ">")      addLine(TGT, 3, 4, 3, "Op >");
                            else if(op == ">=")     addLine(TGE, 3,4,3, "Op >=");
                            else if(op == "<=")     addLine(TLE, 3,4,3, "Op <=");
                            else if(op == "><")     addLine(TNE, 3,4,3, "Op ><");
                            else if(op == "["){
                                addLine(SUB_tm, 3, 4, 3, "Compute offset of value");
                                addLine(LD, 3, 0, 3, "get value");
                            }
                        }
                        break;
                    }
                case ConstantK:
                    loadConst(n);
                    break;

                case IdK:
                    genId(n);
                    break;

                case CallK:
                    reset_pt = offset;
                    addLine("CALL " + string(n->attrib.name));
                    addLine(ST, 1, offset, 1, "Store fp in ghost frame for output");
                    addLine("TOFF dec: " + to_string(--offset));
                    // generate code for arguments
                    genArgs(n->children[0], --offset, 0);
                    addLine("Param end " + string(n->attrib.name));
                    offset = reset_pt;
                    addLine(LDA, 1, offset, 1, "Ghost frame becomes new active frame");
                    addLine(LDA, 3, 1, 7, "Return address in ac");
                    addLine(JMP, 7, functionMap[n->attrib.name]->address - pmem - 1, 7, "CALL " + string(n->attrib.name));
                    addLine(LDA, 3, 0, 2, "Save the result in ac");
                    addLine("Call end " + string(n->attrib.name));
                    addLine("TOFF set: " + to_string(offset));
                    break;
                case AssignK:
                    string op = n->attrib.name;
                    if(op == "+="){
                        genOpAssign(n, op, offset, "Op +=");
                        break;
                    }else if(op == "-="){
                        genOpAssign(n, op, offset, "Op -=");
                        break;
                    }else if(op == "*="){
                        genOpAssign(n, op, offset, "Op *=");
                        break;
                    }else if(op == "/="){
                        genOpAssign(n, op, offset, "Op /=");
                        break;
                    }

                    addLine("EXPRESSION");
                    // provide for array element assignment
                    if(!strcmp(n->children[0]->attrib.name, "[")){
                        genCode(n->children[0]->children[1], offset-1, true);
                        addLine(ST, 3, offset, 1, "Push index");
                        addLine("TOFF dec: " + to_string(--offset));
                        genCode(n->children[1], offset, true);
                        addLine("TOFF inc: " + to_string(++offset));
                        addLine(LD, 4, offset, 1, "Pop index");
                        ASTreeNode* id = n->children[0]->children[0];
                        if(id->varkind == Parameter){
                            addLine(LD, 5, id->loc, 1, "(EXP PARAM) Load address of base of array " + string(id->attrib.name));
                        }else{
                            addLine(LDA, 5, id->loc, 0, "(EXP NONPARAM) Load address of base of array " + string(id->attrib.name));
                        }

                        addLine(SUB_tm, 5, 5, 4, "Compute offset of value");
                        addLine(ST, 3, 0, 5, "Store variable " + string(id->attrib.name));
                    }else if(n->children[0]->type == Char && n->children[0]->isArray){
                        genCode(n->children[1], offset-1, true);
                        addLine(LDA, 4, n->children[0]->loc, 1, "address of lhs");
                        addLine(LD, 5, 1, 3, "size of rhs");
                        addLine(LD, 6, 1, 4, "size of lhs");
                        addLine(SWP, 5, 6, 6, "pick smallest size");
                        addLine(MOV, 4, 3, 5, "array op =");
                    }else{
                        genCode(n->children[1], offset, true);
                        addLine(ST, 3, n->children[0]->loc, n->children[0]->varkind == Local || n->children[0]->varkind == Parameter, "Store variable " + string(n->children[0]->attrib.name));
                    }
                    break;
            }
            break;
    }

    if(genSibling){genCode(n->sibling, offset, true);}
}

void CodeGenerator::genReturn(ASTreeNode* n){
    addLine(LD, 3, -1, 1, "Adjust fp");
    addLine(LD, 1, 0, 1, "Return");
    if(strcmp(n->attrib.name, "main") == 0 && n->num_params == 0) main_ret_loc = pmem;
    addLine(JMP, 7, 0, 3, "jump to old pc");
    addLine("END FUNCTION " + std::string(n->attrib.name));
    addLine("");

}

/*
 * Generate the instructions for loading args to function calls
 */
void CodeGenerator::genArgs(ASTreeNode* n, int toff, int arg_num){
    addLine("TOFF dec: " + to_string(toff));
    if(n == NULL) return;
    addLine("Param " + to_string(arg_num + 1));
    genCode(n, toff, false);
    addLine(ST, 3, toff, 1, "Push parameter");
    addLine("Param end");

    genArgs(n->sibling, toff - 1, arg_num++);
}

/*
 *  Generate code for IdK expressions
 */
void CodeGenerator::genId(ASTreeNode* n){
    if(n->varkind == Global){   // Global
        if(n->isArray){
            addLine(LDA, 3, n->loc, 0, "(GLOBAL)Load address of base of array " + string(n->attrib.name));
        }else{
            addLine(LD, 3, n->loc, 0, "Load variable " + string(n->attrib.name));
        }
    }else{                      // Local
        if(n->isArray){
            // tricky business
            if(n->varkind == Parameter){
                // load params indirectly...
                addLine(LD, 3, n->loc, 1, "(PARAM)Load address of base of array " + string(n->attrib.name));
            }else {
                // load non-params directly...
                addLine(LDA, 3, n->loc, n->varkind == Local, "(NONPARAM)Load address of base of array " + string(n->attrib.name));
            }
        }else{
            addLine(LD, 3, n->loc, n->varkind == Local || n->varkind == Parameter, "retrieve local variable " + string(n->attrib.name));
        }
    }
}

/*
 *  Generate code for assignment operations ADDASS, SUBASS, MULASS, DIVASS.
 */
void CodeGenerator::genOpAssign(ASTreeNode* n, string op, int toff, string comment){
    addLine("EXPRESSION");
    if(!strcmp(n->children[0]->attrib.name, "[")){
        genCode(n->children[0], toff, true);
        addLine(ST, 3, toff, 1, "Push index");
        addLine("TOFF dec: " + to_string(--toff));
        genCode(n->children[1], toff, true);
        addLine("TOFF inc: " + to_string(++toff));
        addLine(LD, 4, toff, 1, "Pop index");
        ASTreeNode* id = n->children[0]->children[0];
        if(id->varkind == Parameter){
            addLine(LD, 5, id->loc, id->varkind == Local || id->varkind == Parameter, "(LOCAL) Load address of base of array " + string(id->attrib.name));
        }else{
            addLine(LDA, 5, id->loc, id->varkind == Local || id->varkind == Parameter, "Load address of base of array " + string(id->attrib.name));
        }
        addLine(SUB_tm, 5,5,4, "Compute offset of value");
        addLine(LD, 4,0,5, "Load lhs variable " + string(id->attrib.name));
        if(op == "+="){
            addLine(ADD_tm, 3,4,3, comment);
        }else if(op == "-="){
            addLine(SUB_tm, 3,4,3, comment);
        }else if(op == "*="){
            addLine(MUL, 3,4,3, comment);
        }else if(op == "/="){
            addLine(DIV_tm, 3,4,3, comment);
        }
        addLine(ST, 3, 0, 5, "Store variable " + string(id->attrib.name));
    }else{
        genCode(n->children[1], toff-1, true);
        addLine(LD, 4, n->children[0]->loc, n->children[0]->varkind != Global, "Load lhs variable " + string(n->children[0]->attrib.name));
        if(op == "+="){
            addLine(ADD_tm, 3,4,3, comment);
        }else if(op == "-="){
            addLine(SUB_tm, 3,4,3, comment);
        }else if(op == "*="){
            addLine(MUL, 3,4,3, comment);
        }else if(op == "/="){
            addLine(DIV_tm, 3,4,3, comment);
        }
        addLine(ST, 3, n->children[0]->loc, 0, "Store variable " + string(n->children[0]->attrib.name));
    }
}

/*
 *  Helper function for loading a constant into memory
 */
void CodeGenerator::loadConst(ASTreeNode* n){
    switch(n->type){
        case Integer:
            addLine(LDC, 3,atoi(n->attrib.name), 6, "Load integer constant");
            break;
        case Boolean:
            addLine(LDC, 3, strcmp(n->attrib.name, "true") == 0, 6, "Load boolean constant");
            break;
        case Char:
            addLine(LDC, 3, n->attrib.name[1], 6, "Load char constant");
            break;
        // TODO: add STRINGCONST
    }
}

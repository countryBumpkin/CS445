#include <iostream>
#include <fstream>
#include "symbolTable.h"
#include <string>
#include "emitcode.h"

extern SymbolTable decls;
using namespace std;

FILE* code; // pointer to testfile.tm, needed by emitcode

// Defines all TM instructions
enum Instruction {
                    NONE,                                   // Default, not a valid instruction
                    LDC, LDA, LD, ST, JNZ, JZR, JMP,        // REGISTER TO MEMORY INSTRUCTIONS (RA)
                    HALT, NOP, IN, INB, INC_tm, OUT, OUTB,     // REGISTER ONLY INSTRUCTIONS (RO)
                    OUTC, OUTNL, ADD_tm, SUB_tm, MUL, DIV_tm,        // ...
                    MOD_tm, AND_tm, OR_tm, XOR, NOT_tm, NEG, SWP, RND,  // ...
                    TLT, TLE, TEQ, TNE, TGE, TGT, SLT, SGT, // TEST INSTRUCTIONS (RO)
                    MOV, SET, CO, COA,                      // BLOCK MEMORY TO MEMORY INSTRUCTIONS (RO)
                    LIT,                                    // LITERAL INSTRUCTIONS
                };

enum LType {DEFAULT, STR_LIT, NUM_LIT, BOOL_LIT}; // denotes what type of literal this is


/*
    Describes all internal data associated with a single "instruction" or line of 3 address code and provides
    any necessary helper functions.
*/
class TMInstruction {
    private:
        Instruction instruction = NONE;    // the instruction to be executed
        int addrs[3];               // 3 address part of "3 Address Code"
        std::string comment;        // stores a comment for this line
        LType ltype = DEFAULT;      // if this is not default, it stores the type of literal
        union literal {
            std::string* str_lit;// if this is one of the LIT commands, put a string lit here
            int* int_lit;        // also for a LIT command, but for int
            bool* bool_lit;      // for LIT command
        } literal;

    public:
        int address;                // program memory address
        std::string instructionToStr(); // convert an instruction code into a string output
        TMInstruction(int line, Instruction ins, int addr1, int addr2, int addr3, std::string comment);
        TMInstruction(int line, Instruction ins, LType ltype, void* lit_ptr, std::string comment);
        TMInstruction(std::string);
        TMInstruction();
        std::string to_string();    // converts this TM instruction into a single 3 address code to go in output

        TMInstruction* head; // TMInstruction above this in the doubly linked list, NULL if true head of list
        TMInstruction* tail; // TMInstruction below, NULL if true tail of list
};

std::ofstream* tm_output;   // reference to 3 address output file
int pmem;                   // store the address of the next instruction here
int main_loc;               // stores the address in program memory for main
int main_ret_loc;           // store the pmem address of the main return stmt, used in init
int goffset;
int goffFinal;
int breakpoint;
SymbolTable declarations;

// imperfect solution, can't handle multiple definitions of single function name
std::map<std::string, TMInstruction*> functionMap; // function names mapping to instructions

bool isCallChild = false;   // if set true, then nodes below call are params
bool inExpression = false;
// Setup functions
void init();                // sets up all static header comments and cookie-cutter code before tree traversal
// Doubly linked list functions
TMInstruction* prog_head;        // reference to the head/first line of 3 address code
TMInstruction* prog_tail;        // reference to the tail/last line of 3 address code
void addLine(TMInstruction*);    // add new line to end of program
// wrappers for addLine that create a new TMInstruction and add it to the list
TMInstruction* addLine(std::string);
TMInstruction* addLine(Instruction, int, int, int, std::string);
TMInstruction* addLine(Instruction, LType, void*, std::string);
void insertLine(TMInstruction*, TMInstruction*); // insert new line after a specific line
TMInstruction* removeLine(TMInstruction*); // remove a line from the list while keeping lines before and after
void appendToFile(); // write all lines of code to the output file in order

// code generation functions
void genCode(ASTreeNode* n, int offset, bool genSibling);
void genReturn(ASTreeNode*);
void genArgs(ASTreeNode*, int, int);
void genId(ASTreeNode*);
void genOpAssign(ASTreeNode*, std::string, int, std::string);
void genOpIncDec(ASTreeNode*, std::string);

void generateInit();
void loadConst(ASTreeNode*);
void initGlobals(string, void*m);
void backpatchJMPHere(int, string comment);
void backpatchJMPHere(Instruction, int, int, string);

void CodeGenerator(ASTreeNode*, int, SymbolTable);     // Generate code based on the AST passed to the generator
void writeToFile(std::ofstream&, std::string);  // appends a string to the output file
void printCode();           // print each line of code
// Test functions
void testCGEN_INSERT();
void testCGEN_REMOVE();

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

void printCode(){
    std::cout   << "--------------------------------------------------------------\n"
                << "                          PROGRAM\n"
                << "--------------------------------------------------------------\n";

    TMInstruction* tmp = prog_head;
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
            return "JZR";
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

////////////////////////////////////////////////////////////////////////////////
//  CODEGENERATOR                                                             //
////////////////////////////////////////////////////////////////////////////////
/*
 *  Constructs a CodeGenerator objectcase parses the output file namecase and creates a new
 *  *.tm file for the 3 address code to be output to
*/
void CodeGenerator(ASTreeNode* root, int gFinal, SymbolTable st){
    // set defaults for doubly linked list
    prog_head = NULL;
    prog_tail = NULL;
    // create output testfile.tm file
    init();
    // attach pointer to code so we can use emitcode.h
    code = fopen("testfile.tm", "a");
    goffset = 1;
    goffFinal = gFinal;
    declarations = st;
    genCode(root, 0, true);
    generateInit();
    appendToFile();
}

/*
 *  Creates and opens a new output file and writes the header comments and C- I/O libraries into it. Also performs any
 *  useful setup of static code that can be done prior to tree traversal.
 */
void init(){
    std::ofstream tm("testfile.tm");
    tm_output = &tm;

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
void generateInit(){
    int tmp = pmem;
    pmem = 0;
    addLine(JMP, 7, main_ret_loc, 7, "JMP to init");
    pmem = tmp;
    // INIT
    addLine("INIT");
    // set frame at end of globals
    addLine(LDA, 1, goffFinal, 0, "set first frame at end of globals");
    addLine(ST, 1, 0, 1, "store old ");

    addLine("INIT GLOBALS AND STATICS");
    // init globals and statics
    declarations.applyToAllGlobal(initGlobals);
    addLine("END INIT GLOBALS AND STATICS");

    addLine(LDA, 3, 1, 7, "return address in ac");
    // Jump to main in pmem
    addLine(JMP, 7, (main_loc) - pmem - 1, 7, "jump to main");
    addLine(HALT, 0, 0, 0, "END EXECUTION");
    addLine("END INIT");
}
/*
 * Initialize all global variables
 */
void initGlobals(string, void* m){
    ASTreeNode* n = (ASTreeNode*)m; // type cast
    if(n->subkind.decl == VarK &&  n->children[0] != NULL){
        genCode(n->children[0], -2, true);
        addLine(ST, 3, n->loc, 0, "initialize " + string(n->attrib.name));
    }
    if(n->subkind.decl == VarK && n->isArray){
        addLine(LDC, 3, n->size-1, 0, "load size of array " + string(n->attrib.name));
        addLine(ST, 3, n->loc + 1, 0, "store size of array " + string(n->attrib.name));
    }
}


/*
 *  Writes a single line to a file, file returns to state it was in before
 *  writing so if it was closed it will be closed after appending
 */
void writeToFile(std::ofstream& file, std::string line){
    bool was_open = true;
    if(!file.is_open()) {file.open("testfile.tm", std::ofstream::app); was_open = false;}
    file << line << std::endl;
    if(!was_open) file.close();
}

/*
 *  Write all lines of code in LL to the output file in order of program memory address
 */
void appendToFile(){
    std::ofstream file("testfile.tm", std::ofstream::app);
    TMInstruction* tmp = prog_head;
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
void addLine(TMInstruction* tm_ins){
    if(prog_head == NULL) prog_head = prog_tail = tm_ins;
    else{
        prog_tail->tail = tm_ins; // previous tail stores ref to this node as its tail
        tm_ins->head = prog_tail; // store ref to previous tail as above this line
        prog_tail = tm_ins;      // new ref to end of list points to this line
    }
}

TMInstruction* addLine(std::string comment){
    TMInstruction* ins = new TMInstruction(comment);
    addLine(ins);
    return ins;
}

TMInstruction* addLine(Instruction ins, int addr, int addr1, int addr2, std::string comment){
    TMInstruction* instruct = new TMInstruction(pmem++, ins, addr, addr1, addr2, comment);
    addLine(instruct);
    return instruct;
}

TMInstruction* addLine(Instruction ins, LType ltype, void* cVal, std::string comment){
    TMInstruction* instruct = new TMInstruction(pmem++, ins, ltype, cVal, comment);
    addLine(instruct);
    return instruct;
}

/*
 *  Insert a new line after some other specified node
 */
void insertLine(TMInstruction* new_line, TMInstruction* target_line){
    if(target_line == NULL) {printf("ERROR: NULL ptr passed to insertLine()\n"); return;}
    else if(target_line == prog_head){

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
TMInstruction* removeLine(TMInstruction* target){
    if(target == NULL){printf("ERROR: NULL ptr passed to removeLine()\n"); return NULL;}

    if(target != prog_head && target != prog_tail){
        target->head->tail = target->tail;
    }else{
        if(prog_head == target){
            prog_head = target->tail;
            // this->prog_head->head = NULL;
        }

        if(prog_tail == target){
            prog_tail = target->head;
            prog_tail->tail = NULL;
        }
    }


    target->head = NULL;
    target->tail = NULL;
    return target;
}

void genCode(ASTreeNode* n, int offset, bool genSibling){
    if(n == NULL) return; // protect against disaster
    //cout << "gen code for " << n->attrib.name << endl;
    int reset_pt, reset_pt2, breakBack;
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
                    //cout << "decl var " << n->attrib.name << endl;
                    //cout << (n->varkind == LocalStatic) << endl;
                    if(n->varkind != Global && n->varkind != LocalStatic && n->hasInit){
                        addLine("TOFF dec: " + to_string(--offset));
                        if(n->children[0] != NULL && !(n->children[0]->type == Char && n->children[0]->size > 1)){ // if not STRINGCONST
                            genCode(n->children[0], offset, true);
                            addLine(ST, 3, n->loc, 1, "Store variable " + string(n->attrib.name));
                        }
                        if(n->isArray){
                            addLine(LDC, 3, n->size-1, 6, "load size of array " + string(n->attrib.name));
                            addLine(ST, 3, n->loc+1, 1, "store size of array " + string(n->attrib.name));
                        }
                        if(n->children[0] != NULL && n->children[0]->type == Char && n->children[0]->size > 1){ // if STRINGCONST
                            genCode(n->children[0], offset, true);
                        }
                    }
                    if(n->varkind == Global || n->varkind == LocalStatic){
                        //cout << "setting global offset" << endl;
                        goffset = n->loc;
                    }
                    break;
            }
            break;
        case StmtK:
            switch(n->subkind.stmt){
                case IfK:
                    addLine("IF");
                    genCode(n->children[0], offset, true);
                    reset_pt = pmem;
                    pmem++;
                    addLine("THEN");
                    genCode(n->children[1], offset, true);
                    if(n->children[2] != NULL){
                        reset_pt2 = pmem;
                        pmem++;
                    }
                    backpatchJMPHere(JZR, 3, reset_pt, "jump on conditional failure [backpatched]");
                    if(n->children[2] != NULL){
                        addLine("ELSE");
                        genCode(n->children[2], offset, true);
                        backpatchJMPHere(reset_pt2, "skip else [backpatched]");
                    }
                    addLine("ENDIF");
                    break;
                case WhileK:
                    {
                        breakBack = breakpoint;
                        addLine("WHILE");
                        int primary_exp = pmem; // save beginning of the primary expression for evaluation
                        genCode(n->children[0], offset, true); // eval primary expression
                        int goto_do = pmem;         // DO JMP: go here to JMP to the do portion
                        pmem += 2;                  // open instruction slots for DO JMP and BREAK JMP
                        breakpoint = goto_do + 1;   // BREAK JMP: go here to jump out of the loop
                        backpatchJMPHere(JNZ, 3, goto_do, "skip jump to end of while on success [backpatched]");
                        addLine("DO");
                        genCode(n->children[1], offset, true); // gen do stmts
                        addLine(LDC, 7, primary_exp, 0, "go to beginning of while");
                        backpatchJMPHere(breakpoint, "jump to end of while [backpatched]");
                        addLine("END WHILE");
                        breakpoint = breakBack;
                        break;
                    }
                case ForK:
                    {
                        addLine("TOFF set: " + to_string(offset));
                        addLine("FOR");
                        genCode(n->children[0], offset, true); // var
                        genCode(n->children[1], offset, true); // RangeK
                        int primary_exp = pmem;
                        // adjust size of compound to consider For stmt
                        if(n->children[2]->nodekind == StmtK && n->children[2]->subkind.stmt == CompoundK) n->children[2]->size -= 2;
                        genCode(n->children[2], offset, true); // COMPOUND or stmt
                        addLine(LD, 3, offset, 1, "Load index");
                        addLine(LD, 5, offset - 2, 1, "Load step");
                        addLine(ADD_tm, 3, 3, 5, "increment");
                        addLine(ST, 3, offset, 1, "store back to index");
                        addLine(JMP, 7, primary_exp - (pmem + 7), 7, "go to beginning of loop");
                        backpatchJMPHere(primary_exp - 1, "Jump past loop [backpatch]");
                        break;
                    }
                case RangeK:
                    {
                        addLine("RANGE");
                        genCode(n->children[0], offset - 3, true);
                        addLine(ST, 3, offset, 1, "save starting value in index var");
                        genCode(n->children[1], offset - 3, true);
                        addLine(ST, 3, offset-1, 1, "save stop value");
                        if(n->children[2] != NULL){
                            genCode(n->children[2], offset-3, true);
                        }else{
                            addLine(LDC, 3, 1, 6, "default increment by 1");
                        }
                        addLine(ST, 3, offset-2, 1, "save step value");
                        addLine(LD, 4, offset, 1, "loop index");
                        addLine(LD, 5, offset-1, 1, "stop value");
                        addLine(LD, 3, offset-2, 1, "step value");
                        addLine(SLT, 3,4,5, "Op <");
                        addLine(JNZ, 3,1,7, "Jump to loop body");
                        pmem++;
                        break;
                    }
                case CompoundK:
                    reset_pt = offset; // store toff for when we leave it again
                    offset = n->size;
                    addLine("COMPOUND");
                    addLine("TOFF set: " + to_string(offset));
                    addLine("Compound Body");
                    genCode(n->children[0], offset, true); // gen for local decs
                    genCode(n->children[1], offset, true); // gen for stmt list
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
                case BreakK:
                    addLine(JMP, 7, breakpoint-pmem-1, 7, "break"); // this doesn't match code... might have some bugs
                    break;
            }
            break;
        case ExpK:
            switch(n->subkind.exp){
                case OpK:
                    {
                        string op = string(n->attrib.name);
                        //cout << "gen lhs" << endl;
                        genCode(n->children[0], offset, true);
                        // UNARY OPs
                        if(op == "chsign") addLine(NEG, 3, 3, 3, "Op unary -");
                        else if(op == "sizeof"){
                            //genCode(n->children[0], offset, true);
                            addLine(LD, 3, 1, 3, "Load array size");
                            break;
                        }else if(op == "?") addLine(RND, 3, 3, 6, "Op ?");
                        else if(op == "not"){
                            addLine(LDC, 4, 1, 6, "Load 1");
                            addLine(XOR, 3, 3, 4, "Op XOR to get logical not");
                        }else{ // BINARY OPs
                            // gen binary
                            addLine(ST, 3, offset, 1, "Push left side"); // store lhs
                            addLine("TOFF dec: " + to_string(--offset));
                            //cout << "gen rhs" << endl;
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
                    {
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
                        }else if(op == "++" || op == "--"){
                            genOpIncDec(n, op);
                            break;
                        }

                        addLine("Assign EXPRESSION " + op + " " + to_string(n->linenum));
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
                                addLine(LDA, 5, id->loc, id->varkind == Local || id->varkind == Parameter, "(EXP NONPARAM) Load address of base of array " + string(id->attrib.name));
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
                            break;
                        }
                    }
                case InitK:
                    {
                        //cout << "gen InitK" << endl;
                        addLine("InitK here");
                        break;
                    }
            }
            break;
    }

    if(genSibling){genCode(n->sibling, offset, true);}
}

void genReturn(ASTreeNode* n){
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
void genArgs(ASTreeNode* n, int toff, int arg_num){
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
void genId(ASTreeNode* n){
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
void genOpAssign(ASTreeNode* n, string op, int toff, string comment){
    addLine("Assign Op EXPRESSION " + op + " " + to_string(n->linenum));
    if(!strcmp(n->children[0]->attrib.name, "[")){
        genCode(n->children[0]->children[1], toff-1, true);
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
 *  Generate the code for increment and decrement instructions
 */
void genOpIncDec(ASTreeNode* n, string op){
    if(!strcmp(n->children[0]->attrib.name, "[")){ // is array
        addLine(LDC, 3,3,6, "Load integer constant");
        ASTreeNode* id = n->children[0]->children[0];
        if(id->varkind == Parameter){
            addLine(LD, 5, id->loc, id->varkind == Local || id->varkind == Parameter, "Load address of base of array " + string(id->attrib.name));
        }else{
            addLine(LDA, 5, id->loc, id->varkind == Local || id->varkind == Parameter, "Load address of base of array " + string(id->attrib.name));
        }
        addLine(SUB_tm, 5,5,3, "Compute offset of value");
        addLine(LD, 3,0,5, "load the lhs variable " + string(id->attrib.name));
        if(op == "++") addLine(LDA, 3, 1,3, "increment value of " + string(id->attrib.name));
        else addLine(LDA, 3, -1,3, "decrement value of " + string(id->attrib.name));
        addLine(ST, 3, 0, 5, "store variable " + string(id->attrib.name));
    }else{
        ASTreeNode* id = n->children[0];
        addLine(LD, 3, id->loc, id->varkind == Local || id->varkind == Parameter, "retreive old value of " + string(id->attrib.name));
        if(op == "++") addLine(LDA, 3, 1,3, "increment value of " + string(id->attrib.name));
        else addLine(LDA, 3, -1,3, "decrement value of " + string(id->attrib.name));
        addLine(ST, 3, id->loc, id->varkind != Global, "Store variable " + string(id->attrib.name));
    }
}

/*
 *  Helper function for loading a constant into memory
 */
void loadConst(ASTreeNode* n){
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

void backpatchJMPHere(int addr, string comment){
    int store = pmem;
    pmem = addr;
    // LDA here
    addLine(JMP, 7, store - addr - 1, 7, comment);
    pmem = store;
}
void backpatchJMPHere(Instruction ins, int reg, int addr, string comment){
    int store = pmem;
    pmem = addr;
    // JMP here
    addLine(ins, reg, store - addr - 1, 7, comment);
    pmem = store;
}

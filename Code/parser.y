%{
#include "ourgetopt.cpp"
#include <string.h>
#include <stdio.h>
#include <map>
#include "scanType.h"
#include "ASTreeNode.h"
#include "symbolTable.cpp"
#include "memloc.cpp"
#include "semantic.cpp"
#include "yyerror.cpp"
#include "codegen.cpp"

extern int yylex();
extern int yyleng;
extern FILE *yyin;	                         // input source file
extern int line; 	                           // line number from flex scanner
extern int yydebug;                          // yydebug flag

extern int ourGetopt( int, char **, char*);  // function definition for get option program from course website

static ASTreeNode* treeRec; // root of the tree

%}
%define parse.error verbose
%union {
  struct Token *tokenData;
  struct ASTreeNode *treeNode;
}

%token <tokenData> BOOL CHAR INT INC ADDASS SUBASS MULTASS DIVASS ASGN SYMBOL           // data types and symbols
%token <tokenData> ID CHARCONST NUMCONST STRINGCONST BOOLCONST                          // constant types defined by c- grammar
%token <tokenData> STATIC FOR TO BY WHILE DO RETURN BREAK                               // keywords, not defined by c-, discovered in test output assignment #1
%token <tokenData> NOT AND OR IF THEN LT GT EQ GEQ LEQ NEQ DEC CONDITIONAL ELSE         // logical symbols and keywords
%token <tokenData> ADD SUB MULT DIV MOD                                                 // mathematical operators
%token <tokenData> LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA COLON SEMICOLON  // terminal symbols

%type <treeNode> program decList dec varDec funDec compStmt localDecs scopedVarDec
%type <treeNode> varDecList varDecInit varDecID params paramList paramTypeList
%type <treeNode> paramIdList paramID type stmtList stmt
%type <treeNode> matchedif unmatchedif iterRange expStmt exp simpleExp
%type <treeNode> andExp unaryRelExp relExp sumExp mulExp unaryExp factor
%type <treeNode> mutable immutable call args argList returnStmt breakStmt
%type <treeNode> assignop mulop sumop unaryop constant
%type <tokenData> relop


%%
program: decList  { treeRec = $1; /*save tree for traversal and print*/}
  ;

decList:  decList dec {ASTreeNode* l = $1;
                          if(l != NULL)
                          {
                            while(l->sibling != NULL) // traverse as far right as possible
                            {
                              l = l->sibling;
                            }
                            l->sibling = $2;
                            $$ = $1;
                          }else $$ = $2;
                      }
  |       dec         {$$ = $1;}
  ;

dec:  varDec  {$$ = $1;}
  |   funDec  {$$ = $1;}
  |   error   { $$ = NULL;}
  ;


varDec: type varDecList           {
                                    ASTreeNode* l = $2;
                                    while(l != NULL)
                                    {
                                      l->type = $1->type;
                                      if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = $1->type;
                                      l = l->sibling;
                                    }

                                    $$ = $2;
                                  }
  |     type varDecList SEMICOLON {
                                    ASTreeNode* l = $2;
                                    while(l != NULL)
                                    {
                                        //std::cout << "\t" << l->attrib.name << " gets type " << typeToStr($1->type) << std::endl;
                                      l->type = $1->type;
                                      if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = $1->type;
                                      l = l->sibling;
                                    }

                                    $$ = $2;
                                    yyerrok;
                                  }
   |    error varDecList SEMICOLON { $$ = NULL; yyerrok; }
   |    type error SEMICOLON { $$ = NULL; yyerrok; yyerrok; }
   ;

funDec: type ID LPAREN params RPAREN compStmt {
                                                $$ = createDeclNode(FuncK, $1->type, $2->token_str, $2->linenum, $4, $6, NULL);
                                                $6->attrib.name = $2->token_str;  // save name for scope creation
                                              }
  |     ID LPAREN params RPAREN compStmt      {
                                                $$ = createDeclNode(FuncK, Void, $1->token_str, $1->linenum, $3, $5, NULL);
                                                $5->attrib.name = $1->token_str;  // save name for scope creation
                                              }
  |     type error                            { $$ = NULL; }
  |     type ID LPAREN error                  { $$ = NULL; }
  |     ID LPAREN params RPAREN error         { $$ = NULL; }
  ;

compStmt: LBRACE localDecs stmtList RBRACE {
                                              $$ = createStmtNode(CompoundK, "", $1->linenum, $2, $3, NULL);
                                              $$->attrib.name = strdup("comp scope");
                                              yyerrok;
                                            };

localDecs: localDecs scopedVarDec {
                                    ASTreeNode* l = $1;
                                    if(l != NULL)
                                    {
                                      while(l->sibling != NULL)
                                      {
                                          l = l->sibling;
                                      }

                                      l->sibling = $2; // scopedVarDec is the final sibling
                                      $$ = $1;
                                    }else{
                                      $$ = $2;
                                    }
                                  }
  |        localDecs error        {$$ = NULL;}
  |        error scopedVarDec     {$$ = NULL;}
  |        %empty                 {$$ = NULL;}
  ;

scopedVarDec: STATIC type varDecList SEMICOLON  {
                                                  $$ = $3;
                                                  ASTreeNode* l = $3;;
                                                  while(l != NULL)
                                                  {
                                                      //std::cout << "\t" << l->attrib.name << " gets type" << std::endl;
                                                    l->type = $2->type;
                                                    if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = $2->type;
                                                    l->isStatic = true;
                                                    l = l->sibling;
                                                  }
                                                  yyerrok;
                                                }
  |           type varDecList SEMICOLON         {
                                                  $$ = $2;
                                                  //std::cout << "passing type " << typeToStr($1->type) << " to variables on line " << $1->linenum << std::endl;
                                                  ASTreeNode* l = $2;
                                                  while(l != NULL)
                                                  {
                                                    //std::cout << "\t" << l->attrib.name << " gets type" << std::endl;
                                                    l->type = $1->type;
                                                    if(l->children[0] != NULL && l->children[0]->subkind.exp == InitK) l->children[0]->type = $1->type;
                                                    l = l->sibling;
                                                  }
                                                  yyerrok;
                                                };

/*handles one or more variable declarations*/
varDecList: varDecList COMMA varDecInit {
                                          if($1 != NULL){ASTreeNode* l = $1;
                                          while(l->sibling != NULL)
                                            l = l->sibling;

                                          l->sibling = $3;
                                          $$ = $1;}
                                          yyerrok;
                                        }
  |         varDecList COMMA error      { $$ = NULL; }
  |         varDecInit                  { $$ = $1; }
  |         error                       { $$ = NULL; }
  ;

varDecInit: varDecID COLON simpleExp  {
                                            $$ = $1;
                                            if($3 != NULL){
                                                $$->children[0] = $3;
                                                $$->isInitialized = true;
                                                //$3->subkind.exp = InitK;
                                                $$->hasInit = true;
                                            }
                                      }
  |         error COLON simpleExp     { $$ = NULL; yyerrok; }
  |         varDecID                  {
                                        $$ = $1;
                                      };

varDecID: ID LBRACKET NUMCONST RBRACKET {
                                          $$ = createDeclNode(VarK, UndefinedType, $1->token_str, $1->linenum, NULL, NULL, NULL);
                                          $$->isArray = true;
                                          $$->size = $3->numValue + 1; // arrays should be size + 1 in length with first element holding size
                                        }
  |       ID LBRACKET error             { $$ = NULL; }
  |       error RBRACKET                { $$ = NULL; yyerrok; }
  |       ID                            {
                                          $$ = createDeclNode(VarK, UndefinedType, $1->token_str, $1->linenum, NULL, NULL, NULL);
                                          $$->size = 1;
                                        }
  ;

params:  paramList  {$$ = $1;}
  |      %empty     {$$ = NULL;}
  ;

paramList:  paramList SEMICOLON paramTypeList {
                                                $$ = $1;
                                                if($1 != NULL){ASTreeNode* l = $1;
                                                while(l->sibling != NULL)
                                                {
                                                  l = l->sibling;
                                                  if(l->isArray) l->size = 1; // arrays are passed by reference so 1 word in size
                                                }

                                                l->sibling = $3;}
                                              }
  |         paramTypeList                     {$$ = $1;}
  |         paramList SEMICOLON error         { $$ = NULL; }
  |         error                             { $$ = NULL; }
  ;

paramTypeList: type paramIdList {
                                  $$ = $2;
                                  ASTreeNode* l = $2;
                                  while(l != NULL)
                                  {
                                      //std::cout << "\t" << l->attrib.name << " gets type" << typeToStr(l->type) << std::endl;
                                    l->type = $1->type;
                                    l->size = 1;
                                    l = l->sibling;
                                  }
                                }
   | type error                 { $$ = NULL; }
   ;

paramIdList:  paramIdList COMMA paramID {
                                          $$ = $1;
                                          if($1 != NULL){ASTreeNode* l = $1;
                                          while(l->sibling != NULL){
                                            l = l->sibling;
                                          }

                                          l->sibling = $3;}
                                          yyerrok;
                                        }
  |           paramID                   { $$ = $1; }
  |           paramIdList COMMA error   { $$ = NULL; }
  |           error                     { $$ = NULL; }
  ;

paramID:  ID                    {
                                  $$ = createDeclNode(ParamK, UndefinedType, $1->token_str, $1->linenum, NULL, NULL, NULL);
                                }
  |       ID LBRACKET RBRACKET  {
                                  $$ = createDeclNode(ParamK, UndefinedType, $1->token_str, $1->linenum, NULL, NULL, NULL);
                                  $$->isArray = true;
                                }
  ;

type: BOOL  {
              $$ = tokenToNode($1);
              $$->type = Boolean;
            }
  |   CHAR  {
              $$ = tokenToNode($1);
              $$->type = Char;
            }
  |   INT   {
              $$ = tokenToNode($1);
              $$->type = Integer;
            }
  ;

stmtList: stmtList stmt   {
                            ASTreeNode* l = $1;
                            if(l != NULL)
                            {
                              while(l->sibling != NULL)
                              {
                                l = l->sibling;
                              }

                              l->sibling = $2;
                              $$ = $1;
                            }else $$ = $2;
                          }
  |       %empty          {$$ = NULL;}
  ;

stmt: matchedif {$$ = $1;}
  |   unmatchedif {$$ = $1;}
  ;

matchedif: IF error                                   { $$ = NULL; }
  |        IF error ELSE matchedif                    { $$ = NULL; yyerrok; }
  |        IF error THEN matchedif ELSE matchedif     { $$ = NULL; yyerrok; }
  |        IF simpleExp THEN matchedif ELSE matchedif {
                                                        $$ = createStmtNode(IfK, "if", $1->linenum, $2, $4, $6);
                                                      }
  |        WHILE error DO matchedif                   { $$ = NULL; yyerrok; }
  |        WHILE error                                { $$ = NULL; }
  |        WHILE simpleExp DO matchedif               {
                                                        $$ = createStmtNode(WhileK, "", $1->linenum, $2, $4, NULL);
                                                      }
  |        FOR ID ASGN error DO matchedif             { $$ = NULL; yyerrok; }
  |        FOR ID ASGN iterRange DO matchedif         {
                                                        ASTreeNode* n = tokenToNode($2);
                                                        n->nodekind = DeclK;
                                                        n->subkind.decl = VarK;
                                                        n->type = Integer;
                                                        n->isInitialized = true;
                                                        n->size = 1;
                                                        $$ = createStmtNode(ForK, "", $1->linenum, n, $4, $6);
                                                      }
  |        FOR error                                  { $$ = NULL; }
  |        returnStmt                                 {$$ = $1;}
  |        breakStmt                                  {$$ = $1;}
  |        expStmt                                    {$$ = $1;}
  |        compStmt                                   {
                                                          $$ = $1;
                                                          //$$->attrib.name = strdup("matchedif scope");
                                                      }
  ;

unmatchedif:  IF error THEN matchedif                       { $$ = NULL; yyerrok; }
  |           IF simpleExp THEN matchedif                   {
                                                              $$ = createStmtNode(IfK, "if", $1->linenum, $2, $4, NULL);
                                                            }
  |           IF error THEN unmatchedif                     { $$ = NULL; yyerrok; }
  |           IF simpleExp THEN unmatchedif                 {
                                                              $$ = createStmtNode(IfK, "if", $1->linenum, $2, $4, NULL);
                                                            }
  |           IF error THEN matchedif ELSE unmatchedif      { $$ = NULL; yyerrok; }
  |           IF simpleExp THEN matchedif ELSE unmatchedif  {
                                                              $$ = createStmtNode(IfK, "if", $1->linenum, $2, $4, $6);
                                                            }
  |           WHILE simpleExp DO unmatchedif                {
                                                              $$ = createStmtNode(WhileK, "", $1->linenum, $2, $4, NULL);
                                                            }
  |           FOR ID ASGN iterRange DO unmatchedif          {
                                                              ASTreeNode* n = tokenToNode($2);
                                                              n->nodekind = DeclK;
                                                              n->subkind.decl = VarK;
                                                              n->type = Integer;
                                                              n->isInitialized = true;
                                                              n->size = 1;
                                                              $$ = createStmtNode(ForK, "", $1->linenum, n, $4, $6);
                                                            }
  ;

iterRange:  simpleExp TO error                  { $$ = NULL; }
  |         error BY error                      { $$ = NULL; yyerrok; }
  |         simpleExp TO simpleExp              {
                                                  $$ = createStmtNode(RangeK, "", $2->linenum, $1, $3, NULL);
                                                }
  |         simpleExp TO simpleExp BY simpleExp {
                                                  $$ = createStmtNode(RangeK, "", $2->linenum, $1, $3, $5);
                                                }
  |         simpleExp TO simpleExp BY error     { $$ = NULL; }
  ;

expStmt:  exp SEMICOLON   {$$ = $1;}
  |       SEMICOLON       {$$ = NULL;}
  |       error SEMICOLON { $$ = NULL; yyerrok; }
  ;

exp:  error assignop exp    { $$ = NULL; yyerrok; }
  |   mutable assignop exp  {
                              $$ = $2;
                              $$->children[0] = $1;
                              $$->children[1] = $3;
                            }
  |   mutable assignop error { $$ = NULL; }
  |   mutable INC           {
                              $$ = tokenToNode($2);
                              $$->nodekind = ExpK;
                              $$->subkind.exp = AssignK;
                              $$->children[0] = $1;
                            }
  |   error INC             { $$ = NULL; yyerrok; }
  |   mutable DEC           {
                              $$ = tokenToNode($2);
                              $$->nodekind = ExpK;
                              $$->subkind.exp = AssignK;
                              $$->children[0] = $1;
                            }
  |   error DEC             { $$ = NULL; yyerrok; }
  |   simpleExp             { $$ = $1; }
  ;

simpleExp:  simpleExp OR error  { $$ = NULL; }
  |         simpleExp OR andExp {
                                  $$ = createOpNode($2->token_str, $2->linenum, $1, $3, NULL);
                                }
  |         andExp              {$$ = $1;}
  ;

andExp: andExp AND error        { $$ = NULL; }
  |     andExp AND unaryRelExp  {
                                  $$ = createOpNode($2->token_str, $2->linenum, $1, $3, NULL);
                                }
  |     unaryRelExp             {$$ = $1;}
  ;

unaryRelExp:  NOT error       { $$ = NULL; }
  |           NOT unaryRelExp {
                                $$ = createOpNode($1->token_str, $2->linenum, $2, NULL, NULL);
                              }
  |           relExp          {$$ = $1;}
  ;

relExp: sumExp relop sumExp {
                              $$ = createOpNode($2->token_str, $2->linenum, $1, $3, NULL);
                            }
  |     sumExp              {
                              $$ = $1;
                            }
  |     sumExp relop error  {
                                $$ = NULL;
                            }
  ;

sumExp: sumExp sumop error    { $$ = NULL; }
  |     sumExp sumop mulExp   {
                                $$ = createOpNode($2->attrib.name, $2->linenum, $1, $3, NULL);
                              }
  |     mulExp                {$$ = $1;};

mulExp: mulExp mulop error    { $$ = NULL; }
  |     mulExp mulop unaryExp {
                                $$ = createOpNode($2->attrib.name, $2->linenum, $1, $3, NULL);
                              }
  |     unaryExp              {$$ = $1;};

unaryExp: unaryop error       { $$ = NULL; }
  |       unaryop unaryExp    {
                                $$ = $1;
                                $$->children[0] = $2; // unaryExp
                              }
  |       factor              { $$ = $1; };

factor: mutable   {$$ = $1;}
  |     immutable {$$ = $1;}
  ;

mutable:  ID                        {
                                      $$ = tokenToNode($1);
                                      $$->subkind.exp = IdK;
                                      $$->type = UndefinedType;
                                    }
  |       ID LBRACKET exp RBRACKET  {
                                      $$ = createOpNode("[", $1->linenum, tokenToNode($1), $3, NULL);
                                      $$->children[0]->subkind.exp = IdK;
                                      //$$->children[0]->isArray = true;
                                    };

immutable:  LPAREN exp RPAREN   { $$ = $2; yyerrok; }
  |         LPAREN error        { $$ = NULL; }
  |         call                {$$ = $1;}
  |         constant            {$$ = $1;}
  ;

call: ID LPAREN args RPAREN {
                              $$ = createNode(ExpK);
                              $$->subkind.exp = CallK;
                              $$->attrib.name = strdup($1->token_str);
                              $$->linenum = $1->linenum;
                              // count args
                              int count = 0;
                              ASTreeNode* l = $3;
                              while(l != NULL){
                                count++;
                                l = l->sibling;
                              }
                              $$->num_params = count;   // save number of params
                              if($3 != NULL) $$->children[0] = $3;
                            }
  |   error LPAREN          { $$ = NULL; yyerrok; }
  ;

args: argList     {$$ = $1;}
  |   %empty      {$$ = NULL;}
  ;

argList:  argList COMMA exp {
                              ASTreeNode* l = $1;
                              if(l != NULL)
                              {
                                while(l->sibling != NULL){
                                  l = l->sibling;
                                }

                                l->sibling = $3;
                                $$ = $1;

                              }else $$ = $3;
                              yyerrok;
                            }
  |       exp               {$$ = $1;}
  |       argList COMMA error { $$ = NULL; yyerrok; }
  ;

returnStmt: RETURN SEMICOLON      {
                                      $$ = createStmtNode(ReturnK, "", $1->linenum, NULL, NULL, NULL);
                                      $$->type = Integer; // the type associated with the default return value
                                      $$->numCVal = 0; // the value returned by non-specific return statements
                                  }
  |         RETURN exp SEMICOLON  {
                                      $$ = createStmtNode(ReturnK, "", $1->linenum, $2, NULL, NULL);
                                      $$->type = UndefinedType;
                                      yyerrok;
                                  }
  |         RETURN error SEMICOLON { $$ = NULL; yyerrok; }
  ;

breakStmt: BREAK SEMICOLON  {
                                $$ = createStmtNode(BreakK, "", $1->linenum, NULL, NULL, NULL);
                            };


assignop: ASGN      {
                      $$ = tokenToNode($1);
                      $$->nodekind = ExpK;
                      $$->subkind.exp = AssignK;
                    }
  |       ADDASS    {
                      $$ = tokenToNode($1);
                      $$->nodekind = ExpK;
                      $$->subkind.exp = AssignK;
                    }
  |       SUBASS    {
                      $$ = tokenToNode($1);
                      $$->nodekind = ExpK;
                      $$->subkind.exp = AssignK;
                    }
  |       MULTASS   {
                      $$ = tokenToNode($1);
                      $$->nodekind = ExpK;
                      $$->subkind.exp = AssignK;
                    }
  |       DIVASS    {
                      $$ = tokenToNode($1);
                      $$->nodekind = ExpK;
                      $$->subkind.exp = AssignK;
                    };

mulop:  MULT  {$$ = tokenToNode($1); $$->subkind.exp = OpK;}
  |     DIV   {$$ = tokenToNode($1); $$->subkind.exp = OpK; }
  |     MOD   {$$ = tokenToNode($1); $$->subkind.exp = OpK;}
  ;

sumop:  ADD   {$$ = tokenToNode($1); $$->subkind.exp = OpK;}
  |     SUB   {$$ = tokenToNode($1); $$->subkind.exp = OpK;}
  ;

unaryop:  SUB         {
                        $$ = createOpNode("chsign", $1->linenum, NULL, NULL, NULL);
                      }
  |       MULT        {
                        $$ = createOpNode("sizeof", $1->linenum, NULL, NULL, NULL);
                      }
  |       CONDITIONAL {
                        $$ = createOpNode($1->token_str, $1->linenum, NULL, NULL, NULL);
                      }
  ;

relop:  LT    {$$ = $1;}
  |     LEQ   {$$ = $1;}
  |     GT    {$$ = $1;}
  |     GEQ   {$$ = $1;}
  |     EQ    {$$ = $1;}
  |     NEQ   {$$ = $1;}
  ;

constant: NUMCONST      {
                            $$ = tokenToNode($1);
                            $$->nodekind = ExpK;
                            $$->subkind.exp = ConstantK;
                            $$->type = Integer;
                        }
  |       STRINGCONST   {
                            $$ = tokenToNode($1);
                            $$->nodekind = ExpK;
                            $$->subkind.exp = ConstantK;
                            $$->varkind = Global;
                            $$->type = Char;
                            $$->isArray = true;
                            $$->size = $1->length + 1; // add 1 for NUL terminal
                        }
  |       CHARCONST     {
                            $$ = tokenToNode($1);
                            $$->nodekind = ExpK;
                            $$->subkind.exp = ConstantK;
                            $$->type = Char; // NOTE: this used to be CharInt to represent 'c'
                        }
  |       BOOLCONST     {
                            $$ = tokenToNode($1);
                            $$->nodekind = ExpK;
                            $$->subkind.exp = ConstantK;
                            $$->type = Boolean;
                        }
  ;

%%

int numErrors = 0;
int numWarnings = 0;

/*
    Compile the provided program printing only warnings and errors.
    IF no errors are thrown, calculate offsets, then finish with generating 3 address code.
*/
void compileNoArgs(char* argv[]){
    int fileIndex = 1;
    if ((yyin = fopen(argv[fileIndex], "r"))){
        // PARSE INPUT
        initErrorProcessing();  // init map for standardized error messages
        yyparse();              // parse file for semantic completeness
        // SEMANTIC ANALYSIS
        SemanticAnalyzer sa = SemanticAnalyzer();   // create object for semantic analysis
        sa.semanticCheck(treeRec, false);           // perform semantic analysis, check that all code "makes sense"
        // OFFSET CALCULATION
        int goffset = 0;
        if(sa.getErrors() == 0){ // if there still aren't errors calculate memory/stack offsets
            Memloc memController = Memloc();
            goffset = memController.traverseTree(treeRec); // fill tree with memory locations
        }
        // CODE GEN
        if(sa.getErrors() == 0){ // check redundant, here just to separate code
            // traverse AST tree in one(or more) passes and construct 3 address code for tm.c
            printf("Number of warnings: %d\n", sa.getWarnings());
            printf("Number of errors: %d\n", sa.getErrors());

            CodeGenerator cg(treeRec);
        }
    }
}

int main(int argc, char *argv[]){
    bool printAnnotatedTree = false, printAugmentedTree = false, printTreeFlag = false, printSTDebug = false;

    // get argument inputs, set flags
    int c;
    c = ourGetopt( argc, argv, (char *)"pPdDMh" );
    int goodArgs = 0;
    while(c != -1) {
        goodArgs++;
 		switch ( c )
 		{
            case 'p':
				printTreeFlag = true;
                break;
            case 'P':
                printAnnotatedTree = true;
                break;
    		case 'd':
    			yydebug = 1;
                break;
            case 'M':
                printAugmentedTree = true;
                printAnnotatedTree = true;
                break;
            case 'D':
                printSTDebug = true;
                break;
            case 'h':
                {
                    const char* usage_msg = "usage: -c [options] [sourcefile]\noptions:\n"
                                  "-d          - turn on parser debugging\n"
                                  "-D          - turn on symbol table debugging\n"
                                  "-h          - print this usage message\n"
                                  "-M          - print augmented tree with variable sizes and locations\n"
                                  "-p          - print the abstract syntax tree\n"
                                  "-P          - print the abstract syntax tree plus type information";
                    printf("%s", usage_msg);
                    break;
                }
            default:
                printf("ignoring %i\n", c);
        }
        c = ourGetopt( argc, argv, (char *)"pdDhMP" );
    }
    if(goodArgs == 0 && argc > 1){ // if no arguments provided with file, run semantic check, memory allocation, and if no errors do code gen
        compileNoArgs(argv);

    }else if (argc > 1) // open file passed for compiling
    {
        int fileIndex = 1 + goodArgs;
        if ((yyin = fopen(argv[fileIndex], "r"))){
            // file open successful
            initErrorProcessing();
            yyparse();

            // execute options for flags set by args
            if(printTreeFlag){
                TreePrinter::printTree(treeRec);
            }

            SemanticAnalyzer sa = SemanticAnalyzer();

            if(numErrors <= 0){ // check the tree for semantic errors and print them
                sa.semanticCheck(treeRec, printSTDebug);

                // if there still aren't errors do memory allocation
                if(numErrors == 0){
                    int goffset;
                    if(sa.getErrors() == 0){
                        Memloc memController = Memloc();
                        goffset = memController.traverseTree(treeRec); // fill tree with memory locations
                    }

                    if(printAnnotatedTree){
                        sa.printSemanticOutput();
                        if(sa.getErrors() == 0 && printAugmentedTree){
                            TreePrinter::printAugmentedTree(treeRec);
                            printf("Offset for end of global space: %d\n", goffset);
                        }else if(!printAugmentedTree && sa.getErrors() == 0 && printAnnotatedTree){
                            // print the tree with added type information
                            TreePrinter::printAnnotatedTree(treeRec);
                        }
                    }
                }
            }
            // print error and warning counts
            printf("Number of warnings: %d\n", sa.getWarnings());
            printf("Number of errors: %d\n", sa.getErrors());

            return 0;
        }
        else{
            // failed to open file
            printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[fileIndex]);
            numErrors++;
            printf("Number of warnings: %d\n", numWarnings);
            printf("Number of errors: %d\n", numErrors);
            exit(1);
        }

    }


}

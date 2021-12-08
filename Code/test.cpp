#include <fstream>
#include <iostream>
#include <map>

#include "codegen.cpp"

using namespace std;

void testCGEN_REMOVE(){
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

void testCGEN_INSERT(){
	std::cout << "------------------------------------------------------------\n"
			  << "TEST: insertLine()\n"
			  << "-------------------------------------------------------------\n";

	CodeGenerator* cg = new CodeGenerator(NULL);
	TMInstruction* a = new TMInstruction(0, LDA, 0, 0, 0, "dummy line");
	std::string str("\"str literal\"");
	TMInstruction* b = new TMInstruction(2, LIT, STR, &str, "LIT instruction");
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



int main(){
	/*fstream mf("filename.txt");

	mf << "Files can be tricky, but it is fun enough!";

	mf.close();*/
	testCGEN_REMOVE();
	testCGEN_INSERT();

}

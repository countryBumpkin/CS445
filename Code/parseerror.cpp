#include "parseerror.h"
void throw_error(std::string token){
    std::cout << "ERROR(" << line << "): Invalid or misplaced input character: \'" << token << "\'. Character Ignored." << std::endl;
}

#include <iostream>
#include <memory>
#include <fstream>
#include "Interpreter.h"

int main() {
    auto ifs_p = std::make_shared<std::ifstream>("midcode.txt");
    std::shared_ptr<std::ostream> os_p = std::make_shared<std::ostream>(std::cout.rdbuf());
    std::shared_ptr<Interpreter> interpreter_p = Interpreter::getInterpreter_p(ifs_p);
    interpreter_p->setOs(os_p);
    interpreter_p->run();
    return 0;
}

//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_INTERPRETER_H
#define VM_INTERPRETER_H

#include "BaseObject.h"
#include "PCode.h"
#include "PCode/ADD.h"
#include "PCode/DIV.h"
#include "PCode/LIT.h"
#include "PCode/LOD.h"
#include "PCode/MINUS.h"
#include "PCode/MOD.h"
#include "PCode/MULT.h"
#include "PCode/STO.h"
#include "PCode/PINT.h"
#include "PCode/EQ.h"
#include "PCode/GEQ.h"
#include "PCode/GRE.h"
#include "PCode/LSS.h"
#include "PCode/LEQ.h"
#include "PCode/CALL.h"
#include "PCode/RET.h"
#include "PCode/ALLO.h"
#include "PCode/BRT.h"
#include "PCode/PUSH.h"
#include "PCode/PWRAP.h"
#include "PCode/GETINT.h"
#include "VMSymTable.h"
#include <vector>
#include <memory>
#include <iostream>
#include <stack>
#include <map>

namespace INTERPRETER {
    class Interpreter : public BaseObject {
    private:
        std::vector<std::shared_ptr<PCode>> MidCodeSequence;
        std::vector<int> DataStack;         // all the data allocate at stack
        std::vector<int> DynamicLink;       // ?
        std::vector<int> ReturnAddrLink;    // return address stack
        std::vector<int> tempVarUseCount;   // is it necessary
        std::vector<int> funcCallStack;     // every param pass toStore a func store here
        int PC = 0;
        int StackOffset{};
        std::shared_ptr<std::ostream> os_p = nullptr;
        std::map<std::string, int> labels;
        std::shared_ptr<VarTable> varTable_p = std::make_shared<VarTable>(nullptr);
        std::shared_ptr<FuncTable> funcTable_p = std::make_shared<FuncTable>();

        static std::shared_ptr<Interpreter> instance_p;
    private:
//    explicit INTERPRETER() = default;

        explicit Interpreter(std::shared_ptr<std::istream> istream_p);

    public:

        Interpreter(Interpreter &) = delete;

        Interpreter(Interpreter &&) = delete;

        Interpreter operator=(Interpreter &) = delete;

        Interpreter operator=(Interpreter &&) = delete;

        void run();

        void setOs(std::shared_ptr<std::ostream> ostream_p);

        static std::shared_ptr<Interpreter>
        getInterpreter_p(std::vector<std::shared_ptr<PCode>> midCodeSequence, std::map<std::string, int> labels);

        static std::shared_ptr<Interpreter> getInterpreter_p(std::shared_ptr<std::istream> istream_p);

        virtual std::string to_string(std::shared_ptr<VarTable> varTable_p) const;

        explicit Interpreter(std::vector<std::shared_ptr<PCode>> midCodeSequence, std::map<std::string, int> labels);
    };
}


#endif //VM_INTERPRETER_H

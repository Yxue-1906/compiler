//
// Created by unrelated on 2021/11/20.
//

#ifndef VM_PCODE_H
#define VM_PCODE_H


#include "BaseObject.h"
#include "VMSymTable.h"

#ifdef ADD
#undef ADD
#endif

class PCode : public BaseObject {
public:
    enum class Type {
        ADD,            // ADD: add top with sub top, pop them and push the outcome
        ALLO,           // ALLO <Name> <Size> -> alloc space in the stack and store the address toStore <Name>
        AND,
        BEND,           // BEND : end the block -> delete top VarTable
        BRF,            // BRF <judge> <label>: jump to label if <judge> is false
        BRT,            // BRT <judge> <label>: jump to label if <judge> is true
        BSTA,           // BSTA : start a new block -> open a new VarTable
        CALL,           // CALL <FuncName> : store PC+1 toStore RA, make a new VarTable, store from toStore PC
        DIV,            // DIV: divide top with sub top, pop them and push the outcome
        EQ,             // EQ : judge top and sub top is equal, pop them two and push the outcome
        GEQ,
        GETA,           // GETA <StoreTo> <From> -> get base of <From>
        GETINT,         // GETINT -> read an integer from console and push it toStore top
        GRE,
        INIT,           // INIT <Size> <InitValues>... -> alloc space and init some of them
        J,              // J <Label> -> jump toStore label immediately
        LEQ,
        LIT,            // LIT <int> : load int toStore top
        LOD,            // LOD <Name> <Address> : load value from address toStore the top, and named it with <Name>
        LODA,           // LODA <Name> <Size> -> load address of <VarName>+<Offset>
        LSS,
        MINUS,          // MINUS: minus top with sub top, pop them and push the outcome
        MOD,            // MOD: mod top with sub top, pop them and push the outcome
        MULT,           // MULT: multiple top with sub top, pop them and push the outcome
        NEQ,
        NOT,            // NOT <VarName> <toStore> : store !<VarName> to <toStore>
        OR,
        PINT,           // PINT <VarName> : print value of <VarName>
        PSTR,           // PSTR <Str> : or maybe ...
        PUSH,           // PUSH -> push the value of top into func call stack
        PWRAP,          // PWARP : print warp
        RET,            // RET <VarName>|void : delete VarTable, restore PC with RA
        STO,            // STO <Value> <Address> : store value toStore address
        STOP,           // STOP <Value> <Address> <Offset> : store value toStore address
    };

public:
    virtual std::string
    to_string(std::shared_ptr<VarTable> varTable_p, const std::vector<int> &DataStack) const = 0;
};

using Type = PCode::Type;

#endif //VM_PCODE_H

//
// Created by unrelated on 2021/11/20.
//

#include "Interpreter.h"
#include "PCode/J.h"
#include "PCode/LODA.h"
#include "PCode/GETA.h"
#include "PCode/STOP.h"
#include "PCode/NOT.h"
#include "PCode/PSTR.h"
#include "PCode/NEQ.h"
#include "PCode/AND.h"
#include "PCode/OR.h"
#include "PCode/BRF.h"


std::shared_ptr<INTERPRETER::Interpreter>INTERPRETER::Interpreter::instance_p = nullptr;

//std::shared_ptr<INTERPRETER> INTERPRETER::getInterpreter_p() {
//    if (!instance_p)
//        instance_p.reset(new INTERPRETER());
//    else {
//        std::cerr << "warning: INTERPRETER has been initialized, you get the former one" << std::endl;
//    }
//    return instance_p;
//}

INTERPRETER::Interpreter::Interpreter(std::shared_ptr<std::istream> istream_p) {
    this->StackOffset = 0;
    this->DynamicLink.push_back(0);
    this->ReturnAddrLink.push_back(0);
    this->tempVarUseCount.push_back(1);
    std::istream &istream = *istream_p;
    for (; !istream.eof();) {
        std::string ins;
        istream >> ins;
        if (ins == "INIT") {
            std::string name, tmp;
            int size, addr = DataStack.size();
            istream >> name >> size >> tmp;
            for (int i = 0; i < size; ++i) {
                if (tmp != ";") {
                    DataStack.push_back(std::stoi(tmp));
                    istream >> tmp;
                } else {
                    DataStack.push_back(0);
                }
            }
            varTable_p->add(name, DataStack.size());
            DataStack.push_back(addr);
            continue;
        } else if (ins == "ADD") {
            std::string name1, name2, toStore;
            istream >> name1 >> name2 >> toStore;
            MidCodeSequence.push_back(std::make_shared<ADD>(name1, name2, toStore));
        } else if (ins == "ALLO") {
            std::string name;
            int size;
            istream >> name >> size;
            MidCodeSequence.push_back(std::make_shared<ALLO>(name, size));
        } else if (ins == "BRT") {
            std::string label1, label2;
            istream >> label1 >> label2;
            MidCodeSequence.push_back(std::make_shared<BRT>(label1, label2));
        } else if (ins == "CALL") {
            std::string funcName;
            std::string param;
            std::vector<std::string> formalParams;
            std::vector<std::string> inParams;
            istream >> funcName;
            istream >> param;
            for (; param != ";"; istream >> param) {
                formalParams.push_back(param);
                istream >> param;
                inParams.push_back(param);
            }
            MidCodeSequence.push_back(std::make_shared<CALL>(funcName, inParams, formalParams));
            continue;
        } else if (ins == "DIV") {
            std::string name1, name2, toStore;
            istream >> name1 >> name2 >> toStore;
            MidCodeSequence.push_back(std::make_shared<DIV>(name1, name2, toStore));
        } else if (ins == "EQ") {
            std::string left, right, toStore;
            istream >> left >> right >> toStore;
            MidCodeSequence.push_back(std::make_shared<EQ>(left, right, toStore));
        } else if (ins == "GEQ") {
            std::string left, right, toStore;
            istream >> left >> right >> toStore;
            MidCodeSequence.push_back(std::make_shared<GEQ>(left, right, toStore));
        } else if (ins == "GETA") {
            std::string toStore, from;
            istream >> toStore >> from;
            MidCodeSequence.push_back(std::make_shared<GETA>(toStore, from));
        } else if (ins == "GETINT") {
            std::string base, offset;
            istream >> base >> offset;
            MidCodeSequence.push_back(std::make_shared<GETINT>(base, offset));
        } else if (ins == "GRE") {
            std::string left, right, toStore;
            istream >> left >> right >> toStore;
            MidCodeSequence.push_back(std::make_shared<GRE>(left, right, toStore));
        } else if (ins == "J") {
            std::string label;
            istream >> label;
            MidCodeSequence.push_back(std::make_shared<J>(label));
        } else if (ins == "LEQ") {
            std::string left, right, toStore;
            istream >> left >> right >> toStore;
            MidCodeSequence.push_back(std::make_shared<LEQ>(left, right, toStore));
        } else if (ins == "LIT") {
            int instantValue;
            istream >> instantValue;
            MidCodeSequence.push_back(std::make_shared<LIT>(instantValue));
        } else if (ins == "LOD") {
            std::string toStore, from, offset;
            istream >> toStore >> from >> offset;
            MidCodeSequence.push_back(std::make_shared<LOD>(toStore, from, offset));
        } else if (ins == "LODA") {
            std::string toStore, from, offset;
            istream >> toStore >> from >> offset;
            MidCodeSequence.push_back(std::make_shared<LODA>(toStore, from, offset));
        } else if (ins == "LSS") {
            std::string left, right, toStore;
            istream >> left >> right >> toStore;
            MidCodeSequence.push_back(std::make_shared<LSS>(left, right, toStore));
        } else if (ins == "MINUS") {
            std::string name1, name2, toStore;
            istream >> name1 >> name2 >> toStore;
            MidCodeSequence.push_back(std::make_shared<MINUS>(name1, name2, toStore));
        } else if (ins == "MOD") {
            std::string name1, name2, toStore;
            istream >> name1 >> name2 >> toStore;
            MidCodeSequence.push_back(std::make_shared<MOD>(name1, name2, toStore));
        } else if (ins == "MULT") {
            std::string name1, name2, toStore;
            istream >> name1 >> name2 >> toStore;
            MidCodeSequence.push_back(std::make_shared<MULT>(name1, name2, toStore));
        } else if (ins == "STO") {
            std::string value, base, offset;
            istream >> value >> base >> offset;
            MidCodeSequence.push_back(std::make_shared<STO>(value, base, offset));
        } else if (ins == "PINT") {
            std::string name;
            istream >> name;
            MidCodeSequence.push_back(std::make_shared<PINT>(name));
        } else if (ins == "PUSH") {
            std::string name;
            istream >> name;
            MidCodeSequence.push_back(std::make_shared<PUSH>(name));
        } else if (ins == "PWARP") {
            MidCodeSequence.push_back(std::make_shared<PWRAP>());
        } else if (ins == "RET") {
            MidCodeSequence.push_back(std::make_shared<RET>());
        }/* else if (ins == "LA") {
            Mid
        }*/ else if (ins.back() == ':') {
            labels.emplace(ins.substr(0, ins.size() - 1), MidCodeSequence.size());
            continue;
        } else {
            if (ins.empty())
                break;
            std::cout << "unknown ins:" << ins << std::endl;
            int tmp;
            std::cin >> tmp;//stuck here
            continue;
        }
        istream >> ins;
        if (ins != ";") {
            std::cout << "error: ins stopped without ';'" << std::endl;
            int tmp;
            std::cin >> tmp;
            continue;
        }
    }
    PC = labels["main"];
}

//INTERPRETER::INTERPRETER(std::vector<std::shared_ptr<PCode>> midCodeSequence) {
//    this->StackOffset = 0;
//    this->DynamicLink.push_back(0);
//    this->ReturnAddrLink.push_back(0);
//    this->MidCodeSequence = midCodeSequence;
//}

std::shared_ptr<INTERPRETER::Interpreter>
INTERPRETER::Interpreter::getInterpreter_p(std::vector<std::shared_ptr<PCode>> midCodeSequence,
                                           std::map<std::string, int> labels) {
    if (!instance_p) {
        instance_p.reset(new Interpreter(midCodeSequence, labels));
    } else {
        std::cerr << "warning: INTERPRETER has been initialized, you get the former one" << std::endl;
    }
    return instance_p;
}

std::shared_ptr<INTERPRETER::Interpreter>
INTERPRETER::Interpreter::getInterpreter_p(std::shared_ptr<std::istream> istream_p) {
    if (!instance_p) {
        instance_p.reset(new Interpreter{istream_p});
    } else {
        std::cerr << "warning: INTERPRETER has been initialized, you get the former one" << std::endl;
    }
    return instance_p;
}

void INTERPRETER::Interpreter::run() {
    for (; PC < MidCodeSequence.size();) {
#ifdef VM_DEBUG
      if(!std::dynamic_pointer_cast<PSTR>(MidCodeSequence[PC]))
        std::cout << MidCodeSequence[PC]->to_string(varTable_p, DataStack) << std::endl;
#endif
        if (std::dynamic_pointer_cast<ADD>(MidCodeSequence[PC])) {
            auto add_p = std::dynamic_pointer_cast<ADD>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(add_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(add_p->name1);
            addr = varTable_p->find(add_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(add_p->name2);
            addr = varTable_p->find(add_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a + b;
            } else {
                varTable_p->add(add_p->toStore, DataStack.size());
                DataStack.push_back(a + b);
            }
        } else if (std::dynamic_pointer_cast<ALLO>(MidCodeSequence[PC])) {
            auto allo_p = std::dynamic_pointer_cast<ALLO>(MidCodeSequence[PC]);
            int addr = DataStack.size();
            for (int i = 0; i < allo_p->size; ++i) {
                DataStack.push_back(0);
            }
            varTable_p->add(allo_p->name, addr);
//            DataStack.push_back(addr);
        } else if (std::dynamic_pointer_cast<AND>(MidCodeSequence[PC])) {
            auto and_p = std::dynamic_pointer_cast<AND>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(and_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(and_p->name1);
            addr = varTable_p->find(and_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(and_p->name2);
            addr = varTable_p->find(and_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a && b;
            } else {
                varTable_p->add(and_p->toStore, DataStack.size());
                DataStack.push_back(a && b);
            }
        } else if (std::dynamic_pointer_cast<BRF>(MidCodeSequence[PC])) {
            auto brf_p = std::dynamic_pointer_cast<BRF>(MidCodeSequence[PC]);
            int judge, addr;
            addr = varTable_p->find(brf_p->judge);
            if (addr != -1) {
                judge = DataStack[addr];
            } else {
                judge = std::stoi(brf_p->judge);
            }
            if (!judge) {
                PC = labels[brf_p->label];
                continue;
            }
        } else if (std::dynamic_pointer_cast<BRT>(MidCodeSequence[PC])) {
            auto brt_p = std::dynamic_pointer_cast<BRT>(MidCodeSequence[PC]);
            int judge, addr;
            addr = varTable_p->find(brt_p->judge);
            if (addr != -1) {
                judge = DataStack[addr];
            } else {
                judge = std::stoi(brt_p->judge);
            }
            if (judge) {
                PC = labels[brt_p->label];
                continue;
            }
        } else if (std::dynamic_pointer_cast<CALL>(MidCodeSequence[PC])) {
            auto call_p = std::dynamic_pointer_cast<CALL>(MidCodeSequence[PC]);
            ReturnAddrLink.push_back(PC + 1);
            PC = labels[call_p->funcName];
            //todo: finished?
            DynamicLink.push_back(DataStack.size());
            varTable_p = std::make_shared<VarTable>(varTable_p);
            for (int i = 0; i < call_p->inParams.size(); ++i) {
                int value, addr;
                addr = varTable_p->find(call_p->inParams[i]);
                if (addr != -1) {
                    value = DataStack[addr];
                } else {
                    value = std::stoi(call_p->inParams[i]);
                }
                if (call_p->formalParams[i][0] == '&') {
                    varTable_p->add(call_p->formalParams[i].substr(1), value);
                } else {
                    varTable_p->add(call_p->formalParams[i], DataStack.size());
                    DataStack.push_back(value);
                }
            }
            funcCallStack.clear();
            continue;
        } else if (std::dynamic_pointer_cast<DIV>(MidCodeSequence[PC])) {
            auto div_p = std::dynamic_pointer_cast<DIV>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(div_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(div_p->name1);
            addr = varTable_p->find(div_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(div_p->name2);
            addr = varTable_p->find(div_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a / b;
            } else {
                varTable_p->add(div_p->toStore, DataStack.size());
                DataStack.push_back(a / b);
            }
        } else if (std::dynamic_pointer_cast<EQ>(MidCodeSequence[PC])) {
            auto eq_p = std::dynamic_pointer_cast<EQ>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(eq_p->left);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(eq_p->left);
            addr = varTable_p->find(eq_p->right);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(eq_p->right);
            addr = varTable_p->find(eq_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a == b);
            } else {
                varTable_p->add(eq_p->toStore, DataStack.size());
                DataStack.push_back(a == b);
            }
        } else if (std::dynamic_pointer_cast<GEQ>(MidCodeSequence[PC])) {
            auto geq_p = std::dynamic_pointer_cast<GEQ>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(geq_p->left);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(geq_p->left);
            addr = varTable_p->find(geq_p->right);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(geq_p->right);
            addr = varTable_p->find(geq_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a >= b);
            } else {
                varTable_p->add(geq_p->toStore, DataStack.size());
                DataStack.push_back(a >= b);
            }
        } else if (std::dynamic_pointer_cast<GETA>(MidCodeSequence[PC])) {
            auto geta_p = std::dynamic_pointer_cast<GETA>(MidCodeSequence[PC]);
            int addr = varTable_p->find(geta_p->from);
            varTable_p->add(geta_p->toStore, DataStack.size());
            DataStack.push_back(addr);
        } else if (std::dynamic_pointer_cast<GETINT>(MidCodeSequence[PC])) {
            auto getint_p = std::dynamic_pointer_cast<GETINT>(MidCodeSequence[PC]);
            int value, base, offset;
            base = varTable_p->find(getint_p->base);
            offset = varTable_p->find(getint_p->offset);
            if (offset == -1) {
                offset = std::stoi(getint_p->offset);
            } else {
                offset = DataStack[offset];
            }
            std::cin >> value;
            DataStack[base + offset] = value;
        } else if (std::dynamic_pointer_cast<GRE>(MidCodeSequence[PC])) {
            auto gre_p = std::dynamic_pointer_cast<GRE>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(gre_p->left);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(gre_p->left);
            addr = varTable_p->find(gre_p->right);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(gre_p->right);
            addr = varTable_p->find(gre_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a > b);
            } else {
                varTable_p->add(gre_p->toStore, DataStack.size());
                DataStack.push_back(a > b);
            }
        } else if (std::dynamic_pointer_cast<J>(MidCodeSequence[PC])) {
            auto j_p = std::dynamic_pointer_cast<J>(MidCodeSequence[PC]);
            PC = labels[j_p->label];
            continue;
        } else if (std::dynamic_pointer_cast<LEQ>(MidCodeSequence[PC])) {
            auto leq_p = std::dynamic_pointer_cast<LEQ>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(leq_p->left);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(leq_p->left);
            addr = varTable_p->find(leq_p->right);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(leq_p->right);
            addr = varTable_p->find(leq_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a <= b);
            } else {
                varTable_p->add(leq_p->toStore, DataStack.size());
                DataStack.push_back(a <= b);
            }
        }/* else if (std::dynamic_pointer_cast<LIT>(MidCodeSequence[PC])) {
            auto lit_p = std::dynamic_pointer_cast<LIT>(MidCodeSequence[PC]);
            DataStack.push_back(lit_p->instantValue);
            StackOffset = DataStack.size();
        }*/ else if (std::dynamic_pointer_cast<LOD>(MidCodeSequence[PC])) {
            auto lod_p = std::dynamic_pointer_cast<LOD>(MidCodeSequence[PC]);
            int addr, base, offset;
            addr = varTable_p->find(lod_p->from);
            if (addr != -1) {
                base = addr;
            } else {
                //should not be -1
                std::cout << "error! can't find base" << std::endl;
                int tmp;
                std::cin >> tmp;
            }
            addr = varTable_p->find(lod_p->offset);
            if (addr != -1) {
                offset = DataStack[addr];
            } else {
                offset = std::stoi(lod_p->offset);
            }
            addr = varTable_p->find(lod_p->toStore);
            if (addr != -1) {
                DataStack[addr] = DataStack[base + offset];
            } else {
                varTable_p->add(lod_p->toStore, DataStack.size());
                DataStack.push_back(DataStack[base + offset]);
            }
        } else if (std::dynamic_pointer_cast<LODA>(MidCodeSequence[PC])) {
            auto loda_p = std::dynamic_pointer_cast<LODA>(MidCodeSequence[PC]);
            int from, offset, addr;
            addr = varTable_p->find(loda_p->from);
            if (addr != -1) {
                from = addr;
            } else {
                // not support instant num now
            }
            addr = varTable_p->find(loda_p->offset);
            if (addr != -1) {
                offset = DataStack[addr];
            } else {
                offset = std::stoi(loda_p->offset);
            }
            addr = varTable_p->find(loda_p->toStore);
            if (addr != -1) {
                DataStack[addr] = from + offset;
            } else {
                varTable_p->add(loda_p->toStore, DataStack.size());
                DataStack.push_back(from + offset);
            }
        } else if (std::dynamic_pointer_cast<LSS>(MidCodeSequence[PC])) {
            auto lss_p = std::dynamic_pointer_cast<LSS>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(lss_p->left);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(lss_p->left);
            addr = varTable_p->find(lss_p->right);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(lss_p->right);
            addr = varTable_p->find(lss_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a < b);
            } else {
                varTable_p->add(lss_p->toStore, DataStack.size());
                DataStack.push_back(a < b);
            }
        } else if (std::dynamic_pointer_cast<MINUS>(MidCodeSequence[PC])) {
            auto minus_p = std::dynamic_pointer_cast<MINUS>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(minus_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(minus_p->name1);
            addr = varTable_p->find(minus_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(minus_p->name2);
            addr = varTable_p->find(minus_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a - b;
            } else {
                varTable_p->add(minus_p->toStore, DataStack.size());
                DataStack.push_back(a - b);
            }
        } else if (std::dynamic_pointer_cast<MOD>(MidCodeSequence[PC])) {
            auto mod_p = std::dynamic_pointer_cast<MOD>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(mod_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(mod_p->name1);
            addr = varTable_p->find(mod_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(mod_p->name2);
            addr = varTable_p->find(mod_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a % b;
            } else {
                varTable_p->add(mod_p->toStore, DataStack.size());
                DataStack.push_back(a % b);
            }
        } else if (std::dynamic_pointer_cast<MULT>(MidCodeSequence[PC])) {
            auto mult_p = std::dynamic_pointer_cast<MULT>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(mult_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(mult_p->name1);
            addr = varTable_p->find(mult_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(mult_p->name2);
            addr = varTable_p->find(mult_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a * b;
            } else {
                varTable_p->add(mult_p->toStore, DataStack.size());
                DataStack.push_back(a * b);
            }
        } else if (std::dynamic_pointer_cast<NEQ>(MidCodeSequence[PC])) {
            auto neq_p = std::dynamic_pointer_cast<NEQ>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(neq_p->left);
            if (addr != -1) {
                a = DataStack[addr];
            } else {
                a = std::stoi(neq_p->left);
            }
            addr = varTable_p->find(neq_p->right);
            if (addr != -1) {
                b = DataStack[addr];
            } else {
                b = std::stoi(neq_p->right);
            }
            addr = varTable_p->find(neq_p->toStore);
            if (addr != -1) {
                DataStack[addr] = (a != b);
            } else {
                varTable_p->add(neq_p->toStore, DataStack.size());
                DataStack.push_back(a != b);
            }
        } else if (std::dynamic_pointer_cast<NOT>(MidCodeSequence[PC])) {
            auto not_p = std::dynamic_pointer_cast<NOT>(MidCodeSequence[PC]);
            int value, addr;
            addr = varTable_p->find(not_p->right);
            if (addr != -1) {
                value = DataStack[addr];
            } else {
                value = std::stoi(not_p->right);
            }
            addr = varTable_p->find(not_p->toStore);
            if (addr != -1) {
                DataStack[addr] = !value;
            } else {
                varTable_p->add(not_p->toStore, DataStack.size());
                DataStack.push_back(!value);
            }
        } else if (std::dynamic_pointer_cast<OR>(MidCodeSequence[PC])) {
            auto or_p = std::dynamic_pointer_cast<OR>(MidCodeSequence[PC]);
            int a, b, addr;
            addr = varTable_p->find(or_p->name1);
            if (addr != -1)
                a = DataStack[addr];
            else
                a = std::stoi(or_p->name1);
            addr = varTable_p->find(or_p->name2);
            if (addr != -1)
                b = DataStack[addr];
            else
                b = std::stoi(or_p->name2);
            addr = varTable_p->find(or_p->toStore);
            if (addr != -1) {
                DataStack[addr] = a || b;
            } else {
                varTable_p->add(or_p->toStore, DataStack.size());
                DataStack.push_back(a || b);
            }
        } else if (std::dynamic_pointer_cast<PINT>(MidCodeSequence[PC])) {
            std::ostream &os = *os_p;
            auto pint_p = std::dynamic_pointer_cast<PINT>(MidCodeSequence[PC]);
            int value = varTable_p->find(pint_p->name);
            if (value != -1) {
                value = DataStack[value];
            } else {
                value = std::stoi(pint_p->name);
            }
            os << value;
#ifdef DEBUG
            os << std::endl;
#endif
        } else if (std::dynamic_pointer_cast<PSTR>(MidCodeSequence[PC])) {
            std::ostream &os = *os_p;
            auto pstr_p = std::dynamic_pointer_cast<PSTR>(MidCodeSequence[PC]);
            os << pstr_p->str;
        } else if (std::dynamic_pointer_cast<PUSH>(MidCodeSequence[PC])) {
            auto push_p = std::dynamic_pointer_cast<PUSH>(MidCodeSequence[PC]);
            int addr = varTable_p->find(push_p->name);
            if (addr != -1) {
                funcCallStack.push_back(DataStack[addr]);
            } else {
                funcCallStack.push_back(std::stoi(push_p->name));
            }
//            DataStack.pop_back();
            StackOffset = DataStack.size();// is it necessary?
        } else if (std::dynamic_pointer_cast<PWRAP>(MidCodeSequence[PC])) {
            std::ostream &os = *os_p;
            os << std::endl;
        } else if (std::dynamic_pointer_cast<RET>(MidCodeSequence[PC])) {
            auto ret_p = std::dynamic_pointer_cast<RET>(MidCodeSequence[PC]);
            varTable_p = varTable_p->formerTable_p;
            PC = ReturnAddrLink.back();
            ReturnAddrLink.pop_back();
            for (; DataStack.size() != DynamicLink.back();)
                DataStack.pop_back();
            DynamicLink.pop_back();
            tempVarUseCount.pop_back();
            continue;
        } else if (std::dynamic_pointer_cast<STO>(MidCodeSequence[PC])) {
            auto sto_p = std::dynamic_pointer_cast<STO>(MidCodeSequence[PC]);
            int value, base, offset;
            base = varTable_p->find(sto_p->base);
            //base should not be -1
            if (base == -1) {
                std::cerr << "error: cant find " << sto_p->base << std::endl;
                int tmp;
                std::cin >> tmp;
                return;
            }
            offset = varTable_p->find(sto_p->offset);
            if (offset == -1) {
                offset = std::stoi(sto_p->offset);
            } else {
                offset = DataStack[offset];
            }
            value = varTable_p->find(sto_p->value);
            if (value != -1) {
                value = DataStack[value];
            } else {
                value = std::stoi(sto_p->value);
            }
            DataStack[base + offset] = value;
        }/* else if (std::dynamic_pointer_cast<STOP>(MidCodeSequence[PC])) {
            auto stop_p = std::dynamic_pointer_cast<STOP>(MidCodeSequence[PC]);
            int value = 0;
            try {
                value = std::stoi(stop_p->value);
            } catch (std::exception &e) {
                int value_addr = varTable_p->find(stop_p->value);
                value = DataStack[value_addr];
            }
            int base = varTable_p->find(stop_p->base);
            int offset = stop_p->offset;
            DataStack[base + offset] = value;
        }*/ else {
            //todo: what happened?
            std::cout << "unknown ins" << std::endl;
            int tmp;
            std::cin >> tmp;
            continue;
        }
        PC++;
    }
}

void INTERPRETER::Interpreter::setOs(std::shared_ptr<std::ostream> ostream_p) {
    if (!os_p)
        os_p = ostream_p;
}

std::string INTERPRETER::Interpreter::to_string(std::shared_ptr<VarTable> varTable_p) const {
    return std::string();//todo
}

INTERPRETER::Interpreter::Interpreter(std::vector<std::shared_ptr<PCode>> midCodeSequence,
                                      std::map<std::string, int> labels) {
    this->MidCodeSequence = std::move(midCodeSequence);
    this->labels = std::move(labels);
    this->DataStack.push_back(0);
    this->varTable_p->add("%ret", 0);
    auto ite = this->labels.find("$start");
    if (ite != this->labels.end()) {
        PC = ite->second;
    } else {
        PC = 0;
    }
}

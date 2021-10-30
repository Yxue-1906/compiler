cmake_minimum_required(VERSION 3.16)
project(src/Parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(Parser src/main.cpp
        src/Parser/Parser.cpp
        src/Parser/Parser.h
        src/Lexer/Lexer.cpp
        src/Lexer/TokenBase.cpp
        src/Lexer/TokenBase.h
        src/Output/MyOutput.cpp
        src/Output/MyOutput.h
        src/Lexer/Token/IDENFR.h
        src/Lexer/Token/INTCON.h
        src/Lexer/Token/STRCON.h
        src/Lexer/Token/MAINTK.h
        src/Lexer/Token/CONSTTK.h
        src/Lexer/Token/INTTK.h
        src/Lexer/Token/BREAKTK.h
        src/Lexer/Token/CONTINUETK.h
        src/Lexer/Token/IFTK.h
        src/Lexer/Token/ELSETK.h
        src/Lexer/Token/NOT.h
        src/Lexer/Token/AND.h
        src/Lexer/Token/OR.h
        src/Lexer/Token/WHILETK.h
        src/Lexer/Token/GETINTTK.h
        src/Lexer/Token/PRINTFTK.h
        src/Lexer/Token/RETURNTK.h
        src/Lexer/Token/PLUS.h
        src/Lexer/Token/MINU.h src/Lexer/Token/VOIDTK.h src/Lexer/Token/MULT.h src/Lexer/Token/DIV.h src/Lexer/Token/MOD.h src/Lexer/Token/LSS.h src/Lexer/Token/LEQ.h src/Lexer/Token/GRE.h src/Lexer/Token/GEQ.h src/Lexer/Token/EQL.h src/Lexer/Token/NEQ.h src/Lexer/Token/ASSIGN.h src/Lexer/Token/SEMICN.h src/Lexer/Token/COMMA.h src/Lexer/Token/LPARENT.h src/Lexer/Token/RPARENT.h src/Lexer/Token/LBRACK.h src/Lexer/Token/RBRACK.h src/Lexer/Token/LBRACE.h src/Lexer/Token/RBRACE.h src/Parser/GramNode.cpp src/Parser/GramNode.h src/Parser/GramNode/CompUnit.cpp src/Parser/GramNode/CompUnit.h src/Parser/GramNode/Decl.cpp src/Parser/GramNode/Decl.h src/Parser/GramNode/FuncDef.cpp src/Parser/GramNode/FuncDef.h src/Parser/TokenNode.cpp src/Parser/TokenNode.h src/Parser/GramNode/ConstDecl.cpp src/Parser/GramNode/ConstDecl.h src/Parser/GramNode/BType.cpp src/Parser/GramNode/BType.h src/Parser/GramNode/ConstDef.cpp src/Parser/GramNode/ConstDef.h src/Parser/GramNode/ConstExp.cpp src/Parser/GramNode/ConstExp.h src/Parser/GramNode/AddExp.cpp src/Parser/GramNode/AddExp.h src/Parser/GramNode/MulExp.cpp src/Parser/GramNode/MulExp.h src/Parser/GramNode/UnaryExp.cpp src/Parser/GramNode/UnaryExp.h src/Parser/GramNode/UnaryOp.cpp src/Parser/GramNode/UnaryOp.h src/Parser/GramNode/PrimaryExp.cpp src/Parser/GramNode/PrimaryExp.h src/Parser/GramNode/Exp.cpp src/Parser/GramNode/Exp.h src/Parser/GramNode/ConstInitVal.cpp src/Parser/GramNode/ConstInitVal.h src/Parser/GramNode/VarDecl.cpp src/Parser/GramNode/VarDecl.h src/Parser/GramNode/VarDef.cpp src/Parser/GramNode/VarDef.h src/Parser/GramNode/MainFuncDef.cpp src/Parser/GramNode/MainFuncDef.h src/Parser/GramNode/Block.cpp src/Parser/GramNode/Block.h src/Parser/GramNode/BlockItem.cpp src/Parser/GramNode/BlockItem.h src/Parser/GramNode/Stmt.cpp src/Parser/GramNode/Stmt.h src/Parser/GramNode/Cond.cpp src/Parser/GramNode/Cond.h src/Parser/GramNode/LOrExp.cpp src/Parser/GramNode/LOrExp.h src/Parser/GramNode/LAndExp.cpp src/Parser/GramNode/LAndExp.h src/Parser/GramNode/EqExp.cpp src/Parser/GramNode/EqExp.h src/Parser/GramNode/RelExp.cpp src/Parser/GramNode/RelExp.h src/Parser/GramNode/LVal.cpp src/Parser/GramNode/LVal.h src/Parser/GramNode/FuncType.cpp src/Parser/GramNode/FuncType.h src/Parser/GramNode/FuncFParams.cpp src/Parser/GramNode/FuncFParams.h src/Parser/GramNode/FuncFParam.cpp src/Parser/GramNode/FuncFParam.h src/Parser/GramNode/Number.cpp src/Parser/GramNode/Number.h src/Parser/GramNode/InitVal.cpp src/Parser/GramNode/InitVal.h src/Parser/GramNode/FuncRParams.cpp src/Parser/GramNode/FuncRParams.h src/Exception/MyException/IllegalCharException.h src/Exception/MyException/DupIdentException.h src/SymTable/SymTable.cpp src/SymTable/SymTable.h src/Exception/MyException/UndefIdentException.h src/Exception/MyException/MisMatchParmNumException.h src/Exception/MyException.cpp src/Exception/MyException.h src/Exception/MyException/OtherException.h)

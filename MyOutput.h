//
// Created by unrelated on 2021/10/8.
//

#ifndef PARSER_MYOUTPUT_H
#define PARSER_MYOUTPUT_H

#include <iostream>

class MyOutput {
public:

    template<typename First, typename ...Rest>
    static void myOutputLexer(First &&, Rest &&...);

    template<typename First, typename ...Rest>
    static void myOutputParser(First &&, Rest &&...);

    static bool setOutputOption(int type);

private:
    static bool LexerOutput;
    static bool ParserOutput;
};

template<typename First, typename ...Rest>
void MyOutput::myOutputLexer(First &&first, Rest &&...rest) {
    if (!LexerOutput)return;
    std::cout << std::forward<First>(first);
    myOutput(std::forward<Rest>(rest)...);
}

template<typename First, typename ...Rest>
void MyOutput::myOutputParser(First &&first, Rest &&...rest) {
    if (!ParserOutput)return;
    std::cout << std::forward<First>(first);
    myOutput(std::forward<Rest>(rest)...);
}

#endif //PARSER_MYOUTPUT_H

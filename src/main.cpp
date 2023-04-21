#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Statement.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char *argv[]) {

    //validate size of arguments
    if (argc < 2) {
        cerr << "Unexpected arguments " << endl;
        return 1;
    }
    //validate file exists
    ifstream is(argv[1]);
    if (!is) {
        cerr << "Could not open file " << argv[1] << endl;
        return 1;
    }
    //read file
    is.seekg(0, ifstream::end);
    size_t fileSize = is.tellg();
    is.seekg(0, ifstream::beg);
    char programText[fileSize + 1];
    size_t index = 0;
    char c;
    while (is.get(c)) {
        programText[index++] = c;
    }
    programText[index] = '\0';

    try {
        Lexer lexer(programText);
        Parser parser(lexer);
        vector<Statement> *programStack = parser.parse();
        Interpreter interpreter;
        interpreter.interpret(programStack);
        delete programStack;
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
    }
    return 0;
}
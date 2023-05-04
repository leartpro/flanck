#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;


int main(int argc, char *argv[]) {

    //validate size of arguments
    if (argc < 3) {
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
        parser.parse();
        CMDInterpreterObserver observer = CMDInterpreterObserver();
        unordered_map<int, StackConstraint> constraints = {};
        unordered_map<int, NotificationChangeType> notifications = {};
        InterpreterOptions options(10, 100000, 10, 2, constraints, notifications);
        Interpreter interpreter(parser, observer, options);
        interpreter.pushStack(0,Stack::fromBinaryString("0"));
        interpreter.start();
        cout << interpreter.getStack(1).toString();
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
    }
    return 0;
}
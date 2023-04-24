#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Statement.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Stack.h"

using namespace std;

int main(int argc, char *argv[]) {

    //validate size of arguments
    if (argc < 2) {
        cerr << "Unexpected amount of arguments " << endl;
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

    bool asBinary;
    int inputPos = 2;
    if(argv[2][0] == '-' && argv[2][1] == 'a') {
        asBinary = false;
        inputPos = 3;
    } else if(argv[2][0] == '-' && argv[2][1] == 'b') {
        asBinary = true;
        inputPos = 3;
    }

    vector<Stack> stacks;
    stacks.reserve(argc - 2);
    for (int pos = inputPos; pos < argc; pos++) {
        Stack stack = asBinary ?
                Stack::fromBinaryString(argv[pos]) :
                Stack::fromString(argv[pos]);
        stacks.push_back(stack);
    }

    try {
        Lexer lexer(programText);
        Parser parser(lexer);
        Interpreter interpreter(parser, stacks);
        interpreter.interpret();
        cout << interpreter.getOutputStack().toBinaryString() << endl;
        cout << interpreter.getOutputStack().toString();
    }
    catch (exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
        return 1;
    }
    return 0;
}
#include <iostream>
#include <fstream>
#include "Lexer.h"
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

    bool inputAsBinary = true;
    bool outputAsBinary = true;
    int inputPos = 2;
    if (argv[2][0] == '-' && argv[2][1] == 'a') {
        inputAsBinary = false;
        inputPos++;
    } else if (argv[2][0] == '-' && argv[2][1] == 'b') {
        inputAsBinary = true;
        inputPos++;
    }

    if (argv[3][0] == '-' && argv[3][1] == 'a') {
        outputAsBinary = false;
        inputPos++;
    } else if (argv[3][0] == '-' && argv[3][1] == 'b') {
        outputAsBinary = true;
        inputPos++;
    }

    vector<Stack> stacks;
    stacks.reserve(argc - 2);
    for (int pos = inputPos; pos < argc; pos++) {
        Stack stack = inputAsBinary ?
                      Stack::fromBinaryString(argv[pos]) :
                      Stack::fromString(argv[pos]);
        stacks.push_back(stack);
    }

    try {
        Lexer lexer(programText);
        Parser parser(lexer);
        Interpreter interpreter(parser, stacks);
        interpreter.interpret();
        cout << (
                outputAsBinary ?
                interpreter.getOutputStack().toBinaryString() :
                interpreter.getOutputStack().toString()
        );
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
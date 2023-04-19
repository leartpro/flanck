#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

/**
 *
 */
struct Stack {
    vector<bool> stack;

    Stack() = default;

    /**
     *
     * @param stack
     */
    explicit Stack(vector<bool> stack) {
        this->stack = std::move(stack);
    }

    /**
     *
     * @return
     */
    [[nodiscard]] int size() const {
        return int(stack.size());
    }

    /**
     *
     * @param index
     * @return
     */
    bool get(int index) {
        return stack[index];
    }

    /**
     *
     * @param value
     */
    void add(bool value) {
        stack.push_back(value);
    }

    /**
     *
     * @param from
     * @param to
     */
    void remove(int n) {
        stack.resize(stack.size() - n);
    }

    /**
     *
     */
    void clear() {
        stack.clear();
    }

    /**
     *
     * @param input
     */
    void pushUserInput(char *input) {
        bool is_binary = true;
        for (int i = 0; i < ::strlen(input); ++i) {
            if (input[i] != '0' && input[i] != '1') {
                is_binary = false;
                break;
            }
        }
        if (is_binary) {
            for (int i = int(::strlen(input)) - 1; i >= 0; i--) {
                stack.push_back(input[i] == '0');
            }
        } else {
            for (int i = 0; i < ::strlen(input); i++) {
                for (int j = 0; j < 8; j++) {
                    stack.push_back((input[i] & (1 << j)) == 0);
                }
            }
        }
    }

    /**
     *
     */
    void print() {
        int size = int(stack.size() - (stack.size() % 8));
        for (int i = 0; i < size; i += 8) {
            std::bitset<8> byte;
            for (int j = 0; j < 8; j++) byte[7 - j] = (!stack[i + j]);
            cout << char(byte.to_ulong());
        }
    }
};

/**
 *
 */
struct Statement {
    vector<Stack> conditions, instructions;
    bool inputRequest, runtimePrint;

    /**
     *
     * @param conditions
     * @param instructions
     * @param inputRequest
     * @param runtimePrint
     */
    Statement(vector<Stack> conditions, vector<Stack> instructions, bool inputRequest, bool runtimePrint) {
        this->conditions = std::move(conditions);
        this->instructions = std::move(instructions);
        this->inputRequest = inputRequest;
        this->runtimePrint = runtimePrint;
    }

    /**
     *
     * @param stacks
     * @return
     */
    bool execute(vector<Stack> &stacks) {
        if (!validateConditions(stacks)) {
            if (inputRequest) {
                handleInputRequest(stacks);
            } else {
                removeConditionsFromStacks(stacks);
                return false;
            }
        }
        bool stackChanged = removeConditionsFromStacks(stacks);
        if (executeInstructions(stacks)) stackChanged = true;
        if (runtimePrint) stacks[1].print();
        return stackChanged;
    }


private:
    /**
     *
     * @param stacks
     * @return
     */
    bool executeInstructions(vector<Stack> &stacks) {
        bool stackChanged = false;
        for (int stack_index = 0; stack_index < instructions.size(); stack_index++) {
            for (int stack_position = int(instructions[stack_index].size());
                 stack_position > 0; stack_position--) {
                stacks[stack_index].add(instructions[stack_index].get(stack_position - 1));
                stackChanged = true;
            }
        }
        return stackChanged;
    }

    /**
     *
     * @param stacks
     * @return
     */
    bool removeConditionsFromStacks(vector<Stack> &stacks) {
        for (int stack_index = 0; stack_index < conditions.size(); stack_index++) {
            if (stacks[stack_index].size() > conditions[stack_index].size()) {
                stacks[stack_index].remove(
                        conditions[stack_index].size()
                );
            } else stacks[stack_index].clear();
        }
        return !conditions.empty();
    }

    /**
     *
     * @param stacks
     * @return
     */
    bool validateConditions(vector<Stack> &stacks) {
        for (int stack_index = 0; stack_index < conditions.size(); stack_index++) {
            if (conditions[stack_index].size() > stacks[stack_index].size()) {
                return false;
            }
            for (int stack_position = 0; stack_position < conditions[stack_index].size(); stack_position++) {
                if (conditions[stack_index].get(stack_position) !=
                    stacks[stack_index].get(stacks[stack_index].size() - 1 - stack_position)) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     *
     * @param stacks
     */
    void handleInputRequest(vector<Stack> &stacks) {
        while (!validateConditions(stacks)) {
            const int BUFFER_SIZE = 1024;
            char buffer[BUFFER_SIZE];
            fgets(buffer, BUFFER_SIZE, stdin);
            char **input = new char *[BUFFER_SIZE];
            int i = 0;
            char *chars_array = strtok(buffer, " ");
            while (chars_array) {
                input[i] = chars_array;
                i++;
                chars_array = strtok(nullptr, " ");
            }
            for (Stack stack: stacks) {
                for (int pos = 0; pos < ::strlen(buffer); pos++) {
                    stack.pushUserInput(input[pos]);
                }
            }
        }
    }
};

/**
 *
 * @param programText
 * @return
 */
tuple<vector<Statement>, int, bool> buildProgramStack(const char *programText) {
    vector<Statement> programStack;
    int position = 0;
    int total_stacks_count = 0;
    while (position < ::strlen(programText)) {
        vector<Stack> read;
        vector<Stack> write;
        bool valueAllowed = false;
        bool hasDivider = false;
        bool runtimePrint = false;
        bool inputRequest = false;
        Stack stack;
        switch (programText[position]) {
            case '<':
                runtimePrint = true;
                position++;
                break;
            case '>':
                inputRequest = true;
                position++;
                break;
        }
        while (programText[position] != '\n' && position < ::strlen(programText)) {
            switch (programText[position]) {
                case '[':
                    if (valueAllowed) {
                        cerr << "Syntax error " << endl;
                        return {programStack, total_stacks_count, false};
                    }
                    stack.clear();
                    valueAllowed = true;
                    break;
                case ']':
                    if (!valueAllowed) {
                        cerr << "Syntax error " << endl;
                        return {programStack, total_stacks_count, false};
                    }
                    valueAllowed = false;
                    if (hasDivider) write.emplace_back(stack);
                    else read.emplace_back(stack);
                    break;
                case ':':
                    if (valueAllowed) {
                        cerr << "Syntax error " << endl;
                        return {programStack, total_stacks_count, false};
                    }
                    valueAllowed = false;
                    hasDivider = true;
                    break;
                case '0':
                case '1':
                    if (!valueAllowed) {
                        cerr << "Syntax error " << endl;
                        return {programStack, total_stacks_count, false};
                    }
                    while (position < ::strlen(programText)) {
                        stack.add(programText[position] == '0');
                        if (programText[position + 1] == '0' || programText[position + 1] == '1') {
                            ++position;
                        } else {
                            break;
                        }
                    }
                    break;
                case '#':
                    if (valueAllowed) {
                        cerr << "Syntax error " << endl;
                        return {programStack, total_stacks_count, false};
                    }
                    while (position < sizeof(programText)) {
                        position++;
                        if (programText[position + 1] != '\n') {
                            position++;
                        } else {
                            break;
                        }
                    }
                    break;
            }
            position++;
        }
        position++;
        if (valueAllowed) {
            cerr << "Syntax error " << endl;
            return {programStack, total_stacks_count, false};
        }
        programStack.emplace_back(read, write, inputRequest, runtimePrint);
        if (max(read.size(), write.size()) > total_stacks_count) {
            total_stacks_count = int(max(read.size(), write.size()));
        }
    }
    return {programStack, total_stacks_count, true};
}

/**
 *
 * @param argc darf nicht kleiner als zwei sein
 * @param argv die .flanck Datei und optional weitere Argumente, wobei jedes Argument Binär auf den entsprechenden Keller gelegt wird
 * @return 0 wenn es zu keinem Fehler gekommen ist
 */
int main(int argc, char **argv) {
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
    //initialize stacks
    vector<Stack> stacks;
    for (int pos = 2; pos < argc; pos++) {
        Stack stack;
        stack.pushUserInput(argv[pos]);
        stacks.push_back(stack);
    }
    //lexing and parsing
    auto [programStack, total_stacks_count, validSyntax] = buildProgramStack(programText);
    if (!validSyntax) return 1;
    //initialize all stacks
    if(total_stacks_count > stacks.size()) {
        stacks.resize(total_stacks_count);
    }
    while (stacks.size() < total_stacks_count) stacks.emplace_back();
    //executes program stack / interpret
    bool stackChanged;
    do {
        stackChanged = false;
        for (Statement statement: programStack) {
            if (statement.execute(stacks)) {
                stackChanged = true;
            }
        }
    } while (stackChanged);
    //print program output
    if (stacks.size() < 2) return 0;
    stacks[1].print();
    return 0;
}
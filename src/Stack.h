#ifndef FLANCK_STACK_H
#define FLANCK_STACK_H

#include <utility>
#include <vector>

using namespace std;
struct Stack {
    explicit Stack(vector<bool> stack) {
        this->stack = std::move(stack);
    }
    vector<bool> stack;

};
#endif //FLANCK_STACK_H

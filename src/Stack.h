#ifndef FLANCK_STACK_H
#define FLANCK_STACK_H

#include <utility>
#include <vector>

using namespace std;
struct Stack {
    explicit Stack(vector<bool> stack) {
        this->data_ = std::move(stack);
    }
    vector<bool> data_;

    bool endsWith(Stack other) {
        if(other.data_.empty() && data_.empty()) {
            return true;
        }
        if(other.data_.size() > data_.size()) {
            return false;
        }
        return std::equal(data_.end() - int(other.data_.size()), data_.end(), other.data_.end());
    }

    void push(Stack other) {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end() );
    }

    void remove(const Stack& howMuch) {
        data_.resize(data_.size() - howMuch.data_.size());
    }
};
#endif //FLANCK_STACK_H
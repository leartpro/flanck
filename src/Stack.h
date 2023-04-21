#ifndef FLANCK_STACK_H
#define FLANCK_STACK_H

#include <utility>
#include <vector>
#include <bitset>

using namespace std;

struct Stack {
    explicit Stack(vector<bool> stack) {
        this->data_ = std::move(stack);
    }

    vector<bool> data_;
public:
    static Stack fromString(const string& s) {
        vector<bool> data;
        for (char i : s) {
            for (int j = 7; j >= 0; j--) {
                data.push_back((i & (1 << j)) == 0);
            }
        }
        return Stack(data);
    }

    static Stack fromBinaryString(string s) {
        vector<bool> data;
        for (int i = int(s.length()) - 1; i >= 0; i--) {
            data.push_back(s[i] == '1');
        }
        return Stack(data);
    }

    static Stack empty() {
        return Stack(vector<bool>());
    }

    __attribute__((always_inline)) inline bool endsWith(Stack other) {
        if (other.data_.empty() && data_.empty()) {
            return true;
        }
        if (other.data_.size() > data_.size()) {
            return false;
        }
        return std::equal(data_.end() - int(other.data_.size()), data_.end(), other.data_.end());
    }

    __attribute__((always_inline)) inline void push(Stack other) {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    __attribute__((always_inline)) inline void remove(const Stack &howMuch) {
        data_.resize(data_.size() - howMuch.data_.size());
    }

    [[nodiscard]] __attribute__((always_inline)) inline bool isEmpty() const {
        return data_.empty();
    }

    string toBinaryString() {
        string result;
        for (auto i = 0; i < data_.size(); i += 1) {
            result += data_[i] ? '1' : '0';
        }
        return result;
    }

    string toString() {
        string result;
        int size = int(data_.size() - (data_.size() % 8));
        for (int i = 0; i < size; i += 8) {
            std::bitset<8> byte;
            for (int j = 0; j < 8; j++) byte[7 - j] = (!data_[i + j]);
            result += char(byte.to_ulong());
        }
        return result;
    }
};

#endif //FLANCK_STACK_H
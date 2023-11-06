#ifndef FLANCK_STACK_H
#define FLANCK_STACK_H

#include <utility>
#include <vector>
#include <bitset>

using namespace std;

/**
 * A Stack contains a order of bytes (represented as booleans>
 */
struct Stack {
    vector<bool> data_;

    /**
     * Initializes with the given data.
     * @param stack
     */
    explicit Stack(vector<bool> stack) {
        this->data_ = std::move(stack);
    }

    /**
     * Initializes an empty Stack.
     */
    explicit Stack() {
        this->data_ = vector<bool>();
    }

    /**
     * Creates a Stack from an Ascii-String.
     * @param s the string to build the Stack from.
     * @return the initialized Stack.
     */
    static Stack fromString(const string &s) {
        if (std::equal(s.begin(), s.end(), "_")) return Stack();
        vector<bool> data;
        for (char i: s) {
            for (int j = 7; j >= 0; j--) {
                data.push_back((i & (1 << j)) != 0);
                //TODO: für == 0 kommt für s: 0 -> 11001111 und für == 1 kommt für s: 0 -> 00000000
                // es sollte aber für s: 0 -> 00110000
                //TODO: gibt result genau falschrum
            }
        }
        return Stack(data);
    }

    /**
     * Creates a Stack from a Binary-String.
     * @param s the string to build the Stack from.
     * @return the initialized Stack.
     */
    static Stack fromBinaryString(string s) {
        if (std::equal(s.begin(), s.end(), "_")) return Stack();
        vector<bool> data;
        for (int i = int(s.length()) - 1; i >= 0; i--) {
            data.push_back(s[i] == '1');
        }
        return Stack(data);
    }

    /**
     * Checks if the current stack ends with another stack
     * by comparing the elements of the current stack with the elements of the other stack.
     * @param other
     * @return true, if both Stacks are emtpy or
     * and false, if the other-Stack contains more elements than the current one.
     */
    __attribute__((always_inline)) inline bool endsWith(Stack other) {
        if (other.isEmpty() && this->isEmpty()) {
            return true;
        }
        if (other.height() > this->height()) {
            return false;
        }
        for (int i = 1; i <= other.height(); i++) {
            if (this->data_[this->height() - i] != other.data_[other.height() - i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Appends the given Stack to the current Stack.
     * @param other the other Stack.
     */
    __attribute__((always_inline)) inline void push(Stack other) {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    /**
     * Removes elements from the top of the current Stack.
     * @param amount the amount of elements to remove
     */
    __attribute__((always_inline)) inline void remove(const int& amount) {
        data_.resize(data_.size() - amount);
    }

    /**
     * Returns a Binary-String of the current Stack.
     * @return a string, representing the current Stack.
     */
    string toBinaryString() {
        string result;
        for (auto i = 0; i < data_.size(); i += 1) {
            result += data_[i] ? '1' : '0';
        }
        return result;
    }

    /**
     * Returns a Ascii-String of the current Stack.
     * @return a string, representing the current Stack.
     */
    string toString() {
        string result;
        int size = int(data_.size() - (data_.size() % 8));
        for (int i = 0; i < size; i += 8) {
            std::bitset<8> byte;
            for (int j = 0; j < 8; j++) byte[7 - j] = (data_[i + j]);
            result += char(byte.to_ulong());
        }
        return result;
    }

    /**
     * Returns if the current Stack contains elements.
     * @return true, if the current Stack is empty, otherwise false.
     */
    __attribute__((always_inline)) inline bool isEmpty() const {
        return data_.empty();
    }

    /**
     * Returns the height/size of the current Stack.
     * @return an integer indicating the number of elements.
     */
    __attribute__((always_inline)) inline int height() const {
        return int(data_.size());
    }

    /**
     * Returns the end of the current Stack.
     * @return the bit-iterator of the end of the current Stack.
     */
    __attribute__((always_inline)) inline __bit_iterator<std::vector<bool, std::allocator<bool> >, false> end() {
        return data_.end();
    }

    /**
     * Returns the begin of the current Stack.
     * @return the bit-iterator of the begin of the current Stack.
     */
    __attribute__((always_inline)) inline __bit_iterator<std::vector<bool, std::allocator<bool> >, false> begin() {
        return data_.begin();
    }
};
#endif //FLANCK_STACK_H
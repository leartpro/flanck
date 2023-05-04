#ifndef FLANCK_STACK_H
#define FLANCK_STACK_H

#include <utility>
#include <vector>
#include <bitset>

using namespace std;

/**
 *
 */
struct Stack {
    vector<bool> data_;

    /**
     *
     * @param stack
     */
    explicit Stack(vector<bool> stack) {
        this->data_ = std::move(stack);
    }

    /**
     *
     */
    explicit Stack() {
        this->data_ = vector<bool>();
    }

    /**
     *
     * @param s
     * @return
     */
    static Stack fromString(const string &s) {
        if (std::equal(s.begin(), s.end(), "_")) return Stack();
        vector<bool> data;
        for (char i: s) {
            for (int j = 7; j >= 0; j--) {
                data.push_back((i & (1 << j)) == 0);
            }
        }
        return Stack(data);
    }

    /**
     *
     * @param s
     * @return
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
     *
     * @param other
     * @return
     */
    __attribute__((always_inline)) inline bool endsWith(Stack other) {
        if (other.isEmpty() && this->isEmpty()) {
            return true;
        }
        if (other.height() > this->height()) {
            return false;
        }
        const auto a = this->end() - other.height();
        const auto b = this->end() - other.height();

        return std::equal(this->begin(), this->begin() + other.height(), other.begin());
    }

    /**
     *
     * @param other
     */
    __attribute__((always_inline)) inline void push(Stack other) {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    /**
     *
     * @param howMuch
     */
    __attribute__((always_inline)) inline void remove(const Stack &howMuch) {
        data_.resize(data_.size() - howMuch.data_.size());
    }

    /**
     *
     * @return
     */
    string toBinaryString() {
        string result;
        for (auto i = 0; i < data_.size(); i += 1) {
            result += data_[i] ? '1' : '0';
        }
        return result;
    }

    /**
     *
     * @return
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
     *
     * @return
     */
    __attribute__((always_inline)) inline bool isEmpty() const {
        return data_.empty();
    }

    /**
     *
     * @return
     */
    __attribute__((always_inline)) inline int height() const {
        return int(data_.size());
    }

    /**
     *
     * @return
     */
    __attribute__((always_inline)) inline __bit_iterator<std::vector<bool, std::allocator<bool> >, false> end() {
        return data_.end();
    }

    __attribute__((always_inline)) inline __bit_iterator<std::vector<bool, std::allocator<bool> >, false> begin() {
        return data_.begin();
    }

};

#endif //FLANCK_STACK_H
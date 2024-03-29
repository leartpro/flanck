#include "Lexer.h"

using namespace std;

Token Lexer::getNextToken() {
    while (position_ < input_.size()) {
        switch (input_[position_]) {
            case '[':
                ++position_;
                return Token::Open;
            case ']':
                ++position_;
                return Token::Close;
            case '0':
                ++position_;
                return Token::Zero;
            case '1':
                ++position_;
                return Token::One;
            case ':':
                ++position_;
                return Token::Divider;
            case '\n':
                ++position_;
                return Token::Eol;
            default:
                //every non Token-Terminal is ignored
                ++position_;
                continue;
        }
    }
    //If position has reached the end.
    return Token::Eof;
}
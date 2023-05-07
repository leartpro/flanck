#include "Lexer.h"

using namespace std;

Token Lexer::getNextToken() {
    while (position_ < input_.size()) {
        switch (input_[position_++]) {
            case '[':
                return Token::Open;
            case ']':
                return Token::Close;
            case '0':
                return Token::Zero;
            case '1':
                return Token::One;
            case ':':
                return Token::Divider;
            case '\n':
                return Token::Eol;
        }
    }
    return Token::Eof;
}
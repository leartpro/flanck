#ifndef FLANCK_TOKEN_H
#define FLANCK_TOKEN_H
/**
 * Tokens of the language Flanck.
 * every other Token will be ignored.
 */
enum Token {
    Eol,     // \n
    Open,    // [
    Close,   // ]
    Zero,    // 0
    One,     // 1
    Divider, // :
    Eof      // End-Of-File
};
#endif //FLANCK_TOKEN_H

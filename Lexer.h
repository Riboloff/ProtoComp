#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/regex.hpp>

#include "Token.h"
#include "ReadFile.h"

using namespace std;

class Lexer {
private:
    Token token_;
    vector <Token> tokens_;
    ReadFile *text_;
    void _findWordQuotesContext (string &word, char pair_symbol);

public:
    Lexer(const char*);
    Token nextToken(void);
    Token getToken(void);
    bool checkEndFile(void);
    unsigned int getPointerSymbol(void);
    void setPointerSymbol(unsigned int);
    void printAllTokens(void);
};


Lexer::Lexer(const char* fileName) {
    text_ = new ReadFile(fileName);
}

Token Lexer::getToken (void) {
    return token_;
}

Token Lexer::nextToken (void) {
    string word;

    while (!text_->pushPointer()) {
        char symbol = text_->getCurSymbol();

        if (symbol == '\'' or symbol == '"') {
            if (word.length() == 0) {
                word.push_back(symbol);
                _findWordQuotesContext(word, symbol);
            } else {
                text_->pullPointer();
            }
            break;
        }
        if (symbol == '(' or symbol == ')' or symbol == '[' or symbol == ']') {
            if (word.length() == 0) {
                word.push_back(symbol);
            } else {
                text_->pullPointer();
            }
            break;

        }
        if (symbol == ' ' or symbol == '\n') {
            if (word.length() == 0) {
                continue;
            }
            break;
        }
        word.push_back(symbol);
    }

    if (text_->checkEndFile()) {
        throw invalid_argument("nextToken: EOF");
    }
    token_.addWord(word);
    tokens_.push_back(token_); //Только для отладки, этот массив не верен,
                               //т.к. можно отказывать позицию указателя

    return getToken();
}

void Lexer::_findWordQuotesContext (string &word, char pair_symbol) {
    while(!text_->pushPointer()) {
        char symbol = text_->getCurSymbol();
        if (symbol == pair_symbol) {
            word.push_back(symbol);
            return;
        }
        word.push_back(symbol);
    }
}

bool Lexer::checkEndFile(void) {
    if (text_->checkEndFile()) return true;
    return false;
}

unsigned int Lexer::getPointerSymbol (void) {
        return text_->getPointerSymbol();
}

void Lexer::setPointerSymbol (unsigned int pointer) {
    text_->setPointerSymbol(pointer);
}

void Lexer::printAllTokens(void) {
    for(vector<Token>::iterator tr = tokens_.begin(); tr != tokens_.end(); tr++) {
        Token tok = *tr;
        cout << "Value=" <<tok.getValue() << "\t";
        cout << "Type=" <<tok.getType() << endl;
    }
}

#endif // LEXER_H

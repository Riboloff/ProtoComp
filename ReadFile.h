#ifndef READFILE_H
#define READFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <boost/regex.hpp>
#include "Token.h"

using namespace std;
class ReadFile {
private:
    char symbol_;
    unsigned int pointerSymbol_;
    string text_;
    Token token_;
    int endText_;
    vector <Token> tokens_;
    map <string, int> tableSymbol_;
    void _findWordQuotesContext (string &word, char pair_symbol);
    int _pullPointer(void);
    int _pushPointer(void);
    char getCurSymbol(void);

public:
    ReadFile(const char* fileName);
    Token nextToken(void);
    Token getToken(void);
    bool checkEndFile(void);
    unsigned int getPointerSymbol(void);
    void setPointerSymbol(unsigned int);
    void printAllTokens(void);
};


ReadFile::ReadFile(const char* fileName) {
    ifstream fin(fileName);
    char ch = fin.get();
    while(!fin.eof()) {
        text_ += ch;
        ch = fin.get();
    }
    fin.close();

    pointerSymbol_ = -1;
    endText_ = 0;
}

Token ReadFile::getToken (void) {
    return token_;
}

Token ReadFile::nextToken (void) {
    string word;

    while (!_pushPointer()) {
        char symbol = getCurSymbol();
        
        if (symbol == '\'' or symbol == '"') {
            if (word.length() == 0) {
                word.push_back(symbol);
                _findWordQuotesContext(word, symbol);
            } else {
                _pullPointer();
            }
            break;
        }
        if (symbol == '(' or symbol == ')' or symbol == '[' or symbol == ']') {
            if (word.length() == 0) {
                word.push_back(symbol);
            } else {
                _pullPointer();
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

    //cout << word << endl;
    if (endText_) {
        throw invalid_argument("nextToken: EOF");
    }
    token_.addWord(word);
    tokens_.push_back(token_); //Только для отладки, этот массив не верен,
                               //т.к. можно отказывать позицию указателя

    return getToken();
}

void ReadFile::_findWordQuotesContext (string &word, char pair_symbol) {
    while(!_pushPointer()) {
        char symbol = getCurSymbol();
        if (symbol == pair_symbol) {
            //предусмотреть экранирование
            word.push_back(symbol);
            return;
        }
        word.push_back(symbol);
    }
}

int ReadFile::_pushPointer(void) {
    if(++pointerSymbol_ <= text_.length()) {
        symbol_ = text_[pointerSymbol_];
        return 0;        
    } else {
        pointerSymbol_--;
        endText_ = 1;
        return 1;
    }
}

int ReadFile::_pullPointer(void) {
    if(pointerSymbol_ > 0) {
        --pointerSymbol_;
        symbol_ = text_[pointerSymbol_];
        return 0;
    } else {
        return 1;
    }
}

bool ReadFile::checkEndFile(void) {
    if (endText_) return true;
    return false;
}

char ReadFile::getCurSymbol (void) {
        this->symbol_ = text_[pointerSymbol_];
        return this->symbol_;
}

unsigned int ReadFile::getPointerSymbol (void) {
        return this->pointerSymbol_;
}

void ReadFile::setPointerSymbol (unsigned int pointer) {
        if (this->pointerSymbol_ >= pointer) {
            this->pointerSymbol_ = pointer;
            this->symbol_ = text_[this->pointerSymbol_];
        } else {
            cout << "DEBAG: попытка установить невалидный указатель"<< endl;
        }
}


void ReadFile::printAllTokens(void) {
    for(vector<Token>::iterator tr = tokens_.begin(); tr != tokens_.end(); tr++) {
        Token tok = *tr;
        cout << "Value=" <<tok.getValue() << "\t";
        cout << "Type=" <<tok.getType() << endl;
    }
}
#endif // READFILE_H

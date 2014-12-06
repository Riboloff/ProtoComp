#ifndef READFILE_H
#define READFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/regex.hpp>
#include "Token.h"

using namespace std;

class ReadFile {
private:
    string text_;
    char symbol_;
    int endText_;
    int pointerSymbol_;
public:
    ReadFile(const char* fileName);
    int pullPointer(void);
    int pushPointer(void);
    char getCurSymbol(void);
    void setCurSymbol(void);
    int getPointerSymbol(void);
    void setPointerSymbol(int);
    bool checkEndFile(void);

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

int ReadFile::pullPointer(void) {
    if(pointerSymbol_ > 0) {
        --pointerSymbol_;
        symbol_ = text_[pointerSymbol_];
        return 0;
    } else {
        return 1;
    }
}

int ReadFile::pushPointer(void) {
    if(++pointerSymbol_ <=int(text_.length() ) ) {
        symbol_ = text_[pointerSymbol_];
        return 0;
    } else {
        pointerSymbol_--;
        endText_ = 1;
        return 1;
    }
}

char ReadFile::getCurSymbol (void) {
    this->symbol_ = text_[pointerSymbol_];
    return this->symbol_;
}

void ReadFile::setCurSymbol(void) {
   this->symbol_ = text_[pointerSymbol_];
}

int ReadFile::getPointerSymbol (void) {
        return this->pointerSymbol_;
}

void ReadFile::setPointerSymbol (int pointer) {
        if (this->pointerSymbol_ >= pointer) {
            this->pointerSymbol_ = pointer;
            this->setCurSymbol();
        } else {
            cout << "DEBAG: попытка установить невалидный указатель"<< endl;
        }
}

bool ReadFile::checkEndFile(void) {
    if (this->endText_) return true;
    return false;
}

#endif //READFILE_H

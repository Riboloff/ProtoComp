#ifndef TABLESYMBOL_H
#define TABLESYMBOL_H

#include <iostream>
#include <map>
#include <boost/regex.hpp> //Почему invalid_argument не работает без этой либы?
#include "Token.h"
#include "Notion.h"

using namespace std;


class TableSymbol {
//typedef map <string, list<list<Token> > > TableNotions;
//typedef map <string, list <Sentence> > TableNotions;
typedef map <string, Notion> TableNotions;

private:
    TableNotions tableSymbol_;

public:
    TableSymbol(void);
    void putNotion(string) throw (invalid_argument);
    void putSentence(Sentence);
    void dumpNotions(void);
    bool checkSymbol(string);
    string curSymbol_;
    TableNotions getNotions(void);
};

TableSymbol::TableSymbol(void) {
//    numberLast_ = 0; //Надо вспомнить зачем храним последний
}

void TableSymbol::putNotion(string key) throw (invalid_argument){
    //vector <vector <Token> > tmp;
    Notion tmp;
    if(!checkSymbol(key)) {
        //this->numberLast_++; //И зачем инкрементим?
        this->tableSymbol_[key] = tmp;
        this->curSymbol_ = key;
    } else {
        throw invalid_argument("dublicate word");
    }
    return;// this->tableSymbol_[key];
}

bool TableSymbol::checkSymbol(string symbol) {
    TableNotions::iterator it = this->tableSymbol_.find(symbol);
    if (it == tableSymbol_.end()) return false;
    return true;
}

//void TableSymbol::putSentence(list <Token> sentence) {
void TableSymbol::putSentence(Sentence sentence) {
    //vector <vector <Token> > tmp =  this->tableSymbol_[curSymbol_];
    //tmp.push_back(sentence);
    //Notion tmp;
    //Sentence sentence;
    //sentence.setSyntax(string);
    this->tableSymbol_[curSymbol_].pushBackSentence(sentence);
}

void TableSymbol::dumpNotions(void) {

    for (map <string, Notion>::iterator iter= this->tableSymbol_.begin(); iter != tableSymbol_.end(); iter++) {
        string key = iter->first;
        Notion value = iter->second;

        cout << key << ":"<< endl;
        list <Sentence> *sentences = value.getSentences();

        for (list <Sentence>::iterator iter2= sentences->begin(); iter2 != sentences->end(); iter2++) {
            cout << "\tString:" << endl;
            vector <Token> *syntax = iter2->getSyntax();
            for (vector <Token>::iterator iter3= syntax->begin(); iter3 != syntax->end(); iter3++) {
                cout <<"\t\t"<< iter3->getValue() << endl;
            }
        }
   }
}

map <string, Notion > TableSymbol::getNotions(void) {
    return this->tableSymbol_;
}


#endif // TABLESYMBOL_H

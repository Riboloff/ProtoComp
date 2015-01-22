#ifndef SENTENCE_H
#define SENTENCE_H

using namespace std;
#include <list>
#include <vector>

#include "Token.h"

class Sentence {
private:
    //list <string> syntax;
    vector <Token> syntax;
    vector <Token> semantic;

public:
    //list <string>* getSyntax(void);
    vector <Token>* getSyntax(void);
    vector <Token>* getSemantic(void);
    //void setSyntax(list <string>);
    void setSyntax(vector <Token>);
    void setSemantic(vector <Token>);
    void dumpSentenceSyntax(void);
};

//list <string>* Sentence::getSyntax(void) {
vector <Token>* Sentence::getSyntax(void) {
    return &syntax;
}

vector <Token>* Sentence::getSemantic(void) {
    return &semantic;
}
//void Sentence::setSyntax(list <string> listParam) {
void Sentence::setSyntax(vector <Token> listParam) {
    this->syntax = listParam;
}

void Sentence::setSemantic(vector <Token> listParam) {
    this->semantic = listParam;
}

void Sentence::dumpSentenceSyntax(void) {
    cout << "Syntax:" << endl;
    for (vector <Token>::iterator iter = this->syntax.begin(); iter != this->syntax.end(); ++iter) {
        Token token = *iter;
        cout << "\t" << token.getType() << ":\t" << token.getValue() << endl;
    }
}

#endif // SENTENCE_H

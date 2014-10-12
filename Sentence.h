#ifndef SENTENCE_H
#define SENTENCE_H

using namespace std;
#include <list>

class Sentence {
private:
    list <string> syntax;
    list <string> semantic;

public:
    list <string>* getSyntax(void);
    list <string>* getSemantic(void);
    void setSyntax(list <string>);
    void setSemantic(list <string>);
};

list <string>* Sentence::getSyntax(void) {
    return &syntax;
}

list <string>* Sentence::getSemantic(void) {
    return &semantic;
}
void Sentence::setSyntax(list <string> listParam) {
    this->syntax = listParam;
}

void Sentence::setSemantic(list <string> listParam) {
    this->semantic = listParam;
}
#endif // SENTENCE_H

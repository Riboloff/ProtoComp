#ifndef NOTION_H
#define NOTION_H
#include <vector>
#include <map>

#include "Sentence.h"

using namespace std;

class Notion {
    private:
        list <string> integration;
        string name;
        list <string> defferenciation;
        list <Sentence> sentences;

    public:
        string getName();
        void setName(string);
        void setDefferenciation (list <string>);
        void setIntegration (list <string>);
        list <string> * getDefferenciation(void);
        list <string> * getIntegration(void);
        void setSentence(list<Sentence>);
        list <Sentence> *getSentences(void) ;
};

void Notion::setName(string name) {
    this->name=name;
}
string Notion::getName() {
    return name;
}
void Notion::setDefferenciation (list <string> listParam) {
    this->defferenciation = listParam;
}

list <string> *Notion::getDefferenciation() {
    return &defferenciation;
}

void Notion::setIntegration(list<string> listParam) {
    this->integration = listParam;
}

list <string> *Notion::getIntegration() {
    return &integration;
}

void Notion::setSentence(list<Sentence> listParam) {
    this->sentences = listParam;
}

list <Sentence> *Notion::getSentences(void) {
    return &sentences;
}
#endif //NOTION_H

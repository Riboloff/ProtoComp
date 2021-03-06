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
        string aspect;

    public:
        string getName();
        void setName(string);
        string getAspect();
        void setAspect(string);
        void setDefferenciation (list <string>);
        void setIntegration (list <string>);
        void setSentence(list<Sentence>);
        void pushBackSentence(Sentence);
        list <string> * getDefferenciation(void);
        list <string> * getIntegration(void);
        list <Sentence> *getSentences(void) ;
};

void Notion::setName(string name) {
    this->name=name;
}
string Notion::getName() {
    return name;
}

void Notion::setAspect(string aspect) {
    this->aspect=aspect;
}
string Notion::getAspect() {
    return aspect;
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

void Notion::pushBackSentence(Sentence sentence) {
    this->sentences.push_back(sentence);
}

list <Sentence> *Notion::getSentences(void) {
    return &sentences;
}
#endif //NOTION_H

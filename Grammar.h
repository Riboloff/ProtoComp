#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include <map>
#include "Notion.h"

using namespace std;

class Grammar {
    private:
        list <Notion> notions;
    public:
        list <Notion> getNotions();
        void setNotions(list <Notion> &notions);
};

list <Notion> Grammar::getNotions() {
    return notions;
}

void Grammar::setNotions(list <Notion> &notions) {
    this->notions=notions;
}

#endif //GRAMMAR_H

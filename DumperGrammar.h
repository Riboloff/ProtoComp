#ifndef DUMPERGRAMMAR_H
#define DUMPERGRAMMAR_H
#include <string>
#include <list>
#include "Grammar.h"
#include "Notion.h"
#include "Sentence.h"

using namespace std;
class DumperGrammar {
private:
    string join(list<string>*);
public:
    void dumpGrammar(Grammar);
};

void DumperGrammar::dumpGrammar(Grammar grammar){
list <Notion> notions = grammar.getNotions();

    for (list<Notion>::iterator iter = notions.begin(); iter != notions.end(); iter++) {
        Notion n = *iter;
        cout << "Notion:" << endl;
        cout << "    Defferenciation:" << join(n.getDefferenciation()) << endl;
        cout << "    Name:" << n.getName() << endl;
        cout << "    Integration:" << join(n.getIntegration()) << endl;
        list<Sentence> *sentences = n.getSentences();
        for (list<Sentence>::iterator tr = sentences->begin(); tr != sentences->end(); tr++) {
            Sentence sentece = *tr;
            cout << "\t\tSentenses:" << endl;
            cout << "\t\t\tsyntax:" << join(&(sentece.syntax)) << endl;
            cout << "\t\t\tsemantic:" << join(&(sentece.semantic)) << endl;
        }
    }
}

string DumperGrammar::join(list<string>* list_) {
    string stringOut;
    unsigned int size = list_->size();
    unsigned int count = 0;
    for (list<string>::iterator tr = list_->begin(); tr != list_->end(); tr++) {
        string str = *tr;
        stringOut += str;
        if(count != size) {
            stringOut +=  " ";
        }
    }
    return stringOut;
}

#endif // DUMPERGRAMMAR_H

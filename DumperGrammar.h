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
    string join(list<string>*, string);
    string join(vector<Token>*, string);
public:
    void dumpGrammar(Grammar);
};

void DumperGrammar::dumpGrammar(Grammar grammar){
list <Notion> notions = grammar.getNotions();
    for (list<Notion>::iterator iter = notions.begin(); iter != notions.end(); iter++) {
        Notion n = *iter;
        string str = ", ";
        cout << "Notion: " << endl;
        cout << "\tAspect: " << n.getAspect() << endl;
        cout << "\tDefferenciation: " << join(n.getDefferenciation(), str) << endl;
        cout << "\tName: " << n.getName() << endl;
        cout << "\tIntegration: " << join(n.getIntegration(), str) << endl;
        list<Sentence> *sentences = n.getSentences();
        for (list<Sentence>::iterator tr = sentences->begin(); tr != sentences->end(); tr++) {
            Sentence sentece = *tr;
            cout << "\t\tSentenses: " << endl;
            cout << "\t\t\tsyntax: " << join(sentece.getSyntax(), str) << endl;
            cout << "\t\t\tsemantic: " << join(sentece.getSemantic(), str) << endl;
        }
    }
}

string DumperGrammar::join(list<string>* list_, string str) {
    string stringOut;
    unsigned int size = list_->size();
    unsigned int count = 0;
    for (list<string>::iterator tr = list_->begin(); tr != list_->end(); tr++) {
        stringOut += *tr;
        if(count != size-1) {
            stringOut +=  str;
        }
        count++;
    }
    return stringOut;
}

string DumperGrammar::join(vector <Token>* list_, string str) {
    string stringOut;
    unsigned int size = list_->size();
    unsigned int count = 0;
    for (vector<Token>::iterator tr = list_->begin(); tr != list_->end(); tr++) {
        stringOut += tr->getValue();
        if(count != size-1) {
            stringOut +=  str;
        }
        count++;
    }
    return stringOut;
}
#endif // DUMPERGRAMMAR_H

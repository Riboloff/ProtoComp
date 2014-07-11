#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <stdexcept>

#include "ReadFile.h"
#include "Parser.h"
#include "TableSymbol.h"
//#include "Grammar.h"

using namespace std;
int main(int argc, char *argv[]) {
    const char *fileName = argv[1];
    if (argc < 2) { 
      cerr << "Вы должны указать имя файла" << endl; 
      exit(1); 
    }

    Parser parser(fileName);
    Grammar grammar;
    list<Notion> notions;
    try {
        grammar = parser.grammar(notions);
        list <Notion> notions = grammar.getNotions();
        
        for (list<Notion>::iterator iter = notions.begin(); iter != notions.end(); iter++) {
            Notion n = *iter;
            list <string> *tmp;
            cout << "Notion:" << endl;
            tmp = n.getDefferenciation();
            string stringOut;
            for (list<string>::iterator tr = tmp->begin(); tr != tmp->end(); tr++) {
                string str = *tr;
                //TODO: Заменить эту парнографию на split, join.
                stringOut += str + " ";
            }
            cout << "    Defferenciation:" << stringOut << endl;
            cout << "    Name:" << n.getName() << endl;
            tmp = n.getIntegration();
            stringOut = "";
            for (list<string>::iterator tr = tmp->begin(); tr != tmp->end(); tr++) {
                string str = *tr;
                stringOut += str + " ";
            }
            cout << "    Integration:" << stringOut << endl;
            list<Sentence> *sentences = n.getSentences();
            for (list<Sentence>::iterator tr = sentences->begin(); tr != sentences->end(); tr++) {
                Sentence sentece = *tr;
                cout << "\t\tSentenses:" << endl;

                tmp = &(sentece.syntax);
                stringOut = "";
                for (list<string>::iterator tr = tmp->begin(); tr != tmp->end(); tr++) {
                    string str = *tr;
                    stringOut += str + " ";
                }
                cout << "\t\t\tsyntax:" << stringOut << endl;

                tmp = &(sentece.semantic);
                stringOut = "";
                for (list<string>::iterator tr = tmp->begin(); tr != tmp->end(); tr++) {
                    string str = *tr;
                    stringOut += str + " ";
                }
                cout << "\t\t\tsemantic:" << stringOut << endl;
            }

        }
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }

    return 0;
}

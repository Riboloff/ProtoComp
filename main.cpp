#include <iostream>
#include <stdlib.h>
#include <list>

#include "Parser.h"
#include "DumperGrammar.h"

using namespace std;
int main(int argc, char *argv[]) {
    const char *fileName = argv[1];
    if (argc < 2) { 
      cerr << "Вы должны указать имя файла" << endl; 
      exit(1);
    }

    Parser parser(fileName);
    Grammar grammar;
    //list<Notion> notions;
    try {
        grammar = parser.grammar();
        //DumperGrammar dumper;
       // dumper.dumpGrammar(grammar);
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }

    return 0;
}

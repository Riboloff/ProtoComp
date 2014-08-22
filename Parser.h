#include <vector>
#include <map>
#include "Grammar.h"

//#include "Token.h"
#include "TableSymbol.h"
//#include "ReadFile.h"
#include "Lexer.h"

using namespace std;

class Parser {
private:
    Lexer *text_;
    TableSymbol *tableSymbol_;
    Notion notion(void);
    list <string> defferenciation(void);
    list <string> integration(void);
    string nameDefinition(void);
    string aspectDefinition(void);
    list <Sentence> sentences(void);
    Sentence sentence(void);
    list <string> syntax(void);
    list <string> semantic(void);
    string item(void);

public:
    Parser(const char*);
    Grammar grammar(void);
};
Parser::Parser(const char* fileName) {
    text_ = new Lexer(fileName);
    tableSymbol_ = new TableSymbol();
}
Grammar Parser::grammar(void) {
    Grammar grammar;
    Notion notion;
    list<Notion> notions;

    while (!text_->checkEndFile()) { //Кажется Парсер не должен проверять конец файла.
        notion = Parser::notion();
        notions.push_back(notion);
    }
    /*
    while (true) {
        try {
            notion = Parser::notion();
            notions.push_back(notion);
        } catch (EndOfFile) {
            break;
        } catch (invalid_argument) {
            throw (invalid_argument);
        }
    }
    */
    grammar.setNotions(notions);
    return grammar;    
}

Notion Parser::notion(void) {
    Notion notion;
    int localPosition = text_->getPointerSymbol();

    try {
        notion.setAspect(aspectDefinition());
    } catch (invalid_argument) {

    }

    try {
        notion.setDefferenciation(defferenciation());
    } catch (invalid_argument &e) {
        text_->setPointerSymbol(localPosition);
        cout << e.what() << endl;
    } /*catch (EndOfFile) {
        throw EndOfFile;
    }
*/
    notion.setName(nameDefinition());
    try {
        notion.setIntegration(integration());
    } catch (invalid_argument &e) {
        text_->setPointerSymbol(localPosition);
        cout << e.what() << endl;
    }
    int startPositionSentance = text_->getPointerSymbol();
    try {//Есть мнение, что может не быть ни одного sentence
        notion.setSentence(sentences());
    } catch (invalid_argument) {
        text_->setPointerSymbol(startPositionSentance);
    }
    return notion;
}

list <string> Parser::defferenciation(void) {
    list <string> defferenciation;
    Token token = text_->nextToken();
    if(text_->checkEndFile()) {
        throw invalid_argument("defferenciation: EOF");
    }

    if (token.getValue() == "(") {
        token = text_->nextToken();
        while(token.getValue() != ")") {
            defferenciation.push_back(token.getValue());
            token = text_->nextToken();
        }
        return defferenciation;
    } else {
        throw invalid_argument("defferenciation: Token != (");
    }
}

list <string> Parser::integration(void) {
    list <string> integration;
    Token token = text_->nextToken();

    if(text_->checkEndFile()) {
        throw invalid_argument("integration: EOF");
    }
    if (token.getValue() == "(") {
        token = text_->nextToken();
        while(token.getValue() != ")") {
            integration.push_back(token.getValue());
            token = text_->nextToken();
        }
        return integration;
    } else {
        throw invalid_argument("integration: Token != (");
    }
}

string Parser::aspectDefinition(void) {
    string aspect_definition;
    int startPosition = text_->getPointerSymbol();
    Token token = text_->nextToken();

    if(token.getValue() == "(") {
        cout << startPosition<<endl;
        text_->setPointerSymbol(startPosition);
        throw invalid_argument("");
    }
//Для аспектов нужна ли таблица символов?
    if (token.getType() == "id") {
        aspect_definition = token.getValue();
        boost::smatch result;
        boost::regex name_valid("[A-Za-z][A-Za-z]*");
        if(! boost::regex_match(aspect_definition, result, name_valid)) {
            text_->setPointerSymbol(startPosition);
            throw invalid_argument("nameDefinition");
        }

    }

    return aspect_definition;
}

string Parser::nameDefinition(void) {
    string name_definition;
    unsigned int startPosition = text_->getPointerSymbol();
    Token token = text_->nextToken();

    if(token.getValue() == "(") {
        //пустое понятие
        text_->setPointerSymbol(startPosition);
        name_definition = "__empty__";
        try {
            tableSymbol_->putSymbol(name_definition);
        } catch (invalid_argument &e) {
            cout << "Dublication empty name" << name_definition << endl;
        }
    } else {
        name_definition = token.getValue();
        boost::smatch result;
        boost::regex name_valid("[A-Za-z][A-Za-z]*");
        if(boost::regex_match(name_definition, result, name_valid)) {
            try {
               tableSymbol_->putSymbol(name_definition);
            } catch (invalid_argument) {
                cout << "Dublication" << name_definition << endl;
            }
        } else {
            throw invalid_argument("nameDefinition");
        }
    }

    return name_definition;
}

list <Sentence> Parser::sentences(void) {
    if(text_->checkEndFile()) {
        throw invalid_argument("defferenciatio: EOF");
    }
    list<Sentence> sentences;

    while(1) {
        try {
            Sentence sent;
            sent = sentence();
            sentences.push_back(sent);
        } catch (invalid_argument &e) {
            //cout << e.what() << endl;
            break;
        }
    }
    return sentences;
}

Sentence Parser::sentence(void) {
    Sentence sentence;
    unsigned int pointer = text_->getPointerSymbol();
    try {
        sentence.setSyntax(syntax());
        sentence.setSemantic(semantic());
    } catch(invalid_argument) {
        text_->setPointerSymbol(pointer);
        throw invalid_argument("sencence: test");
    }
    return sentence;
}

list <string> Parser::syntax(void) {
    list <string> syntax;
    unsigned int pointer = text_->getPointerSymbol();
    Token token = text_->nextToken();
    string item;
    while (token.getValue() != "{") {
        try {
            item = Parser::item();
            syntax.push_back(item);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            throw invalid_argument("syntax: test");
        }

        pointer = text_->getPointerSymbol();
        token = text_->nextToken();
    }
    text_->setPointerSymbol(pointer);
    return syntax;
}

string Parser::item(void) {
    Token token = text_->getToken();
    string type = token.getType();
    if (type == "term") {
        return "'" + token.getValue() + "'"; //должнабыть ф-я, которая квотит строку.
    } else if (type == "pattern") {
        return "\"" + token.getValue() + "\"";
    } else if (type == "alias") {
        return "`" + token.getValue() + "`";
    } else if (type == "id") {
        if (tableSymbol_->checkSymbol(token.getValue())) {
            return token.getValue();
        }
    }
    throw invalid_argument("item: test");
}

list <string> Parser::semantic(void) {
    list <string> semantic;
    Token token = text_->nextToken();
    string item;
    if (token.getValue() != "{") {
        throw invalid_argument("semantic: ");
    }
    token = text_->nextToken();
    while (token.getValue() != "}") {
        try {
            item = Parser::item();
            semantic.push_back(item);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            throw invalid_argument("semantic: test");
        }

        token = text_->nextToken();
    }
    return semantic;
}

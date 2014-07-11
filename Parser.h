#include <vector>
#include <map>
#include "Grammar.h"

//#include "Token.h"
#include "TableSymbol.h"
#include "ReadFile.h"

using namespace std;

class Parser {
private:
    ReadFile *text_;
    TableSymbol *tableSymbol;
    Notion notion(void);
    list <string> defferenciation(void);
    list <string> integration(void);
    string nameDefinition(void);
    list <Sentence> sentences(void);
    Sentence sentence(void);
    list <string> syntax(void);
    list <string> semantic(void);
    string item(void);

public:
    Parser(const char*);
    Grammar grammar(list<Notion> &notions) throw (invalid_argument);
};
Parser::Parser(const char* fileName) {
    text_ = new ReadFile(fileName);
    tableSymbol = new TableSymbol();
}
Grammar Parser::grammar(list<Notion> &notions) throw (invalid_argument){
    Grammar grammar;
    Notion notion; 

    notion = Parser::notion();
    notions.push_back(notion);
    if (!text_->checkEndFile()) {
        Grammar grammar_tmp;
        //if (grammar_tmp = Parser::grammar()) {
            
        //}
    }
    grammar.setNotions(notions);
    return grammar;    
}

Notion Parser::notion(void) {
    Notion notion;
    int localPosition = text_->getPointerSymbol();
    try {
        notion.setDefferenciation(defferenciation());
    } catch (invalid_argument &e) {
        text_->setPointerSymbol(localPosition);
        cout << e.what() << endl;
    }
    notion.setName(nameDefinition());
    try {
        notion.setIntegration(integration());
    } catch (invalid_argument &e) {
        text_->setPointerSymbol(localPosition);
        cout << e.what() << endl;
    }
    int startPositionSentance = text_->getPointerSymbol();
    try {
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
        throw invalid_argument("defferenciatio: EOF");
    }

    if (token.getValue() == "(") {
        token = text_->nextToken();
        while(token.getValue() != ")") {
            defferenciation.push_back(token.getValue());
            token = text_->nextToken();
        }
        return defferenciation;
    } else {
        throw invalid_argument("defferenciatio: Token != (");
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

string Parser::nameDefinition(void) {
    string name_definition;
    unsigned int startPosition = text_->getPointerSymbol();
    Token token = text_->nextToken();

    if(token.getValue() == "(") {
        //пустое понятие
        text_->setPointerSymbol(startPosition);
        name_definition = "__empty__";
        try {
            tableSymbol->putSymbol(name_definition);
        } catch (invalid_argument &e) {
            cout << "Dublication empty name" << name_definition << endl;
        }
    } else {
        name_definition = token.getValue();
        boost::smatch result;
        boost::regex name_valid("[A-Za-z][A-Za-z]*");
        if(boost::regex_match(name_definition, result, name_valid)) {
            try {
               tableSymbol->putSymbol(name_definition);
            } catch (invalid_argument &e) {
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
            cout << e.what() << endl;
            break;
        }
    }
    return sentences;
/*
    try {
        Sentence sent;
        sent = sentence();
        sentences.push_back(sent);
        sentences = sentences(sentences);
    } catch(invalid_argument) {
        return sentences;
    }
*/
}

Sentence Parser::sentence(void) {
    Sentence sentence;
    //throw invalid_argument("sencence: test");
    sentence.syntax = syntax();
    sentence.semantic = semantic();

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
            //throw invalid_argument("syntax: test");
        }

        pointer = text_->getPointerSymbol();
        token = text_->nextToken();
    }
    cout << token.getValue() <<text_->getPointerSymbol()<<"!!!!!!!!!!!!" << endl;
    text_->setPointerSymbol(pointer);
    cout << token.getValue() <<text_->getPointerSymbol()<<"!!!!!!!!!!!!" << endl;
    return syntax;
}

string Parser::item(void) {
    Token token = text_->getToken();
    string type = token.getType();
    cout << token.getValue() <<"\t"<< token.getType() << endl;
    if (type == "quotes") {
        return token.getValue();
    } else if (type == "dublesQuotes") {
        return token.getValue();
    } else if (type == "id") {
            //проверить, если ли в таблице символов
        text_->printAllTokens();
        //cout << text_->nextToken().getValue() << endl;
        if (tableSymbol->checkSymbol(token.getValue())) {
            return token.getValue();
        }
    }
    throw invalid_argument("item: test");
}

list <string> Parser::semantic(void) {
    list <string> semantic;
    Token token = text_->nextToken();
    cout << token.getValue() <<"????????"<< endl;
    string item;
    if (token.getValue() != "{") {
        throw invalid_argument("semantic: ");
    }
    while (token.getValue() != "}") {
        try {
            item = Parser::item();
            semantic.push_back(item);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
           // throw invalid_argument("syntax: test");
        }

        token = text_->nextToken();
    }
    return semantic;
}

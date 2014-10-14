#include <vector>
#include <map>
#include "Grammar.h"

#include "TableSymbol.h"
#include "Lexer.h"
#include "ExceptionStorage.h"

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

    while (true) {
        try {
            notion = Parser::notion();
            notions.push_back(notion);

        } catch (incorrect_branch_parsing) {
            cout << "incorrect_branch_parsing" << endl;

        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            throw invalid_argument("grammar:");

        } catch (end_of_file) {
            break;
        }
    }

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
        throw invalid_argument("notion:");
    } catch (end_of_file) {
        throw end_of_file("");
    }

    notion.setName(nameDefinition());

    try {
        notion.setIntegration(integration());
    } catch (invalid_argument &e) {
        text_->setPointerSymbol(localPosition);
        cout << e.what() << endl;
        throw invalid_argument("notion:");
    }

    int startPositionSentance = text_->getPointerSymbol();

    try {
        notion.setSentence(sentences());
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
        text_->setPointerSymbol(startPositionSentance);
        throw invalid_argument("notion:");
    }

    return notion;
}

list <string> Parser::defferenciation(void) {
    list <string> defferenciation;
    Token token = text_->nextToken();

    if (token.getValue() == "(") {
        token = text_->nextToken();
        string item;
        while(token.getValue() != ")") {
            try {
                item = Parser::item();
                defferenciation.push_back(token.getValue());
            } catch (invalid_argument &e) {
                cout << e.what() << endl;
                throw invalid_argument("deffferenciation: item()");
            }
            token = text_->nextToken();
        }
        return defferenciation;
    } else {
        cout << token.getValue()<< endl;
        throw invalid_argument("defferenciation: Token != (");
    }
}

list <string> Parser::integration(void) {
    list <string> integration;
    Token token = text_->nextToken();

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

    while(true) {
        try {
            Sentence sent;
            sent = sentence();
            sentences.push_back(sent);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            throw invalid_argument("sentences: Parser::sentence ->invalid_argument");
        } catch(incorrect_branch_parsing) {
            //cout << "sencences: ->incorrect_branch_parsing" << endl;
            break;
        } catch (end_of_file) {
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
    } catch(invalid_argument &e) {
        cout << e.what() << endl;
        text_->setPointerSymbol(pointer);
        throw invalid_argument("sencence: ->invalid_argument");
    } catch(incorrect_branch_parsing) {
        //cout << "sencence: ->incorrect_branch_parsing" << endl;
        text_->setPointerSymbol(pointer);
        throw incorrect_branch_parsing("sencence: ->incorrect_branch_parsing");
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
            //cout << e.what() << endl;
            throw incorrect_branch_parsing("syntax: Parser::item");
        }

        pointer = text_->getPointerSymbol();
        token = text_->nextToken();
    }
    text_->setPointerSymbol(pointer);

    //for (list <string>::iterator iter= syntax.begin(); iter != syntax.end(); iter++) {
    //   cout << *iter << endl;
    //}
    //cout << "___" <<token.getValue() << endl;
    return syntax;
}

string Parser::item(void) {
    Token token = text_->getToken();
    string type = token.getType();
    string error;

    if (type == "term") {
        return "'" + token.getValue() + "'"; //должнабыть ф-я, которая квотит строку.
    } else if (type == "pattern") {
        return "\"" + token.getValue() + "\"";
    } else if (type == "alias") {
        return "`" + token.getValue() + "`";
    } else if (type == "id") {
        if (tableSymbol_->checkSymbol(token.getValue())) {
            return token.getValue();
        } else {
             error = "Токен " + token.getValue() + " не найден";
        }
    }

    throw invalid_argument("item: " + error);
}

list <string> Parser::semantic(void) {
    list <string> semantic;
    Token token = text_->nextToken();
    string item;

    if (token.getValue() != "{") {
        throw invalid_argument("semantic: Токен != { -> invalid_argument");
    }

    token = text_->nextToken();

    while (token.getValue() != "}") {
        try {
            item = Parser::item();
            semantic.push_back(item);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            throw invalid_argument("semantic: Parser::item() -> invalid_argument");
        }

        token = text_->nextToken();
    }

    return semantic;
}

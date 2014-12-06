#ifndef SEMANTICCHECKER_H
#define SEMANTICCHECKER_H

#include <string>
#include <vector>
#include <boost/regex.hpp>

#include "Token.h"
#include "Notion.h"

using namespace std;

class Semantic {
typedef map <string, Notion> TableNotions;

private:
    string text;
    TableNotions tableNotions;
    vector <Token> semantic;
    vector <int> matchToken(int, Token);

public:
    Semantic(string, TableNotions);
    bool checkSemantic(int);
    vector<Token> getSemantic (void);
};

Semantic::Semantic(string text, TableNotions tableNotions) {
//trim(text) - брезать текст от пробельных символов с обеих сторон
    this->text = text;
    this->tableNotions = tableNotions;
}

bool Semantic::checkSemantic(int pos) {
    if (pos == this->text.length()) {
        return true;
    }
    for (TableNotions::iterator iter= this->tableNotions.begin(); iter != this->tableNotions.end(); iter++) {
        Notion notion = iter->second;
        //matches =
    }

    return false;
}
vector <int> Semantic::matchToken(int pos, Token token) {

    vector <int> vec;
    if(token.getType() == "term") {
        vector <int> vec;
        if (this->text.substr(pos, pos + token.getValue().length()) == token.getValue()) {
            vec.push_back(pos + token.getValue().length());
        }

        return vec;

    } else if(token.getType() == "id") {
        Notion notion = this->tableNotions[token.getValue()];
        //vector <int> matches = matchNotion(pos, notion);
        //return matches;

    } else if (token.getType() == "pattern") {
        cout << "qw" << endl;
        vector <int> vec;
        boost::regex re ("\^" + token.getValue());
        boost::smatch result;
        string str = this->text.substr(pos);
        if(boost::regex_search(str, result, re)) {
            cout << result[0] << endl;
            vec.push_back(pos + result[0].length());
            return vec;
        }
    }
    return vec;
}

vector <Token> Semantic::getSemantic (void) {
    return this->semantic;
}

#endif // SEMANTICCHECKER_H

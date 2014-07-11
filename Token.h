#ifndef TOKEN_H
#define TOKEN_H
#include <boost/regex.hpp>
//#include "TableSymbol.h"

using namespace std;

class Token {
private:
    string type_;
    string value_;
    //unsigned int id_;
public:
    void addWord(string);
    string getType(void);
    string getValue(void);
};

void Token::addWord(string word) {
    boost::smatch result;

    boost::regex regBracket("\\(|\\)|\\[|\\]|\\{|\\}");
    if(boost::regex_match(word, result, regBracket)){
        this->type_ = "bracket";
        this->value_ = word;
        //this->id_ = 0;
        return;

    }
    boost::regex regQuotesDubles("\"(.*)\"");
    if(boost::regex_match(word, result, regQuotesDubles)){
        this->type_ = "dublesQuotes";
        this->value_ = result[1];
        //this->id_ = 0;
        return;
    }
    boost::regex regQuotes("\'(.*)\'");
    if(boost::regex_match(word, result, regQuotes)){
        this->type_ = "quotes";
        this->value_ = result[1];
        //this->id_ = 0;
        return;
    }
    //this->id_ = tableSymbol_.putSymbol(word);
    this->type_ = "id";
    this->value_ = word;

    return;

}
string Token::getType(void) {
    return this->type_;
}

string Token::getValue(void) {
    return this->value_;
}

#endif // TOKEN_H

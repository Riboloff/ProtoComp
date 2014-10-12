#ifndef TOKEN_H
#define TOKEN_H
#include <boost/regex.hpp>

using namespace std;

class Token {
private:
    string type_;
    string value_;
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
        return;

    }
    boost::regex regQuotesDubles("\"(.*)\"");
    if(boost::regex_match(word, result, regQuotesDubles)){
        this->type_ = "pattern";
        this->value_ = result[1];
        return;
    }
    boost::regex regQuotes("\'(.*)\'");
    if(boost::regex_match(word, result, regQuotes)){
        this->type_ = "term";
        this->value_ = result[1];
        return;
    }
    boost::regex regQuotesBack("`(.*)`");
    if(boost::regex_match(word, result, regQuotesBack)){
        this->type_ = "alias";
        this->value_ = result[1];
        return;
    }
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

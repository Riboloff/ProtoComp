#ifndef SEMANTICCHECKER_H
#define SEMANTICCHECKER_H

#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

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
    vector <int> matchNotion(int, Notion);
    vector <int> matchSentence(int, Sentence);
    vector <int> _chompTokenTrailingSpaces(vector <int>);

public:
    Semantic(string, TableNotions);
    bool checkSemantic(int);
    vector<Token> getSemantic (void);
};

Semantic::Semantic(string text, TableNotions tableNotions) {
    boost::algorithm::trim(text);
    this->text = text;
    this->tableNotions = tableNotions;
}

bool Semantic::checkSemantic(int pos) {
    if (pos == this->text.length()) {
        return true;
    }
    for (TableNotions::iterator iter= this->tableNotions.begin(); iter != this->tableNotions.end(); iter++) {
        Notion notion = iter->second;
        vector <int> matches = matchNotion(pos, notion);
        for (vector <int>::iterator i = matches.begin(); i != matches.end(); ++i) {
            int match = *i;
            if (checkSemantic(match)) {
                return true;
            }
        }
    }

    return false;
}

vector <int> Semantic::matchToken(int pos, Token token) {
    vector <int> vec;

    if(token.getType() == "term") {
        vector <int> vec;
        //if (this->text.substr(pos, pos + token.getValue().length()) == token.getValue()) {
        if (this->text.substr(pos, token.getValue().length()) == token.getValue()) {
            vec.push_back(pos + token.getValue().length());
        }

        return vec;

    } else if(token.getType() == "id") {
        Notion notion = this->tableNotions[token.getValue()];
        vector <int> matches = matchNotion(pos, notion);

        return matches;

    } else if (token.getType() == "pattern") {
        vector <int> vec;
        boost::regex re ("^" + token.getValue());
        boost::smatch result;
        string str = this->text.substr(pos);
        if(boost::regex_search(str, result, re)) {
            vec.push_back(pos + result[0].length());
            return vec;
        }
    }

    return vec;
}

vector <int> Semantic::matchNotion(int pos, Notion notion) {
    vector <int> notionMatches;
    for (list <Sentence>::iterator iter=notion.getSentences()->begin(); iter != notion.getSentences()->end(); ++iter) {
        Sentence sentence = *iter;
        vector <int> sentenceMatches = matchSentence(pos, sentence);

        for (vector <int>::iterator j = sentenceMatches.begin(); j != sentenceMatches.end(); ++j) {
            notionMatches.push_back(*j);
        }
    }

    return notionMatches;
}

vector <int> Semantic::matchSentence(int pos , Sentence sentence) {
    vector <int> sentenceMatches;
    Token token = *(sentence.getSyntax()->begin());

    if (! sentence.getSyntax()->size()) {
        sentenceMatches.push_back(pos);
        return sentenceMatches;
    }
    vector <int> matches = _chompTokenTrailingSpaces(matchToken(pos, token));
    for (vector <int>::iterator i = matches.begin(); i != matches.end(); ++i) {
        int match = *i;
        vector <Token>* Syntax = sentence.getSyntax();
        Syntax->erase(Syntax->begin());
        sentence.setSyntax(*Syntax);
        //КОСТЫЛЬ
        vector <int> tailMatches;
        if (! sentence.getSyntax()->size()) {
            //sentenceMatches.push_back(match);
            //return sentenceMatches;
            tailMatches.push_back(match);
        } else {
            tailMatches = matchSentence(match, sentence);
        }
        //
        for (vector <int>::iterator i = tailMatches.begin(); i != tailMatches.end(); ++i) {
            sentenceMatches.push_back(*i);
        }
    }

    return sentenceMatches;
}

vector <Token> Semantic::getSemantic (void) {
    return this->semantic;
}

vector <int> Semantic::_chompTokenTrailingSpaces(vector <int> poss) {
    for (u_int i = 0; i != poss.size(); ++i) {
        while (this->text.substr(poss[i], 1) == " ") {
            poss[i]++;
        }
    }

    return poss;
}

#endif // SEMANTICCHECKER_H

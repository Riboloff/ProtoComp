#ifndef TABLESYMBOL_H
#define TABLESYMBOL_H

#include <iostream>
#include <map>
#include <boost/regex.hpp>

using namespace std;


class TableSymbol {

private:
    map <string,int> tableSymbol_;
    int numberLast_;
public:
    TableSymbol(void);
    int putSymbol(string) throw (invalid_argument);
    bool checkSymbol(string);
};

TableSymbol::TableSymbol(void) {
    numberLast_ = 0;
}

int TableSymbol::putSymbol(string key) throw (invalid_argument){
//    map<string, int>::iterator it = this->tableSymbol_.find(key);
//    if (it == tableSymbol_.end()) {
    if(!checkSymbol(key)) {
        this->numberLast_++;
        this->tableSymbol_[key] = this->numberLast_;
    } else {
        throw invalid_argument("");
    }
    //for (map<string, int>::iterator iter = tableSymbol_.begin(); iter != tableSymbol_.end(); iter++){
    //    cout << iter->first << endl;
    //}
    return this->tableSymbol_[key];
}
bool TableSymbol::checkSymbol(string symbol) {
    map<string, int>::iterator it = this->tableSymbol_.find(symbol);
    if (it == tableSymbol_.end()) return false;
    return true;
}

#endif // TABLESYMBOL_H

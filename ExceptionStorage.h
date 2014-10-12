#ifndef EXCEPTIONSTORAGE_H
#define EXCEPTIONSTORAGE_H
#include <exception>
#include <string>

using namespace std;

class incorrect_branch_parsing : exception {
public:
    incorrect_branch_parsing (const string&);
};
incorrect_branch_parsing::incorrect_branch_parsing(const string&) {}

class end_of_file : exception {
public:
    end_of_file (const string&);
};
end_of_file::end_of_file(const string&) {}

#endif // EXCEPTIONSTORAGE_H

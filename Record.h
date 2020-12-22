#ifndef Record_H
#define Record_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Record {
private:
    string title;
    string author;
    string ISBN;
    string year;
    string edition;
public:
    //accessor/mutator functions
    string get_title() const;
    void set_title(string newTitle);
    string get_author() const;
    void set_author(string newAuthor);
    string get_ISBN() const;
    void set_ISBN(string newISBN);
    string get_year() const;
    void set_year(string newYear);
    string get_edition() const;
    void set_edition(string newEdition);
    Record();
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif
#include "Record.h"
using namespace std;

// Record::Record(){
//     title = "";
//     author = ""; 
//     ISBN = ""; 
//     year = ""; 
//     edition = "";
// }
string Record::get_title() const{
    return this->title;
}

void Record::set_title(string newTitle){
    this->title = newTitle;
}

string Record::get_author() const{
    return this->author;
}

void Record::set_author(string newAuthor){
    this->author = newAuthor;
}

string Record::get_ISBN() const{
    return this->ISBN;
}

void Record::set_ISBN(string newISBN){
    this->ISBN = newISBN;
}

string Record::get_year() const{
    return this->year;
}

void Record::set_year(string newYear){
    this->year = newYear;
}

string Record::get_edition() const{
    return this->edition;
}

void Record::set_edition(string newEdition){
    this->edition = newEdition;
}

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec){
    string line;
    getline(is, line);
    if(!is.eof()){
        getline(is, line);
        rec.set_title(line);
        getline(is, line);
        rec.set_author(line);
        getline(is, line);
        rec.set_ISBN(line);
        getline(is, line);
        rec.set_year(line);
        getline(is, line);
        rec.set_edition(line);

    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Record& rec){
    os << rec.get_title() << std::endl << rec.get_author() << std::endl << rec.get_ISBN() << std::endl << rec.get_edition() << std::endl << rec.get_year() << std::endl;
    return os;
}

// Comparison operators
bool operator==(const Record& r1, const Record& r2){
    Record r11 = r1;
    Record r22 = r2;

     if (r11.get_title() == r22.get_title()){
       if (r11.get_author() == r22.get_author()){
           if (r11.get_ISBN() == r22.get_ISBN()){
               return true;
           }
           else
           {
               false;
           }
       }
       else
       {
           return false;
       }
   }
   else
   {
       return false;
   }
}
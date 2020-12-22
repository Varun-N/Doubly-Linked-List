#include "Library.h"
#include "TemplatedDLList.h"
#include <algorithm>


std::vector<Record> Library::search(std::string title){
    vector<Record> listStuff;
    int location = (int)title[0] - (int)'A';
    DLListNode<Record> * start = book_db[location].first_node();

    while (start != book_db[location].after_last_node()) {
        if (start->obj.get_title() == title) {
            listStuff.push_back(start->obj);
        }
        start = start->next;
    }
    return listStuff;


}

//Imports records from a file.  Does not import duplicates.
// Return the number of records added to the database
int Library::import_database(std::string filename){

    // string line;
    // getline(is, line);
    // if(!is.eof()){
    //     getline(is, line);
    //     rec.set_title(line);
    //     getline(is, line);
    //     rec.set_author(line);
    //     getline(is, line);
    //     rec.set_ISBN(line);
    //     getline(is, line);
    //     rec.set_year(line);
    //     getline(is, line);
    //     rec.set_edition(line);

    // }
    ifstream fin(filename);
    string line;
    if (!fin)
    {
      cout << "file didnt open ";
      return;
    }
    else{
        while(!fin.eof()){
            string line;
            getline(fin, line);
            add_record();
    }
}

//Exports the current database to a file
//Return the number of records exported
int export_database(std::string filename){

}

void print_database(){

}

//add record to database, avoid complete duplicates
bool Library::add_record(Record book){
    char startLetter = book.get_title()[0];
    int location = (int)startLetter - (int)'A';
    if(book_db[location].is_empty()){
        book_db[location].insert_first(book);
    }
    else {
        DLListNode<Record> * start = book_db[location].first_node();
        while (start->obj.get_title() < book.get_title()) {
                start = start->next;
                if (start == book_db[location].after_last_node()) {
                    book_db[location].insert_last(book);
                    return true;
                }
                if (start->obj == book) {
                    return false;
                }

        }
        book_db[location].insert_before(*start, book);
        return true;    
    }
}

//Deletes a record from the database
void Library::remove_record(Record book){
    char startLetter = book.get_title()[0];
    int location = (int)startLetter - (int)'A';
    if(book_db[location].is_empty()){
        throw "empty list";
    }
    else {
        DLListNode<Record> * start = book_db[location].first_node();
        if (start->obj == book) {
            book_db[location].remove_first();
            return;
            // return false;
        }
        while (start->obj.get_title() < book.get_title()) {
                start = start->next;
                if (start->obj == book) {
                    book_db[location].remove_after(*start->prev);
                    return;
                    // return false;
                }

        }
        // return true;    
    }

}

//Prompts user for yes or no and returns choice Y or N
char Library::prompt_yes_no(){
    string choice;
    cin >> choice;
    if((choice == "Y") || (choice == "y")){
        return 'Y';
    }
    else if((choice == "N") || (choice == "n")){   
        return 'N';
    }
    else{
        cout << "User Entered Error"; 
    }
}

//Given a vector of menu options returns index of choice
int Library::prompt_menu(std::vector<std::string> pig){
    for (int i = 0; i < pig.size(); i++) {
        cout << "option " << i + 1 << ": " << pig[i] << endl;
    }

    int blegh;
    std::cin >> blegh;
    return blegh - 1;


}

//Prompts user for a new record
Record Library::prompt_record(){
    std::string title;
    std::string author;
    std::string ISBN;
    std::string year;
    std::string edition;

    std::cin >> title >> author >> ISBN >> year >> edition;

    Record * rectoRed = new Record();
    rectoRed->set_title(title);
    rectoRed->set_author(author);
    rectoRed->set_ISBN(ISBN);
    rectoRed->set_year(year);
    rectoRed->set_edition(edition);

    return *rectoRed;

}

//Prompt for a valid title
std::string Library::prompt_title(){
    string title;
    std::cin >> title;
    return title;

}

// Prompt for a valid string
std::string Library::prompt_string(std::string prompt){
    std::cout << prompt << std::endl;
    string inval;
    std::cin >> inval;
    return inval;

    

}

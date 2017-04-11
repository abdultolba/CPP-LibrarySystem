/*
 *  main.cpp
 *  Purpose: C++ Program that manages a library system.
 *
 *  @author Abdulrahman Tolba
 *  @version 1.0
 *
 *  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
 *
 */

#include <iostream>     // std::cout, std::cin, std::endl
#include <string>       // std::string
#include <cstring>      // std::strstr()
#include <vector>       // std::vector
#include <iomanip>      // std::setw(), std::left
#include <fstream>      // std::istream, std::ostream
#include "Book.h"
#include "Magazine.h"
#include "Journal.h"
#include "CinError.h"

using namespace std;

// Function prototypes
int menu();
void toUpperCase(string&);
void loadCatalog(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void searchLibrary(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void checkOut(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void returnItem(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void addItem(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void saveData(vector<Book>&, vector<Magazine>&, vector<Journal>&);
void loadData(vector<Book>&, vector<Magazine>&, vector<Journal>&);
int stringToInt(string);
bool doesExist(string, vector<Book>&, vector<Magazine>&, vector<Journal>&);

// Main function
int main(){
    int option;
    
    // Declaring a vector for library books, magazines, and journals.
    vector<Book> libBooks;
    vector<Magazine> libMagazines;
    vector<Journal> libJournals;
    
    // Loading a catalog of books, magazines, and journals at the start o the program.
    loadCatalog(libBooks, libMagazines, libJournals);

    cout << "***************************************************************\n" << endl;
    cout << "                  Library Management System                      " << endl;
    cout << "               Copyright Abdulrahman Tolba 2017.               \n" << endl;
    cout << "***************************************************************\n" << endl;
    cout << "Please choose an option from the menu below." << endl;
    
    // do-while loop that will keep the program running
    // until the user enters the sentinel value '7' to quit.
    do{
        try{
            option = menu();
            if (option == 1) searchLibrary(libBooks, libMagazines, libJournals);
            else if (option == 2) checkOut(libBooks, libMagazines, libJournals);
            else if (option == 3) returnItem(libBooks, libMagazines, libJournals);
            else if (option == 4) addItem(libBooks, libMagazines, libJournals);
            else if (option == 5) saveData(libBooks, libMagazines, libJournals);
            else if (option == 6) loadData(libBooks, libMagazines, libJournals);
            else if (option == 7)
                cout << "Thank you for using the Library Management System. Goodbye!" << endl;
            else{
                // Clear the input stream if it enters a failure state
                if (cin.fail()) throw CinError();
                // If the user enter a value out of the range 1-7, inform them.
                cout << "Sorry, that option was not recognized. Please try again." << endl;
            }
        }
        // If the user enters invalid input causing a input stream fail
        // state, the error will be caught and will notify the user.
        catch(CinError ce){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ce.what() << endl;
        }
    } while(option != 7); // end do-while loop
    
    return 0;
}

// Displays the main menu to the user and prompts them for input
// @return - returns the users input
int menu(){
    int op;
    
    cout << "\nMain Menu: " << endl;
    cout << "----------------------------" << endl;
    cout << "1. Search Catalog" << endl;
    cout << "2. Check Out an Item" << endl;
    cout << "3. Return an Item" << endl;
    cout << "4. Add a New Item" << endl;
    cout << "5. Save Library Information" << endl;
    cout << "6. Load Library Information" << endl;
    cout << "7. Exit\n" << endl;
    cout << ">> ";
    cin >> op;
    
    return op;
}

// Converts a string to uppercase characters for the purpose of comparison
// @param - a string or array of characters
void toUpperCase(string& str) {
    for (string::iterator p = str.begin(); p != str.end(); ++p){
        // Converting each character in the string to uppercase using
        // pointers and the built in toupper function (characters only)
        *p = toupper(*p);
    }
}

// Fills vectors with preloaded items at the start of the program
// @param - three vectors of type book, magazine, and journal, respectively.
void loadCatalog(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    // Adding a preloaded selection of books to the library catalog
    book.push_back(Book("3BZ", "Harry Potter and the Prisoner of Azkaban", true, "J.K. Rowling"));
    book.push_back(Book("A24", "Perks of Being a Wallflower", false, "Stephen Chbosky"));
    book.push_back(Book("78S", "The Giver", true, "Lois Lowry"));
    book.push_back(Book("12C", "The Book Thief", false, "Markus Zusak"));
    book.push_back(Book("87F", "Harry Potter and the Philosophers Stone", false, "J.K. Rowling"));
    book.push_back(Book("45G", "Harry Potter and the Half Blood Prince", true, "J.K. Rowling"));
    book.push_back(Book("2CN", "Harry Potter and the Chamber of Secrets", false, "J.K. Rowling"));
    
    // Adding a preloaded selection of magazines to the library catalog
    magazine.push_back(Magazine("BBF", "Boys Don't Cry", false, 1));
    magazine.push_back(Magazine("4NL", "People", false, 37));
    magazine.push_back(Magazine("8VD", "TIME", true, 28));
    magazine.push_back(Magazine("14J", "Vogue Magazine", true, 17));
    
    // Adding a preloaded selection of journals to the library catalog
    journal.push_back(Journal("9W9", "American Journal of Education", false, 123));
    journal.push_back(Journal("WS6", "United States Health Care Reform", true, 316));
    journal.push_back(Journal("PQ0", "Wayne State Academic Journal", true, 8));
}

void searchLibrary(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    int op, choice;
    string name, author, temp, original;
    bool found = false;
    
    cout << "Search by: " << endl;
    cout << "1. Name of the item" << endl;
    cout << "2. List by category (Books, Magazines, Journals)" << endl;
    cout << "3. Name of the author (Books only)\n" << endl;
    cout << ">> ";
    
    try{
        cin >> op;
        if(cin.fail()) throw CinError();
        
        switch(op){
            case 1:
                cin.ignore();
                // If the user chooses option 1, the input is searched by checking
                // if it is a substring (or string) of an existing item.
                cout << "Enter the name of the item you are searching for: ";
                getline(cin, name);
                original = name;
                // Converting the users input to uppercase so it can compare it with all titles that
                // contain that string. i.e: searching for "harry" yields all results that contain "harry" in them
                toUpperCase(name);
                
                for (unsigned int i = 0; i < book.size(); i++){
                    temp = book[i].getName();
                    toUpperCase(temp);
                    if (strstr(temp.c_str(), name.c_str())){
                        found = true;
                        break;
                    }
                }
                // If there were any books found matching the users input, display them in a table
                if (found){
                    cout << "Books matching '" << original << "':" << endl << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tAuthor" << endl;
                    cout << "-------------------------------------------------------------------------------------"
                         << endl;
                    for (unsigned int i = 0; i < book.size(); i++){
                        temp = book[i].getName();
                        toUpperCase(temp);
                        if (strstr(temp.c_str(), name.c_str())){
                            cout << left << setw(44) << book[i].getName() << book[i].getID() << "\t\t";
                            cout << (book[i].getStatus() ? "Checked Out" : "Available");
                            cout << "\t" << book[i].getAuthorName() << endl;
                        }
                    }
                } else cout << "\nNo books were found matching '" << original << "'." << endl;
                
                found = false;
                for (unsigned int j = 0; j < magazine.size(); j++){
                    temp = magazine[j].getName();
                    toUpperCase(temp);
                    if (strstr(temp.c_str(), name.c_str())){
                        found = true;
                        break;
                    }
                }
                // If there were any magazines found matching the users input, display them in a table
                if (found){
                    cout << "\nMagazines matching '" << original << "':" << endl << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tIssue Number" << endl;
                    cout << "-------------------------------------------------------------------------------------";
                    cout << endl;
                    for (unsigned int j = 0; j < magazine.size(); j++){
                        temp = magazine[j].getName();
                        toUpperCase(temp);
                        if (strstr(temp.c_str(), name.c_str())){
                            cout << left << setw(44) << magazine[j].getName() << magazine[j].getID() << "\t\t";
                            cout << (magazine[j].getStatus() ? "Checked Out" : "Available");
                            cout << "\t" << magazine[j].getIssueNumber() << endl;
                        }
                    }
                } else cout << "\nNo magazines were found matching '" << original << "'." << endl;
                
                found = false;
                for (unsigned int k = 0; k < journal.size(); k++){
                        temp = journal[k].getName();
                        toUpperCase(temp);
                        if (strstr(temp.c_str(), name.c_str())){
                            found = true;
                            break;
                        }
                }
                // If there were any journals found matching the users input, display them in a table
                if (found){
                    cout << "\nJournals matching '" << original << "':" << endl << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tVolume" << endl;
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    for (unsigned int k = 0; k < journal.size(); k++){
                        temp = journal[k].getName();
                        toUpperCase(temp);
                        if (strstr(temp.c_str(), name.c_str())){
                            cout << left << setw(44) << journal[k].getName() << journal[k].getID() << "\t\t";
                            cout << (journal[k].getStatus() ? "Checked Out" : "Available");
                            cout << "\t" << journal[k].getVolume() << endl;
                        }
                    }
                } else cout << "\nNo journals were found matching '" << original << "'." << endl;
                
                break;
            case 2:
                cout << "Which category would you like to search for?" << endl;
                cout << "1. Books" << endl;
                cout << "2. Magazines" << endl;
                cout << "3. Journals" << endl;
                cout << "\n>> ";
                cin >> choice;
                
                if(cin.fail()) throw CinError();
                
                if (choice == 1){
                    // Display a table containing all the books on file
                    cout << "Books:\n" << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tAuthor" << endl;
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    
                    for (unsigned int i = 0; i < book.size(); i++){
                        cout << left << setw(44) << book[i].getName() << book[i].getID() << "\t\t";
                        cout << (book[i].getStatus() ? "Checked Out" : "Available");
                        cout << "\t" << book[i].getAuthorName() << endl;
                    }
                }
                
                else if (choice == 2){
                    // Display a table containing all the magazines on file
                    cout << "\nMagazines:\n" << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tIssue Number" << endl;
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    for (unsigned int j = 0; j < magazine.size(); j++){
                        cout << left << setw(44) << magazine[j].getName() << magazine[j].getID() << "\t\t";
                        cout << (magazine[j].getStatus() ? "Checked Out" : "Available");
                        cout << "\t" << magazine[j].getIssueNumber() << endl;
                    }
                }
                
                else if (choice == 3){
                    // Display a table containing all the journals on file
                    cout << "\nJournals:\n" << endl;
                    cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tVolume" << endl;
                    cout << "-------------------------------------------------------------------------------------" << endl;
                    for (unsigned int k = 0; k < journal.size(); k++){
                        cout << left << setw(44) << journal[k].getName() << journal[k].getID() << "\t\t";
                        cout << (journal[k].getStatus() ? "Checked Out" : "Available");
                        cout << "\t" << journal[k].getVolume() << endl;
                    }
                }
                else{
                    cout << "Error. Please enter a valid choice." << endl;
                    searchLibrary(book, magazine,journal);
                }
                break;
                
            case 3:
                cin.ignore();
                
                cout << "Enter the authors name: ";
                getline(cin, author);
                original = author;
                toUpperCase(author);
                cout << "Books matching author '" << original << "':\n" << endl;
                cout << left << setw(44) << "Name" << "ID" << "\t\tStatus\t\tAuthor" << endl;
                cout << "------------------------------------------------------------------------------------" << endl;
                for (unsigned int i = 0; i < book.size(); i++){
                    temp = book[i].getAuthorName();
                    toUpperCase(temp);
                    if (strstr(temp.c_str(), author.c_str())){
                        cout << left << setw(44) << book[i].getName() << book[i].getID() << "\t\t";
                        cout << (book[i].getStatus() ? "Checked Out" : "Available");
                        cout << "\t" << book[i].getAuthorName() << endl;
                    }
                }
                break;
                
            default:
                cout << "Error. Option not recognized. Please try again.\n" << endl;
                searchLibrary(book, magazine,journal);
                break;
        }
    }
    catch(CinError ce){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ce.what() << endl << "Please try again.\n" << endl;
        searchLibrary(book, magazine,journal);
    }
}

void checkOut(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    string id;
    bool found = false;
    
    // Asking the user to search for the item so
    // they can enter the correct ID of the item
    cout << "To check an item out, please find the item first." << endl;
    cout << "Once you have found it, please enter its unique ID.\n" << endl;
    searchLibrary(book, magazine, journal);
    
    cout << endl << "Enter the ID of the item you are checking out: ";
    cin >> id;
    toUpperCase(id);
    
    for (unsigned int i = 0; i < book.size(); i++){
        if (book[i].getID() == id){
            found = true;
            // If the book is available, check it out and change the status
            if(book[i].getStatus() == false){
                book[i].setStatus(true);
                cout << "Thank you for checking out " << book[i].getName() << "!" << endl;
            }
            else
                cout << "Sorry. This item has already been checked out." << endl;
            return; // Return to the main program if the item has been found
        }
    }

    for (unsigned int i = 0; i < magazine.size(); i++){
        if (magazine[i].getID() == id){
            found = true;
            // If the magazine is available, check it out and change the status
            if(magazine[i].getStatus() == false){
                magazine[i].setStatus(true);
                cout << "Thank you for checking out " << magazine[i].getName() << "!" << endl;
            }
            else
                cout << "Sorry. This item has already been checked out.";
            return; // Return to the main program if the item has been found
        }
    }
    
    for (unsigned int i = 0; i < journal.size(); i++){
        if (journal[i].getID() == id){
            found = true;
            // If the journal is available, check it out and change the status
            if(journal[i].getStatus() == false){
                journal[i].setStatus(true);
                cout << "Thank you for checking out " << journal[i].getName() << "!" << endl;
            }
            else
                cout << "Sorry. This item has already been checked out.";
            return; // Return to the main program if the item has been found
        }
    }
    
    // Prompt the user to try again if they entered an invalid ID
    if(!found){
        cout << "Error. The item matching the ID you entered was not found. Please try again.\n" << endl;
        checkOut(book, magazine, journal);
    }
    
}

void returnItem(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    string id;
    bool found = false;
    
    // Asking the user to search for the item so
    // they can enter the correct ID of the item
    cout << "To return an item out, please find the item first." << endl;
    cout << "Once you have found it, please enter its unique ID.\n" << endl;
    searchLibrary(book, magazine, journal);
    
    cout << endl << "Enter the ID of the item you are returning: ";
    cin >> id;
    toUpperCase(id);
    
    for (unsigned int i = 0; i < book.size(); i++){
        if (book[i].getID() == id){
            found = true;
            // If the book is checked out, return it and change the status
            if(book[i].getStatus() == true){
                book[i].setStatus(false);
                cout << "Thank you for returning " << book[i].getName() << "!" << endl;
            }
            else
                cout << "Error. This item is already available." << endl;
            return; // Return to the main program if the item has been found
        }
    }
    
    for (unsigned int i = 0; i < magazine.size(); i++){
        if (magazine[i].getID() == id){
            found = true;
            // If the book is checked out, return it and change the status
            if(magazine[i].getStatus() == true){
                magazine[i].setStatus(false);
                cout << "Thank you for returning " << magazine[i].getName() << "!" << endl;
            }
            else
                cout << "Error. This item is already available.";
            return; // Return to the main program if the item has been found
        }
    }
    
    for (unsigned int i = 0; i < journal.size(); i++){
        if (journal[i].getID() == id){
            found = true;
            // If the book is checked out, return it and change the status
            if(journal[i].getStatus() == true){
                journal[i].setStatus(false);
                cout << "Thank you for returning " << journal[i].getName() << "!" << endl;
            }
            else
                cout << "Error. This item is already available.";
            return; // Return to the main program if the item has been found
        }
    }
    
    // Prompt the user to try again if they entered an invalid ID
    if(!found){
        cout << "Error. The item matching the ID you entered was not found. Please try again.\n" << endl;
        returnItem(book, magazine, journal);
    }
}

void addItem(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    int op, volume, issueNumber;
    string name, author, id;
    
    try{
        cout << "\nWhich type of item would you like to add?" << endl;
        cout << "1. Book" << endl;
        cout << "2. Magazine" << endl;
        cout << "3. Journal\n" << endl;
        cout << ">> ";
        cin >> op;
        
        if (cin.fail()) throw CinError();
        cin.ignore();
        
        switch (op){
            case 1:
                try{
                    cout << "Enter the name of the book: ";
                    getline(cin, name);
                    cout << "Enter the name of the author: ";
                    getline(cin, author);
                    cout << "Enter the book's ID: ";
                    cin >> id;
                    toUpperCase(id);
                    // If an item matching the ID already exists, throw an exception.
                    if(doesExist(id, book, magazine, journal)) throw true;
                    book.push_back(Book(id, name, false, author));
                    cout << name << " was successfully added to the library!" << endl;
                } catch(bool i){
                    cout << "Error: An item matching this ID already exists." << endl;
                }
                break;
            case 2:
                try{
                    cout << "Enter the name of the magazine: ";
                    getline(cin, name);
                    cout << "Enter the magazine's issue number: ";
                    cin >> issueNumber;
                    if (cin.fail()) throw CinError();
                    cout << "Enter the magazine's ID: ";
                    cin >> id;
                    toUpperCase(id);
                    // If an item matching the ID already exists, throw an exception.
                    if(doesExist(id, book, magazine, journal)) throw true;
                    magazine.push_back(Magazine(id, name, false, issueNumber));
                    cout << name << " was successfully added to the library!" << endl;
                } catch(bool i){
                    cout << "Error: An item matching this ID already exists." << endl;
                }
                break;
            case 3:
                try{
                    cout << "Enter the name of the journal: ";
                    getline(cin, name);
                    cout << "Enter the volume of the journal: ";
                    cin >> volume;
                    if (cin.fail()) throw CinError();
                    cout << "Enter the journal's ID: ";
                    cin >> id;
                    toUpperCase(id);
                    // If an item matching the ID already exists, throw an exception.
                    if(doesExist(id, book, magazine, journal)) throw true;
                    journal.push_back(Journal(id, name, false, volume));
                    cout << name << " was successfully added to the library!" << endl;
                } catch(bool i){
                    cout << "Error: An item matching this ID already exists." << endl;
                }
                break;
            default:
                cout << "Sorry, that option was not recognized. Please try again." << endl;
                addItem(book, magazine, journal);
                break;
        }
    }
    catch(CinError ce){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ce.what() << endl;
    }
    
}

// Accepts a structure specific file to save library database
// @param - three vectors of type book, magazine, and journal, respectively.
void saveData(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    ofstream saveData;
    saveData.open("data.txt");
    
    if(saveData.is_open()){
        // Write to the file the number of each type of element
        // so it can be read lated and correctly loaded
        saveData << "Books " << book.size() << endl;
        saveData << "Magazines " << magazine.size() << endl;
        saveData << "Journal " << journal.size() << endl;
        for(unsigned int i = 0; i < book.size(); i++){
            saveData << book[i].getName() << "\n" << book[i].getID()
                     << "\n" << book[i]. getStatus() << "\n" << book[i].getAuthorName() << endl;
        }
        
        for(unsigned int i = 0; i < magazine.size(); i++){
            saveData << magazine[i].getName() << "\n" << magazine[i].getID()
                     << "\n" << magazine[i]. getStatus() << "\n" << magazine[i].getIssueNumber() << endl;
        }
        
        for(unsigned int i = 0; i < journal.size(); i++){
            saveData << journal[i].getName() << "\n" << journal[i].getID()
            << "\n" << journal[i]. getStatus() << "\n" << journal[i].getVolume();
            if (i != journal.size() - 1) saveData << endl;
        }
        saveData.close();
        cout << "The library information was successfully saved to 'data.txt'!" << endl;
    }
    
    // If the file can't be saved for any reason (i.e: no memory), display an error.
    else
        cout << "Error: Library information couldn't be saved." << endl;
}

// Accepts a structure specific file to load library database
// @param - three vectors of type book, magazine, and journal, respectively.
void loadData(vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    string fileName, temp, id, name, author;
    int bookSize, magSize, journalSize;
    int issueNum = 0, volume = 0;
    bool status;
    
    // Temporary vector of string type that will hold file contents
    vector<string> items;
    
    // Prompt the user for input and declare an ifstream object for reading the file
    cout << "Enter the filename you would like to load (i.e: data.txt): ";
    cin >> fileName;
    
    ifstream getData;
    getData.open(fileName.c_str());
    
    // If the file exists, perform the operations necessary to load it.
    if(getData.is_open()){
        try{
            // Clearing the current (preloaded) vectors
            // and replacing them with the users data
            book.clear();
            magazine.clear();
            journal.clear();
            
            // The program will read the size of each vector to
            // control the for loops necessary for reading data
            getData >> temp >> bookSize >> temp >> magSize >> temp >> journalSize;
            if(getData.fail()) throw CinError("Could not read file: Incorrect file structure.");
            getData.ignore();
            
            int bookArr = bookSize * 4;
            int magArr = magSize * 4;
            int journalArr = journalSize * 4;
            
            // While the file is still being read, accept each line and store it in a string vector
            while(!getData.eof()){
                getline(getData, temp);
                items.push_back(temp);
            }
            
            // Reading the 'Books' data and parsing it into the book vector
            for(unsigned int i = 0; i < bookArr; i = i + 4){
                name = items[i];
                id = items[i + 1];
                author = items[i + 3];
                if(items[i + 2] == "1") status = true;
                else status = false;
                book.push_back(Book(id, name, status, author));
            }
            
            // Reading the 'Magazines' data and parsing it into the magazine vector
            for(unsigned int i = bookSize * 4; i < bookArr + magArr; i += 4){
                name = items[i];
                id = items[i + 1];
                if(items[i + 2] == "1") status = true;
                else status = false;
                issueNum = stringToInt(items[i + 3]);
                magazine.push_back(Magazine(id, name, status, issueNum));
            }
            
            // Reading the 'Journal' data and parsing it into the journal vector
            for(unsigned int i = bookArr + magArr; i < bookArr + magArr + journalArr; i += 4){
                name = items.at(i);
                id = items[i + 1];
                if(items[i + 2] == "1") status = true;
                else status = false;
                volume = stringToInt(items[i + 3]);
                journal.push_back(Journal(id, name, status, volume));
            }
            // Close the file and display a message to the user.
            getData.close();
            cout << "The file '" << fileName << "' was loaded successfully!" << endl;
        }
        catch(CinError ce){
            getData.clear();
            getData.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ce.what() << endl;
            // If the file fails to read after clearing the vectors, reload the pre-existing data.
            loadCatalog(book, magazine, journal);
        }
    }
    
    // If the file doesn't exist, produce an error message and resume the program.
    else
        cout << "Error: The file was not loaded." << endl;
    
}

// Converts a string to an integer
int stringToInt(string stringNum){
    int number = 0;
    int i = 0;
    unsigned long stringLength = stringNum.length();
    
    // Converting the string a base 10 (decimal) number using a while loop
    while (i < stringLength ) {
        int digit = stringNum[i++] - '0';
        number *= 10;
        number += digit;
    }

    return number;
}


// Checks whether an item already exists and returns a boolean true or false
bool doesExist(string id, vector<Book> &book, vector<Magazine> &magazine, vector<Journal> &journal){
    
    // Check if a matching ID already exists and return true if it does
    for (unsigned int i = 0; i < book.size(); i++)
        if(book[i].getID() == id){
            return true;
        }

    for (unsigned int i = 0; i < magazine.size(); i++)
        if(magazine[i].getID() == id){
            return true;
        }

    for (unsigned int i = 0; i < journal.size(); i++)
        if(journal[i].getID() == id){
            return true;
        }
    
    // If an ID matching the ID entered by the librarian is false, return false.
    return false;
}

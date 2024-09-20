#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Book {
protected:
  string title;
  string author;
  string bookDetails;
  string type;
  int yearOfPublication;

public:
  Book(){};
  virtual ~Book(){};
  virtual void displayInfo() = 0;
  virtual void setBookDetails() = 0;
  string getBookDetails() { return bookDetails; }
};

class Fiction : public Book {
  string genre;

public:
  Fiction() { type = "Fiction"; }
  void displayInfo() { cout << bookDetails; }
  void setBookDetails() {
    cout << "--Please enter the " << type << " Book detail--" << endl;
    cout << "Title : ";
    getline(cin, title);
    cout << "Author : ";
    getline(cin, author);
    cout << "Year of Publication : ";
    cin >> yearOfPublication;
    cout << "Genre : ";
    cin.ignore();
    getline(cin, genre);
    bookDetails = "---------------------\nTitle : " + title +
                  "\nType : " + type + "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
                  "\nGenre : " + genre + '\n';
  }
};

class NonFiction : public Book {
  string subject;

public:
  NonFiction() { type = "Non Fiction"; }
  void displayInfo() { cout << bookDetails; }
  void setBookDetails() {
    cout << "--Please enter the " << type << " Book detail--" << endl;
    cout << "Title : ";
    getline(cin, title);
    cout << "Author : ";
    getline(cin, author);
    cout << "Year of Publication : ";
    cin >> yearOfPublication;
    cout << "Subject : ";
    cin.ignore();
    getline(cin, subject);
    bookDetails = "---------------------\nTitle : " + title +
                  "\nType : " + type + "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
                  "\nSubject : " + subject + '\n';
  }
};

int main() {
  string filename = "library.txt";
  int noOfBooks = 10;
  Book *books[noOfBooks];

  for (int i = 0; i < noOfBooks; i++) {
  rerun:
    char bookType;
    string bookData;
    cout << "Add a NonFiction/Fiction (N/F) : ";
    cin >> bookType;
    cin.ignore();
    switch (bookType) {
    case 'F':
      books[i] = new Fiction;
      books[i]->setBookDetails();
      bookData = books[i]->getBookDetails();
      break;
    case 'N':
      books[i] = new NonFiction;
      books[i]->setBookDetails();
      bookData = books[i]->getBookDetails();
      break;
    default:
      cout << "Please enter correct format either N or F" << endl;
      goto rerun;
    }
    ofstream file(filename, ios::app);
    if (file) {
      cout << "Successfully Saved to library.txt\n";
      file << bookData;
    } else {
      cout << "Failed to Save to file\n";
    }
    file.close();
  }
  ifstream file(filename, ios::in);
  if (file) {
    string text;
    cout << "---------------------" << endl;
    cout << "--Reading File Content--" << endl;
    while (getline(file, text)) {
      cout << text << endl;
    }
    cout << "---------------------" << endl;
    cout << "--End of File Content--" << endl;
    cout << "---------------------" << endl;
  } else {
    cout << "Failed to read from file.\n";
  }

  return 0;
}

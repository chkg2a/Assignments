#include <fstream>
#include <iostream>

using namespace std;

class Book {
protected:
  string title;
  string author;
  string bookDetails;
  string type;
  int yearOfPublication;
  static int noOfBooksAdded;

public:
  Book() { noOfBooksAdded++; };
  virtual ~Book(){};
  virtual void displayInfo() = 0;
  virtual void setBookDetails() = 0;
  string getBookDetails() { return bookDetails; }
};

class Fiction final : public Book {
  string genre;

public:
  Fiction() { type = "Fiction"; }
  void displayInfo() override { cout << bookDetails; }
  void setBookDetails() override {
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
                  "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
                  "\nID : " + to_string(noOfBooksAdded) + "\nType : " + type +
                  "\nGenre : " + genre + '\n';
  }
};

class NonFiction final : public Book {
  string subject;

public:
  NonFiction() { type = "Non Fiction"; }
  void displayInfo() override { cout << bookDetails; }
  void setBookDetails() override {
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
                  "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
                  "\nID : " + to_string(noOfBooksAdded) + "\nType : " + type +
                  "\nSubject : " + subject + '\n';
  }
};

class File {
  string filename;
  ifstream iFile;
  ofstream oFile;

public:
  File() {
    filename = "library.txt";
    try{
      iFile.open(filename);
      if(!iFile){
        throw filename + " doesn't exist";
      }
    }
    catch(const char * error){
      cout << error << endl;
      cout << "Created a new empty File" << endl;
      saveData("", ios::out);
    }
    catch(...){
      cout << "Unexpected Error occurred" << endl;
    }
    iFile.close();
  }
  File(string fn) {
    filename = fn;
    try{
      iFile.open(filename);
      if(!iFile){
        throw filename + " doesn't exist";
      }
    }
    catch(const char * error){
      cout << error << endl;
      cout << "Create a new empty File" << endl;
      saveData("", ios::out);
    }
    catch(...){
      cout << "Unexpected Error occurred" << endl;
    }
    iFile.close();
  }
  ~File() {
    iFile.close();
    oFile.close();
  }
  void saveData(string text, ios_base::openmode __mode) {
    cout << "Saving to file" << endl;
    oFile.open(filename, __mode);
    if(oFile){
      cout << text;
      oFile << text;
    }
  }
  string readData() {
    string text;
    string finalText = "";
    iFile.open(filename, ios::in);
    while (getline(iFile, text)) {
      finalText += text + '\n';
    }
    return finalText;
  }
};

int Book::noOfBooksAdded = 0;

int main() {
  int noOfBooks = 2;

  Book *books[noOfBooks];
  File fileObj;

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
    fileObj.saveData(bookData, ios::out);
  }

  cout << fileObj.readData();

  return 0;
}

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
    bookDetails = "---------------------\nID : " + to_string(noOfBooksAdded) + 
                  "\nTitle : " + title +
                  "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
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
    bookDetails = "---------------------\nID : " + to_string(noOfBooksAdded) + 
                  "\nTitle : " + title +
                  "\nType : " + type +
                  "\nAuthor : " + author +
                  "\nYear Of Publication : " + to_string(yearOfPublication) +
                  "\nSubject : " + subject + '\n';
  }
};

class File {
  string filename;
  ifstream iFile;
  ofstream oFile;

public:
  File() { filename = "library.txt"; }
  File(string fn) { filename = fn; }
  ~File() {
    iFile.close();
    oFile.close();
  }
  void saveData(string text, ios_base::openmode __mode) {
    oFile.open(filename, __mode);
    if (!oFile) {
      cerr << "ERROR couldn't save";
      return;
    }
    cout << "Saving to file" << endl;
    oFile << text;
    oFile.close();
  }
  string readData() {
    string text;
    string finalText = "";
    iFile.open(filename, ios::in);
    if (!iFile) {
      cerr << "Failed to read" << endl;
      return "";
    }
    while (getline(iFile, text)) {
      finalText += text + '\n';
    }
    iFile.close();
    return finalText;
  }
};

int Book::noOfBooksAdded = 0;

void replacePrevFileData() {
  cout << "Replacing Previous Data" << endl;
  File temp;
  temp.saveData("", ios::out);
}

int main() {
  int noOfBooks = 10;
  Book *books[noOfBooks];

  replacePrevFileData();

  for (int i = 0; i < noOfBooks; i++) {
    File fileObj;
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
    fileObj.saveData(bookData, ios::app);
  }

  File fileObj;

  cout << "---------------------" << endl;
  cout << "--Reading File Content--" << endl;
  cout << fileObj.readData();
  cout << "---------------------" << endl;
  cout << "--End of File Content--" << endl;
  cout << "---------------------" << endl;

  return 0;
}

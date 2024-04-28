#include <iostream>

using namespace std;

class Employee {
protected:
  string name;
  string role;
  float salary;
  float hoursWorked;
  float hourlyRate;
  float overTimeWork;
  virtual void calculatePay() = 0;

public:
  Employee(){
    name = "Default";
    role = "Default";
    salary = 0;
    hourlyRate = 0;
    overTimeWork = 0;
    hoursWorked = 0;
  };
  Employee & operator=(const Employee &) = delete;
  virtual ~Employee(){};
  virtual void getEmployeeData() = 0;
  virtual void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

class FullTimeEmployee final : public Employee {
  void calculatePay() override {}

public:
  FullTimeEmployee() {
    Employee::role = "Full-Time";
  }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Salary: ";
    cin >> salary;
    cin.ignore();
  }
};

class PartTimeEmployee final : public Employee {
  void calculatePay() override {
    if (hoursWorked > 40) {
      overTimeWork = hoursWorked - 40;
    }
    salary = ((hoursWorked - overTimeWork) * hourlyRate) +
             (overTimeWork * hourlyRate * 1.5);
  }

public:
  PartTimeEmployee() {
    Employee::role = "Part-Time";
  }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
  }
  void displayWeeklyPay() override{
    calculatePay();
    cout << name << " (" << role << "): $" << salary << " ("
         << hoursWorked - overTimeWork << " regular hours + " << overTimeWork
         << " overtime hours)" << endl;
  }
};

class Contractor final : public Employee {
  void calculatePay() override{ salary = hoursWorked * hourlyRate; }

public:
  Contractor() {
    Employee::role = "Contractor";
  }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
  }
};

int main(int argc, char *argv[]) {
  int noOfEmployees = 0;
  int noOfFullTime = 0;
  int noOfPartTime = 0;
  int noOfContractors = 0;

  cout << "You have a company" << endl;
  cout << "How many employees do you have?" << endl;
  cin >> noOfEmployees;

  Employee *ep[noOfEmployees];

  do {
    cout << "Please enter the correct number of employees." << endl;
    cout << "How many Full Times?" << endl;
    cin >> noOfFullTime;
    if ((noOfFullTime + noOfPartTime + noOfContractors) == noOfEmployees) {
      break;
    }
    cout << "How many Part Times?" << endl;
    cin >> noOfPartTime;
    if ((noOfFullTime + noOfPartTime + noOfContractors) == noOfEmployees) {
      break;
    }
    cout << "How many Contractors?" << endl;
    cin >> noOfContractors;
  } while ((noOfFullTime + noOfPartTime + noOfContractors) != noOfEmployees);

  cout << endl;

  while (true) {
    int z = 0;
    cin.ignore();
    for (int q = 0; q < noOfFullTime; q++) {
      ep[z] = new FullTimeEmployee;
      ep[z]->getEmployeeData();
      z++;
      cout << endl;
    }
    for (int q = 0; q < noOfPartTime; q++) {
      ep[z] = new PartTimeEmployee;
      ep[z]->getEmployeeData();
      z++;
      cout << endl;
    }
    for (int q = 0; q < noOfContractors; q++) {
      ep[z] = new Contractor;
      ep[z]->getEmployeeData();
      z++;
      cout << endl;
    }
    break;
  }

  cout << "Weekly Payroll:" << endl;
  for (int x = 0; x < noOfEmployees; x++) {
    ep[x]->displayWeeklyPay();
  }
  
  for (int i = 0; i < noOfEmployees; i++) {
    delete (ep[i]);
  }
  return 0;
}

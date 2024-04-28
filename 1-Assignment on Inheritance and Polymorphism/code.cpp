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
  Employee(){};
  virtual ~Employee(){};
  virtual void getEmployeeData() = 0;
  virtual void displayWeeklyPay() = 0;
};

class FullTimeEmployee : public Employee {
  void calculatePay() {}

public:
  FullTimeEmployee() {
    Employee::name = "Default";
    Employee::role = "Full-Time";
    Employee::salary = 0;
    Employee::hourlyRate = 0;
    Employee::hoursWorked = 0;
  }
  void getEmployeeData() {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Salary: ";
    cin >> salary;
    cin.ignore();
  }
  void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

class PartTimeEmployee : public Employee {
  void calculatePay() {
    if (hoursWorked > 40) {
      overTimeWork = hoursWorked - 40;
    }
    salary = ((hoursWorked - overTimeWork) * hourlyRate) +
             (overTimeWork * hourlyRate * 1.5);
  }

public:
  PartTimeEmployee() {
    Employee::name = "Default";
    Employee::role = "Part-Time";
    Employee::salary = 0;
    Employee::hourlyRate = 0;
    Employee::overTimeWork = 0;
    Employee::hoursWorked = 0;
  }
  void getEmployeeData() {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cin.ignore();
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
  }
  void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << " ("
         << hoursWorked - overTimeWork << " regular hours + " << overTimeWork
         << " overtime hours)" << endl;
  }
};

class Contractor : public Employee {
  void calculatePay() { salary = hoursWorked * hourlyRate; }

public:
  Contractor() {
    Employee::name = "Default";
    Employee::role = "Contractor";
    Employee::salary = 0;
    Employee::hourlyRate = 0;
    Employee::hoursWorked = 0;
  }
  void getEmployeeData() {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cin.ignore();
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
  }
  void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << endl;
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
  cin.ignore();

  Employee *ep[noOfEmployees];

  do {
    cout << "Please enter the correct number of employees." << endl;
    cout << "How many Full Times?" << endl;
    cin >> noOfFullTime;
    cin.ignore();
    if ((noOfFullTime + noOfPartTime + noOfContractors) == noOfEmployees) {
      break;
    }
    cout << "How many Part Times?" << endl;
    cin >> noOfPartTime;
    cin.ignore();
    if ((noOfFullTime + noOfPartTime + noOfContractors) == noOfEmployees) {
      break;
    }
    cout << "How many Contractors?" << endl;
    cin >> noOfContractors;
    cin.ignore();
  } while ((noOfFullTime + noOfPartTime + noOfContractors) != noOfEmployees);

  cout << endl;

  while (true) {
    int z = 0;
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

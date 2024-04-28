#include <iostream>

using namespace std;

class Employee {
protected:
  virtual void calculateSalary() = 0;

public:
  Employee(){};
  virtual ~Employee(){};
  virtual void getEmployeeData() = 0;
  virtual void displayWeeklyPay() = 0;
};

class FullTimeEmployee : public Employee {
  string name;
  string role;
  float salary;
  float hoursWorked;
  float hourlyRate;

  void calculateSalary() {}

public:
  FullTimeEmployee() {
    name = "Default";
    role = "Full-Time";
    salary = 0;
    hourlyRate = 0;
    hoursWorked = 0;
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
    calculateSalary();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

class PartTimeEmployee : public Employee {
  string name;
  string role;
  float salary;
  float hoursWorked;
  float hourlyRate;
  float overTimeWork;

  void calculateSalary() {
    if (hoursWorked > 40) {
      overTimeWork = hoursWorked - 40;
    }
    salary = ((hoursWorked - overTimeWork) * hourlyRate) +
             (overTimeWork * hourlyRate * 1.5);
  }

public:
  PartTimeEmployee() {
    name = "Default";
    role = "Part-Time";
    salary = 0;
    hourlyRate = 0;
    overTimeWork = 0;
    hoursWorked = 0;
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
    calculateSalary();
    cout << name << " (" << role << "): $" << salary << " ("
         << hoursWorked - overTimeWork << " regular hours + " << overTimeWork
         << " overtime hours)" << endl;
  }
};

class Contractor : public Employee {
  string name;
  string role;
  float salary;
  float hoursWorked;
  float hourlyRate;

  void calculateSalary() { salary = hoursWorked * hourlyRate; }

public:
  Contractor() {
    name = "Default";
    role = "Contractor";
    salary = 0;
    hourlyRate = 0;
    hoursWorked = 0;
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
    calculateSalary();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

int main(int argc, char *argv[]) {
  int noOfEmployees = 3;
  int noOfFullTime = 1;
  int noOfPartTime = 1;
  int noOfContractors = 1;

  Employee *ep[noOfEmployees];

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

  cout << "Weekly Payroll:" << endl;
  for (int x = 0; x < noOfEmployees; x++) {
    ep[x]->displayWeeklyPay();
  }

  for (int i = 0; i < noOfEmployees; i++) {
    delete (ep[i]);
  }
  return 0;
}

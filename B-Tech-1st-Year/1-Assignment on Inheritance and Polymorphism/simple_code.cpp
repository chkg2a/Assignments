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
  virtual ~Employee(){};
  virtual void getEmployeeData() = 0;
  virtual void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

class FullTimeEmployee : public Employee {
  void calculatePay() {}

public:
  FullTimeEmployee() {
    Employee::role = "Full-Time";
  }
  void getEmployeeData() {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Salary: ";
    cin >> salary;
    cin.ignore();
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
    Employee::role = "Part-Time";
  }
  void getEmployeeData() {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
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
    Employee::role = "Contractor";
  }
  void getEmployeeData() {
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

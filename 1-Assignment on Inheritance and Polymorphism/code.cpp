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
  Employee() {
    name = "Default";
    role = "Default";
    salary = 0;
    hourlyRate = 0;
    overTimeWork = 0;
    hoursWorked = 0;
  };
  Employee &operator=(const Employee &) = delete;
  virtual void displayEmployeeDetails(){
    cout << "--------------------------------"<< endl;
    cout << "Name : " << name << endl;
    cout << "Role : " << role << endl;
    cout << "Hourly Rate : " << hourlyRate << endl;
    cout << "Hours Worked : " << hoursWorked << endl;
    cout << "Salary : " << salary << endl;
  }
  virtual ~Employee(){};
  virtual void getEmployeeData() = 0;
  virtual void displayWeeklyPay() {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << endl;
  }
};

class FullTimeEmployee final : public Employee {
  void calculatePay() override {
    hoursWorked = salary/hourlyRate;
  }

public:
  FullTimeEmployee() { 
    Employee::role = "Full-Time"; 
    hourlyRate = 30;
  }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Salary: ";
    cin >> salary;
    cin.ignore();
    calculatePay();
  }
};

class PartTimeEmployee final : public Employee {
  void calculatePay() override {
    auto makeSalary = [&]() {
      overTimeWork = (hoursWorked > 40) ? hoursWorked - 40 : 0;
      return ((hoursWorked - overTimeWork) * hourlyRate) +
             (overTimeWork * hourlyRate * 1.5);
    };
    salary = makeSalary();
  }

public:
  PartTimeEmployee() { Employee::role = "Part-Time"; }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
    calculatePay();
  }
  void displayWeeklyPay() override {
    calculatePay();
    cout << name << " (" << role << "): $" << salary << " ("
         << hoursWorked - overTimeWork << " regular hours + " << overTimeWork
         << " overtime hours)" << endl;
  }
};

class Contractor final : public Employee {
  void calculatePay() override { Employee::salary = hoursWorked * hourlyRate; }

public:
  Contractor() { Employee::role = "Contractor"; }
  void getEmployeeData() override {
    cout << "Enter details for " << role << " Employee" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Hourly Rate: ";
    cin >> hourlyRate;
    cout << "Hours Worked: ";
    cin >> hoursWorked;
    cin.ignore();
    calculatePay();
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
  // cout << "Display Employee Details:" << endl;
  for (int x = 0; x < noOfEmployees; x++) {
    ep[x]->displayWeeklyPay();
    // ep[x]->displayEmployeeDetails();
  }

  for (int i = 0; i < noOfEmployees; i++) {
    delete (ep[i]);
  }
  return 0;
}

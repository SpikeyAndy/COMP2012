#include <iostream>
#include "Employee.h"
#include <cstring>

using namespace std;

//TODO: Complete conversion constructor
Employee::Employee(const char* name, double base_salary)




//TODO: Complete copy constructor
Employee::Employee(const Employee & employee)




Employee::~Employee(){
    cout << "Call destructor of Employee" <<endl;
// TODO: dynamic memory deallocation

}

// TODO: Complete Employee::get_name
string Employee::get_name() const{

}

// TODO: Complete Employee::get_base_salary
double Employee::get_base_salary() const{

}

// TODO: Complete Employee::get_salary. In the base class, salary is equal to base salary.
double Employee::get_salary() const{

}

void Employee::print() const{
    cout << "Employee: " << get_name() << endl;
    cout << "Salary: " << get_salary() << endl;
}
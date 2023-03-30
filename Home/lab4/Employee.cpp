#include <iostream>
#include "Employee.h"
#include <cstring>

using namespace std;

//TODO: Complete conversion constructor
Employee::Employee(const char* name, double base_salary) : base_salary(base_salary)
{
    char* name_ptr = new char[strlen(name) + 1];
    strcpy(name_ptr, name);
    this->name = name_ptr;
}


//TODO: Complete copy constructor
Employee::Employee(const Employee & employee) : base_salary(employee.base_salary)
{
    char* new_name = new char[strlen(employee.name) + 1];
    strcpy(new_name, employee.name);
    this->name = new_name;
}


Employee::~Employee(){
    cout << "Call destructor of Employee" <<endl;
// TODO: dynamic memory deallocation
    delete [] name;
}

// TODO: Complete Employee::get_name
string Employee::get_name() const{
    return name;

}

// TODO: Complete Employee::get_base_salary
double Employee::get_base_salary() const{
    return base_salary;
}

// TODO: Complete Employee::get_salary. In the base class, salary is equal to base salary.
double Employee::get_salary() const{
    return base_salary;
}

void Employee::print() const{
    cout << "Employee: " << get_name() << endl;
    cout << "Salary: " << get_salary() << endl;
}
#include <iostream>
#include "Full_time.h"

using namespace std;

// TODO: Complete the constructor of Full_time class. 
//       Remember to call the constructor of base class, use new to initialize char*position.
Full_time::Full_time(const char* name, double base_salary, const char* position, int seniority, double bonus)


Full_time::~Full_time() {
    cout << "Call destructor of Full_time" << endl;
// TODO: dynamic memory deallocation

}

// TODO: Complete Full_time::get_position
string Full_time::get_position() const{

}

// TODO: Complete Full_time::get_seniority
int Full_time::get_seniority() const{
    
}

// TODO: Complete Full_time::get_bonus
double Full_time::get_bonus() const{
   
}

// TODO: Complete Full_time::get_salary. Salary = base_salary + 0.1 * base_salary * seniority + bonus
double Full_time::get_salary() const{

}

void Full_time::print() const{
    cout << "Full_time employee: " << get_name() << ", position: " << get_position() << endl;
    cout << "Salary: " << get_salary() << endl;
}
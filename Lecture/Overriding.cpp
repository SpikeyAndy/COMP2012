#include <iostream>

using namespace std;

class A {
    int* p;
    int capacity;
    public:
        A(int capcity) : capacity(capcity) { p = new int[capacity]; cout << "constructing A" << endl;} // use MIL to call capacity to define the capacity
        A(const A& a) : A(a.capacity) {             //* use A MIL to call capacity and new capacity (deep copy) 
            for (int i = 0; i < capacity; i++) { //* need to manually deep copy the array
                p[i] = a.p[i];
            }
        }
        virtual ~A() { delete [] p; cout << "~A" << endl; }
};

class B : public A {
    int* q;
    int c;
    public:
        B(int c) : A(5), c(c) { q = new int[c]; cout << "constructing B"<< endl;} //* construct A and construct c
        B(const B& b) : B(b.c) {
            for (int i = 0; i < c; i++)
                q[i] = b.q[i];
        }
        ~B() { delete [] q; cout << "~B" << endl; }
};

int main() { //
    A* a = new B(5); // pass cv
    delete a;
}
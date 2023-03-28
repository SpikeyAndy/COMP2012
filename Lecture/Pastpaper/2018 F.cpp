class A {
int* p;
public:
A() { p = new int; }
~A() { delete p; }
};
int main() {
A obj1, obj2;
obj1 = obj2;
}

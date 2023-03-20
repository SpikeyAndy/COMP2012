

class Car {
    public:
        Car() { getSpeed();} //! >.< NOT ALLOWED to call a pure virtual function because there is no way to do it
        virtual double getSpeed() const = 0; //- this is a pure virtual function
                                             //* don't know how to implement, but is good for derived classes
};      /* if not virutal, then even if cp is AudiTT, it will ALWAYS call the getSpeed() function
           allow it to call the derive class function */


class AudiTT : public Car {
    public:
        double getSpeed() const { return 101;} // if we do not overwrite getspeed(), it will be a abstract function

        
}

int main() {
    Car c; // is this allowed? 
    Car* cp;
    AudiTT audi;
    Car& chaha = audi;
}
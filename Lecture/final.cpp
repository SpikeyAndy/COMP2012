class A {
    public:
        virtual void funct () final;
};

void A::func() final {

}

class B : public A {
    public:
    void func() override final; // or final override
};


int main() {
    B obj;
}
inline const int& larger(const int& a, const int & b)
{
    return (a<b) ? b : a;
}


// before function prototype

template <typename T>

inline const T& larger(const T& a, const T& b) // T is dummy type
{
    return (a<b) ? b : a;
}

intline const double& larger(const double& a, const double)
{
    //* do something different (function specialisation)

}
int main() {
    int x = 10;
    int y = 20;
    int a = larger(2.0, 5.0); //-> generate larger() as double
    int z = larger(x, y);     //! will still generate smaller larger() for int
    int a = larger(2.0, 5.0); //-> use the original function generated

    int c = larger(4, 5.5); // Error! >.< 2 different type

    //<explicit instantiation>
    cout << larger<double>(4, 5.5); //-> manually decide the type function
}
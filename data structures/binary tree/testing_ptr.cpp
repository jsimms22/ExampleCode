#include<iostream>

class IN
{
public:
    IN(int v) :value{v} { }
    int get_value() const { return value; }
private:
    int value;
};

std::ostream& operator<<(std::ostream& os, const IN& i)
{
    os << i.get_value();
    return os;
}

int main() {
    int i = 5;
    int* i_ptr = &i;

    std::cout << "i = " << i << '\n';
    std::cout << "&i = " << &i << '\n';
    std::cout << "i_ptr = " << i_ptr << '\n';
    std::cout << "*i_ptr = " << *i_ptr << '\n';

    IN* in = new IN(i);
    IN* yn = in;

    std::cout << "IN* in = " << in << '\n';
    std::cout << "IN* yn = " << yn << '\n';
    delete(in);
    std::cout << "IN* in was deleted.\n";
    std::cout << "IN* yn = " << yn << '\n';

    return 0;
}
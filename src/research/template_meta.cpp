#include <array>
#include <iostream>

template <int flag>
struct MetaPrint
{
    void print();
};

template <int flag>
void MetaPrint<flag>::print()
{
    std::cout << "Base Print, flag=" << flag << std::endl;
}

template <>
void MetaPrint<3>::print()
{
    std::cout << "Meta Print, flag=" << 3 << std::endl;
}

int main(int arg, char* argv[])
{
    MetaPrint<1> meta_print_1;
    MetaPrint<2> meta_print_2;
    MetaPrint<3> meta_print_3;

    meta_print_1.print();
    meta_print_2.print();
    meta_print_3.print();

    return 0;
}
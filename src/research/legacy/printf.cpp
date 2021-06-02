#include <iostream>

int main(int argc, char* argv[])
{
    char character = 'a';
    int integer = 126;
    float floating_point = 126.36;
    const char* str = "Hello World!";

    std::string d_fmt_str = ("  Base 10: printf(\"%%d\", " + std::to_string(integer) + ") = \"%d\"\n");
    std::string i_fmt_str = ("  Base 10: printf(\"%%i\", " + std::to_string(integer) + ") = \"%i\"\n");
    std::string o_fmt_str = ("  Base  8: printf(\"%%o\", " + std::to_string(integer) + ") = \"%o\"\n");
    std::string x_fmt_str = ("  Base 16: printf(\"%%x\", " + std::to_string(integer) + ") = \"%x\"\n");
    std::string u_fmt_str = (" Unsigned: printf(\"%%u\", " + std::to_string(integer) + ") = \"%u\"\n");
    std::string f_fmt_str = ("  Decimal: printf(\"%%f\", "  + std::to_string(floating_point) + ") = \"%f\"\n");
    std::string e_fmt_str = (" Exponent: printf(\"%%e\", "  + std::to_string(floating_point) + ") = \"%e\"\n");
    std::string c_fmt_str = ("Character: printf(\"%%c\", '" + std::string(1, character) + "') = \"%c\"\n");
    std::string s_fmt_str = ("   String: printf(\"%%s\", \"" + std::string(str) + "\") = \"%s\"\n");

    printf(d_fmt_str.c_str(), integer);
    printf(i_fmt_str.c_str(), integer);
    printf(o_fmt_str.c_str(), integer);
    printf(x_fmt_str.c_str(), integer);
    printf(u_fmt_str.c_str(), integer);
    printf(f_fmt_str.c_str(), floating_point);
    printf(e_fmt_str.c_str(), floating_point);
    printf(c_fmt_str.c_str(), character);
    printf(s_fmt_str.c_str(), str);
    return 0;
}
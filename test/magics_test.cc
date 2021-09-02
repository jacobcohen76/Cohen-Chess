#include <iomanip>
#include <iostream>
#include <string>

std::string LCS(std::string str1, std::string str2) {
    if (empty(str1) || empty(str2)) {
        return "";
    } else if (str1[0] == str2[0]) {
        return str1[0] + LCS(str1.substr(1), str2.substr(1));
    } else {
        std::string opt1 = LCS(str1.substr(1), str2);
        std::string opt2 = LCS(str1, str2.substr(1));
        return size(opt1) > size(opt2) ? opt1 : opt2;
    }
}

int main(int argc, char* argv[]) {
    --argc, ++argv;
    if (argc < 2) {
        std::cout << "Needed two string arguments!" << '\n';
        return 1;
    }
    std::string str1 = argv[0];
    std::string str2 = argv[1];
    std::string lcs  = LCS(str1, str2);
    std::cout << "LCS(" << std::quoted(str1) << ", "
                        << std::quoted(str2) << ") = "
                        << std::quoted(lcs)  << '\n';
    return 0;
}

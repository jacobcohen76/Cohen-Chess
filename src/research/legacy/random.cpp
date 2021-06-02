#include "../util/"

#include <cstdint>
#include <iostream>
#include <math.h>
#include <map>
#include <random>
#include <string>

int DigitCount(size_t n)
{
    return int(log10(n)) + 1;
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> pair)
{
    return os << "(" << pair.first << ", " << pair.second << ")";
}

int main(int argc, char* argv[])
{

    int lower = 0, upper = std::numeric_limits<int>::max();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(lower, upper);
    std::map<int, size_t> freq_count;

    size_t no_rolls = 30;
    const char* roll_fmt_str = ("roll %" + std::to_string(DigitCount(no_rolls)) + "llu = %i\n").c_str();
    for(size_t i = 0; i < no_rolls; ++i)
    {
        int rolled = distribution(generator);
        printf(roll_fmt_str, i, rolled);
        ++freq_count[rolled];
    }

    const char* freq_fmt_str = ("%" + std::to_string(DigitCount(std::max(lower, upper))) + "i: %5.2f%%\n").c_str();
    for(auto kv_pair : freq_count)
    {
        float k_freq_percent = float(kv_pair.second) / no_rolls * 100.0;
        printf(freq_fmt_str, kv_pair.first, k_freq_percent);
    }
    return 0;
}
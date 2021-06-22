#include <iostream>
#include <vector>

template <typename T>
class Stack : private std::vector<T>
{
public:
    using std::vector<T>::vector;
    using std::vector<T>::size;

    using std::vector<T>::begin;
    using std::vector<T>::cbegin;
    using std::vector<T>::rbegin;
    using std::vector<T>::crbegin;

    using std::vector<T>::end;
    using std::vector<T>::cend;
    using std::vector<T>::rend;
    using std::vector<T>::crend;

    inline void push(const T& item)
    {
        this->push_back(item);
    }

    inline T pop()
    {
        auto item = this->back();
        this->pop_back();
        return item;
    }
};

int main(int argc, char* argv[])
{
    auto test = {1, 2, 3};
    Stack<int> stack;
    stack.push(3);
    stack.push(4);
    stack.push(5);
    std::cout << stack.pop() << "," << stack.size() << std::endl;
    std::cout << stack.pop() << "," << stack.size() << std::endl;
    std::cout << stack.pop() << "," << stack.size() << std::endl;
    return 0;
}


int main(int argc, char* argv[])
{
    auto f = []<typename ...Ts>(Ts&& ...ts)
    {
        return foo(std::forward<Ts>(ts)...);
    };
    return 0;
}

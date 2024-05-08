#include <Insight/Insight.hpp>

#include <iostream>

class Test
{
public:
    Test() = default;
    virtual ~Test() = default;

    inline void TEST()
    {
        abc = 69;
    }

private:

} INSIGHT_CLASS(Test);

int main(int argc, char* argv[])
{
    Insight::Internal::Classes& classes = Insight::Internal::ClassSymbols;

    return 0;
}
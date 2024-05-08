#include <Insight/Insight.hpp>

class Test
{
public:
    Test() = default;
    virtual ~Test() = default;

private:
    INSIGHT_FIELD(INSIGHT_PRIVATE, Test, int, abc, 10);

} INSIGHT_CLASS(Test);

INSIGHT_FIELD_EXPORT(INSIGHT_PRIVATE, Test, int, abc);
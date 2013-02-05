#include "PowTest.hpp"
#include "Pow.hpp"
#include "StateGenerator.hpp"
#include "Constant.hpp"
#include "Serialize.hpp"

PowTest::PowTest() : a(DataGenerator(171429)), generate(StateGenerator())
{
}

void PowTest::SetUp()
{
}

void PowTest::TearDown()
{
}


TEST_F(PowTest, should_be_able_to_define_x_power_something)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const auto x = generate.state(a.random<std::string>());
        **x = a.random<double>().between(-20,20);
        const double exp = a.random<double>().between(-5,5);
        const auto x2 = Pow(x,exp);
        ASSERT_EQ(pow(**x,exp), x2.get_value()());
    }
}

TEST_F(PowTest, derivative)
{
    const auto x = generate.state("x");
    const std::tr1::shared_ptr<Parameter> n(new Parameter(10));
    const auto x_pow_n = Pow(x,n);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(0,20);
        **n = a.random<double>().between(1,5);
        ASSERT_DOUBLE_EQ((**n)*pow(**x,(**n)-1), x_pow_n.diff(x)->get_value()());
    }
}
/*
 * SimplifyTest.hpp
 *
 * \date 13 f�vr. 2013, 08:57:17
 *  \author cec
 */

#ifndef SIMPLIFYTEST_HPP_
#define SIMPLIFYTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class SimplifyTest : public ::testing::Test
{
    protected:
        SimplifyTest();
        virtual ~SimplifyTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        StateGenerator generate;
        StatePtr x1;
        StatePtr x2;
        StatePtr x3;
};

#endif  /* SIMPLIFYTEST_HPP_ */

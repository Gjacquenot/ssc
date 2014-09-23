/*
 * kahan_sumTest.hpp
 *
 *  Created on: May 19, 2014
 *      Author: cady
 */

#ifndef KAHAN_SUMTEST_HPP_
#define KAHAN_SUMTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class kahan_sumTest : public ::testing::Test
{
    protected:
        kahan_sumTest();
        virtual ~kahan_sumTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* KAHAN_SUMTEST_HPP_ */

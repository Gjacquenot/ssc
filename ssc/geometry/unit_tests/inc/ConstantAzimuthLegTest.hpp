/*
 * ConstantAzimuthLegTest.hpp
 *
 *  Created on: May 14, 2014
 *      Author: cady
 */

#ifndef CONSTANTAZIMUTHLEGTEST_HPP_
#define CONSTANTAZIMUTHLEGTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class ConstantAzimuthLegTest : public ::testing::Test
{
    protected:
        ConstantAzimuthLegTest();
        virtual ~ConstantAzimuthLegTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* CONSTANTAZIMUTHLEGTEST_HPP_ */

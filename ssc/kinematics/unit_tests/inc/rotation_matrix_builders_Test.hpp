#ifndef ROTATION_MATRIX_BUILDERS_TEST_HPP_
#define ROTATION_MATRIX_BUILDERS_TEST_HPP_

#include "gtest/gtest.h"
#include "random_data_generator/DataGenerator.hpp"

class rotation_matrix_builders_Test : public ::testing::Test
{
    protected:
        rotation_matrix_builders_Test();
        virtual ~rotation_matrix_builders_Test();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

};

#endif  /* ROTATION_MATRIX_BUILDERS_TEST_HPP_ */

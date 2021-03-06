#ifndef KINEMATICSTESTS_HPP_
#define KINEMATICSTESTS_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"

class Kinematics;
class KinematicsTests : public ::testing::Test
{
    protected:
        KinematicsTests();
        virtual ~KinematicsTests();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;

        void add_frame(Kinematics& k, const std::string& name, const double x, const double y, const double z, const double phi, const double theta, const double psi) const;
};

#endif  /* KINEMATICSTESTS_HPP_ */

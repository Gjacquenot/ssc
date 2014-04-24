/*
 * KinematicsTests.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: maroff
 */

#include "KinematicsTests.hpp"
#include "Kinematics.hpp"
#include "random_kinematics.hpp"
#include "test_macros.hpp"
#include "almost_equal.hpp"
#include "KinematicsException.hpp"

#define EPS 1E-13

bool double_equal(const kinematics::Transform& t1, const kinematics::Transform& t2, const double eps=0);
bool double_equal(const kinematics::Transform& t1, const kinematics::Transform& t2, const double eps)
{
    if (t1.get_from_frame() != t2.get_from_frame())
    {
        std::cerr << "'from' frames don't match:" << std::endl;
        std::cerr << "t1 : " << t1.get_from_frame() << " -> " << t1.get_to_frame() << std::endl;
        std::cerr << "t2 : " << t2.get_from_frame() << " -> " << t2.get_to_frame() << std::endl;
        return false;
    }
    if (t1.get_to_frame() != t2.get_to_frame())
    {
        std::cerr << "'to' frames don't match." << std::endl;
        std::cerr << "t1 : " << t1.get_from_frame() << " -> " << t1.get_to_frame() << std::endl;
        std::cerr << "t2 : " << t2.get_from_frame() << " -> " << t2.get_to_frame() << std::endl;
        return false;
    }
    const Point u1(t1.get_from_frame(), 1, 0, 0);
    const Point u2(t1.get_from_frame(), 0, 1, 0);
    const Point u3(t1.get_from_frame(), 0, 0, 1);

    const Point u11 = t1*u1;
    const Point u12 = t1*u2;
    const Point u13 = t1*u3;
    const Point u21 = t2*u1;
    const Point u22 = t2*u2;
    const Point u23 = t2*u3;

    const std::vector<double> std_u11(&u11.x, &u11.x + 3);
    const std::vector<double> std_u12(&u12.x, &u12.x + 3);
    const std::vector<double> std_u13(&u13.x, &u13.x + 3);
    const std::vector<double> std_u21(&u21.x, &u21.x + 3);
    const std::vector<double> std_u22(&u22.x, &u22.x + 3);
    const std::vector<double> std_u23(&u23.x, &u23.x + 3);

    if (not(almost_equal(std_u11, std_u21, eps)))
    {
        std::cerr << "t1*(1,0,0) = " << u11.v.transpose() << std::endl;
        std::cerr << "t2*(1,0,0) = " << u21.v.transpose() << std::endl;
        return false;
    }

    if (not(almost_equal(std_u12, std_u22, eps)))
    {
        std::cerr << "t1*(0,1,0) = " << u12.v.transpose() << std::endl;
        std::cerr << "t2*(0,1,0) = " << u22.v.transpose() << std::endl;
        return false;
    }
    if (not(almost_equal(std_u13, std_u23, eps)))
    {
        std::cerr << "t1*(0,0,1) = " << u13.v.transpose() << std::endl;
        std::cerr << "t2*(0,0,1) = " << u23.v.transpose() << std::endl;
        return false;
    }

    return true;
}

KinematicsTests::KinematicsTests() : a(DataGenerator(122))
{
}

KinematicsTests::~KinematicsTests()
{
}

void KinematicsTests::SetUp()
{
}

void KinematicsTests::TearDown()
{
}

TEST_F(KinematicsTests, can_add_a_transform_to_a_kinematics_object)
{
    Kinematics k;
    const auto bTa = random_transform(a, a.random<std::string>(), a.random<std::string>());
    k.add(bTa);
}

TEST_F(KinematicsTests, can_retrieve_a_transform)
{
	Kinematics k;
	const std::string from_frame = a.random<std::string>();
	const std::string to_frame = a.random<std::string>();
	const auto bTa = random_transform(a, from_frame, to_frame);
	k.add(bTa);
	const auto transform = k.get(from_frame, to_frame);
	ASSERT_TRUE(double_equal(transform, bTa));
}

TEST_F(KinematicsTests, can_retrieve_inverse_transform)
{
    //! [KinematicsTests get_example]
    Kinematics k;
    const std::string from_frame = a.random<std::string>();
    const std::string to_frame = a.random<std::string>();
    const auto bTa = random_transform(a, from_frame, to_frame);
    k.add(bTa);
    const auto aTb = k.get(to_frame, from_frame);
    //! [KinematicsTests get_example]
    //! [KinematicsTests get_example output]
    ASSERT_TRUE(double_equal(kinematics::identity(from_frame), aTb*bTa, EPS));
    ASSERT_TRUE(double_equal(kinematics::identity(to_frame), bTa*aTb, EPS));
    //! [KinematicsTests get_example output]
}

TEST_F(KinematicsTests, throws_if_transform_is_not_computable)
{
    Kinematics k;
    ASSERT_THROW(k.get(a.random<std::string>(),a.random<std::string>()), KinematicsException);
}

TEST_F(KinematicsTests, can_compute_a_transformation_if_necessary_and_feasible)
{
    Kinematics k;

    const auto bTa = random_transform(a, "A", "B");
    const auto cTa = random_transform(a, "A", "C");
    const auto dTb = random_transform(a, "B", "D");
    const auto eTc = random_transform(a, "C", "E");
    const auto fTc = random_transform(a, "C", "F");
    const auto gTd = random_transform(a, "D", "G");
    const auto hTd = random_transform(a, "D", "H");
    const auto iTd = random_transform(a, "D", "I");
    const auto dTe = random_transform(a, "E", "D");

    k.add(bTa);
    k.add(cTa);
    k.add(dTb);
    k.add(eTc);
    k.add(fTc);
    k.add(gTd);
    k.add(hTd);
    k.add(iTd);
    k.add(dTe);

    const auto hTe = k.get("E", "H");

    ASSERT_TRUE(double_equal(hTe, hTd*dTe, EPS));
}

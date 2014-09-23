/*
 * ParabolicRunoutSplines.cpp
 *
 * \date 1 ao�t 2012, 09:50:24
 *  \author cec
 */

#include "interpolation/ParabolicRunoutSplines.hpp"

using namespace ssc::interpolation;

ParabolicRunoutSplines::ParabolicRunoutSplines() : Splines()
{
	M = (h != 0) ? compute_second_derivative() : std::vector<double>(2,0);
}

ParabolicRunoutSplines::ParabolicRunoutSplines(const double& xmin_, const double& xmax_, const std::vector<double>& y) : Splines(xmin_, xmax_,y)
{
	M = (h != 0) ? compute_second_derivative() : std::vector<double>(2,0);
}

double ParabolicRunoutSplines::get_endpoint_value() const
{
	return 5;
}

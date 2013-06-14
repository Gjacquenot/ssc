/*
 * Interpolator.cpp
 *
 * \date 12 juin 2013, 15:26:56
 *  \author cec
 */

#include "Interpolator.hpp"
#include "InterpolatorException.hpp"
#include <cmath>

#include "test_macros.hpp"

Interpolator::Interpolator() :
xmin(0), xmax(0), y(std::vector<double>()), n(0), delta(0), idx(0), val_sat(0), coefficients_have_been_computed_for_interval(std::vector<bool>())
{

}

Interpolator::Interpolator(const double& xmin_,
        const double& xmax_,
        const std::vector<double>& y_) : xmin(xmin_), xmax(xmax_), y(y_), n(y.size()), delta(0), idx(0), val_sat(xmin)
        , coefficients_have_been_computed_for_interval(std::vector<bool>())
{
    if (n == 0)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "y must have at least one element.");
    }
    if (xmin>xmax)
    {
        THROW(__PRETTY_FUNCTION__, InterpolatorException, "xmin>xmax");
    }
    delta = n==1 ? (xmax-xmin) : (xmax-xmin)/double(n-1);
    coefficients_have_been_computed_for_interval = std::vector<bool>(n-1,false);
}

void Interpolator::update_index(const double val)
{
    val_sat = std::max(xmin,std::min(xmax,val));
    idx = (n==1) ? 0 : floor((val_sat-xmin)/(xmax-xmin)*(n-1));
    idx = std::min(idx,n-2);
}

double Interpolator::f(const double x)
{
    update_index(x);
    if (idx >= coefficients_have_been_computed_for_interval.size() || not(coefficients_have_been_computed_for_interval.at(idx)))
    {
        compute_coefficients_for_ith_interval(x,idx);
    }
    return get_f();
}

double Interpolator::df(const double x, const size_t derivative_order)
{
    update_index(x);
    if (idx >= coefficients_have_been_computed_for_interval.size() || not(coefficients_have_been_computed_for_interval.at(idx)))
    {
        compute_coefficients_for_ith_interval(x,idx);
    }
    return get_df(derivative_order);
}


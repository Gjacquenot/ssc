/*
 * AddPointToIntegral.cpp
 *
 * \date 10 juin 2013, 10:10:32
 *  \author cec
 */

#include "AddPointToIntegral.hpp"


/** \author cec
 *  \date 10 juin 2013, 10:24:41
 *  \brief Integrates a function between two points
 *  \returns Previous value of the integral augmented by integral between x1 and x2
 *  \snippet integrate/unit_tests/src/AddPointToIntegralTest.cpp AddPointToIntegralTest integrate_example
*/
double integrate(double previous_value_of_the_integral, //!< Value of the integral computed so far (until x1)
                 double y1, //<! Value of the function to integrate, at x1
                 double y2, //<! Value of the function to integrate, at x2
                 double Dx  //<! Length of the interval on which to integrate
                 )
{
    return previous_value_of_the_integral + Dx*(y1+y2)/2.;
}
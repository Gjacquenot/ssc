/*
 * ParabolicCoefficients.hpp
 *
 * \date 19 f�vr. 2013, 11:20:00
 *  \author cec
 */

#ifndef PARABOLICCOEFFICIENTS_HPP_
#define PARABOLICCOEFFICIENTS_HPP_


struct ParabolicCoefficients
{
    public:
        ParabolicCoefficients(const double& a_, const double& b_, const double& c_);
        double a;
        double b;
        double c;

    private:
        ParabolicCoefficients();
};

#endif /* PARABOLICCOEFFICIENTS_HPP_ */

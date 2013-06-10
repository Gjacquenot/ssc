/*
 * TrapezoidalIntegration.hpp
 *
 * \date 23 avr. 2013, 14:47:21
 *  \author cec
 */

#ifndef TRAPEZOIDALINTEGRATION_HPP_
#define TRAPEZOIDALINTEGRATION_HPP_

#include "Integrator.hpp"
#include <tr1/memory>

/** \author cec
 *  \brief This class was created to
 *  \ingroup quadpack
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet quadpack/unit_tests/src/TrapezoidalIntegrationTest.cpp TrapezoidalIntegrationTest example
 *  \section ex2 Expected output
 *  \snippet quadpack/unit_tests/src/TrapezoidalIntegrationTest.cpp TrapezoidalIntegrationTest expected output
 */

class TrapezoidalIntegration : public Integrator
{
    public:
        TrapezoidalIntegration(const Function& f);
        double integrate(const double& a, const double& b, const double& eps=1e-6) const;

    private:
        class Impl;
        std::tr1::shared_ptr<Impl> pimpl;
};

#endif /* TRAPEZOIDALINTEGRATION_HPP_ */

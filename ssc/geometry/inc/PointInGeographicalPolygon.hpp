/*
 * PointInGeographicalPolygon.hpp
 *
 * \date 27 mars 2013, 15:57:40
 *  \author cec
 */

#ifndef POINTINGEOGRAPHICALPOLYGON_HPP_
#define POINTINGEOGRAPHICALPOLYGON_HPP_

#include "PointInPolygon.hpp"

/** \author cec
 *  \brief This class was created to determine if a point is inside a polygon (taken on the WGS84 ellipsoid)
 *  \details  The points are given in (longitude,latitude) in degrees. The ellipsoid parameters are:
 *  - Transverse radius a = 6378137.0 m
    - Conjugate radius b = 6356752.314245 m
 *  \section ex1 Example
 *  \snippet ECA_zones/unit_tests/src/PointInGeographicalPolygonTest.cpp PointInGeographicalPolygonTest example
 *  \section ex2 Expected output
 *  \snippet ECA_zones/unit_tests/src/PointInGeographicalPolygonTest.cpp PointInGeographicalPolygonTest expected output
 */

class PointInGeographicalPolygon : public PointInPolygon
{
    public:
        PointInGeographicalPolygon(const std::vector<LongitudeLatitude>& polygon);
};

#endif /* POINTINGEOGRAPHICALPOLYGON_HPP_ */
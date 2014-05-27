/*
 * TrackGenerator.hpp
 *
 * \date 11 avr. 2013, 12:41:36
 *  \author cec
 */

#ifndef TRACKGENERATOR_HPP_
#define TRACKGENERATOR_HPP_

#include "DataGenerator.hpp"
#include "Track.hpp"

template <> Track get_min_bound();
template <> Track get_max_bound();
template <> Track TypedScalarDataGenerator<Track>::get() const;

#endif /* TRACKGENERATOR_HPP_ */
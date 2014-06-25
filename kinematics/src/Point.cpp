#include "Point.hpp"

Point::Point() : v(0,0,0), frame("")
{
}

Point::Point(const std::string& frame_) : v(0,0,0), frame(frame_)
{

}

Point::Point(const std::string& frame_, const Eigen::Vector3d& v_) : v(v_), frame(frame_)
{
}

Point::Point(const Point& P) : v(P.v), frame(P.frame)
{
}

Point::Point(const std::string& frame_, const double x_, const double y_, const double z_) : v(x_,y_,z_), frame(frame_)
{
}

Point& Point::operator=(const Point& rhs)
{
    if (&rhs != this)
    {
        v = rhs.v;
        frame = rhs.frame;
    }
    return *this;
}

std::string Point::get_frame() const
{
    return frame;
}

Eigen::Vector3d Point::operator-(const Point& P) const
{
    return Eigen::Vector3d(x() - P.x(), y() - P.y(), z() - P.z());
}

Point Point::operator+(const Point& P) const
{
    return Point(frame, x() + P.x(), y() + P.y(), z() + P.z());
}

std::ostream& operator<<(std::ostream& os, const Point& P)
{
    os << "[" << P.v.transpose() << "] [in " << P.get_frame() << "]";
    return os;
}

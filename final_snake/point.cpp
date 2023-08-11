/*********************************
 * Author: Avigail Millatiner		
 * File: point.cpp
 * ******************************/
#include "point.hpp"

namespace ilrd
{
    Point::Point(int x, int y) : m_x(x), m_y(y)
    {}

    const Point Point::operator-() const
    {
        return Point(m_x*(-1), m_y*(-1));
    }

    const Point Point::operator+(const Point &other) const
    {
        return Point(m_x + other.m_x, m_y + other.m_y);
    }

    const Point Point::operator-(const Point &other) const
    {
        return *this + (-other);
    }

    Point &Point::operator+=(const Point &other)
    {
        return *this = *this + other;
    }

    Point &Point::operator-=(const Point &other)
    {
        *this += (-other);
        return *this;    
    }

    bool Point::operator==(const Point& other)
    {
        return m_x == other.m_x && m_y == other.m_y;
    }

    void Point::SetX(int x)
    {
        m_x = x;
    }

    void Point::SetY(int y)
    {
        m_y = y;
    }

} // namespace ilrd

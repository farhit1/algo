#pragma once


namespace geometry {
namespace two_dimensional {

/////////////////
// DECLARTIONS //
/////////////////

template<typename T>
struct Point {
    T x;
    T y;

    Point() = default;
    ~Point() = default;

    Point(const T& x, const T& y);

    template<typename U>
    Point<U> bind() const;

    bool operator==(const Point& other) const;
};

//////////////////////
// Point DEFINITION //
//////////////////////

template<typename T>
Point<T>::Point(const T& x, const T& y)
        : x(x)
        , y(y)
{}

template<typename T>
template<typename U>
Point<U> Point<T>::bind() const
{
    return Point<U>(x, y);
}

template<typename T>
bool Point<T>::operator==(const Point& other) const
{
    return x == other.x && y == other.y;
}

}}  // ::geometry::two_dimensional

#pragma once

#include <geometry/two_dimensional/point.h>
#include <geometry/two_dimensional/vector.h>

#include <cassert>


namespace geometry {
namespace two_dimensional {

//////////////////
// DECLARATIONS //
//////////////////

template<typename T>
struct Ray {
    Point<T> point;
    Vector<T> direction;

    Ray() = default;
    ~Ray() = default;

    template<typename U1, typename U2>
    Ray(const Point<U1>& point, const Vector<U2>& direction);

    template<typename U1, typename U2>
    Ray(const Point<U1>& start, const Point<U2>& direction);

    template<typename U>
    Ray<U> bind() const;

    template<typename U = T>
    U y(const T& x) const;
};

////////////////////
// Ray DEFINITION //
////////////////////

template<typename T>
template<typename U1, typename U2>
Ray<T>::Ray(const Point<U1>& point, const Vector<U2>& direction)
        : point(point.template bind<T>())
        , direction(direction.template bind<T>())
{}

template<typename T>
template<typename U1, typename U2>
Ray<T>::Ray(const Point<U1>& start, const Point<U2>& direction)
        : point(start.template bind<T>())
        , direction(Vector<T>(direction.x - start.x, direction.y - start.y))
{}

template<typename T>
template<typename U>
Ray<U> Ray<T>::bind() const {
    return Ray<U>(point, direction);
}

template<typename T>
template<typename U>
U Ray<T>::y(const T& x) const {
    assert(direction.x != 0);
    U yPerX = U(direction.y) / U(direction.x);
    return point.y + yPerX * fabs(x - point.x);
}

}}  // ::geometry::two_dimensional

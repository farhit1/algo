#pragma once


namespace geometry {
namespace two_dimensional {

//////////////////
// DECLARATIONS //
//////////////////

template<typename T>
struct Vector {
    T x;
    T y;

    Vector() = default;
    ~Vector() = default;

    Vector(const T& x, const T& y);

    template<typename U>
    Vector<U> bind() const;
};

///////////////////////
// Vector DEFINITION //
///////////////////////

template<typename T>
Vector<T>::Vector(const T& x, const T& y)
        : x(x)
        , y(y)
{}

template<typename T>
template<typename U>
Vector<U> Vector<T>::bind() const
{
    return Vector<U>(x, y);
}

}}  // ::geometry::two_dimensional

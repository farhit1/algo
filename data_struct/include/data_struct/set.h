#pragma once

#include <cstddef>


namespace data_struct {

template<typename T>
class Set {
public:
    typedef const T& const_reference;

    virtual ~Set() = default;

    virtual void insert(const_reference element) = 0;

    virtual size_t lower_bound(const_reference element) = 0;

    virtual void remove(size_t index) = 0;

    virtual const_reference at(size_t index) = 0;

    virtual size_t size() const = 0;
};

}  // ::data_struct

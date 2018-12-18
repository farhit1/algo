#pragma once

#include <utility>
#include <vector>


namespace problem {
namespace refrain {
namespace data_struct {

class Refrain {
public:
    virtual ~Refrain() = default;

    virtual std::pair<std::vector<int>, long long> getRefrain() = 0;
};

}}}  // ::problem::refrain::data_struct

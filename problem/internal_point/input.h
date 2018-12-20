#pragma once

#include <task/input.h>

#include <geometry/two_dimensional/point.h>

#include <vector>


namespace problem {
namespace internal_point {

class Input : public ::task::Input {
    using Point = ::geometry::two_dimensional::Point<int>;
    using RequiredVectorOfPoints = std::unique_ptr<Variable<std::vector<Point>>>;

public:
    Input() = default;

    RequiredVectorOfPoints polygon = requiredVariable<std::vector<Point>>();
    RequiredVectorOfPoints dots = requiredVariable<std::vector<Point>>();

protected:
    virtual void scan_(std::istream& cin) override;
};

}}  // ::problem::internal_point

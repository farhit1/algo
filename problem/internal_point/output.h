#pragma once

#include <task/output.h>

#include <vector>


namespace problem {
namespace internal_point {

class Output : public ::task::Output {
public:
    using ::task::Output::Output;

    enum class Result {
        INSIDE,
        BORDER,
        OUTSIDE
    };

    std::unique_ptr<Variable<std::vector<Result>>> answer = requiredVariable<std::vector<Result>>();

protected:
    virtual void print_(std::ostream& cout) const override;
};

}}  // ::problem::internal_point

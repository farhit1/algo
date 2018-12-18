#pragma once

#include <task/output.h>

#include <vector>


namespace problem {
namespace refrain {

class Output : public ::task::Output {
public:
    using ::task::Output::Output;

    std::unique_ptr<Variable<long long>> ans = requiredVariable<long long>();
    std::unique_ptr<Variable<std::vector<int>>> refrain = requiredVariable<std::vector<int>>();

protected:
    virtual void print_(std::ostream& cout) const override;
};

}}  // ::problem::refrain

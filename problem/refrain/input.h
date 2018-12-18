#pragma once

#include <task/input.h>

#include <memory>
#include <vector>


namespace problem {
namespace refrain {

class Input : public ::task::Input {
public:
    Input() = default;

    std::unique_ptr<Variable<int>> m = requiredVariable<int>();
    std::unique_ptr<Variable<std::vector<int>>> numbers = requiredVariable<std::vector<int>>();

protected:
    virtual void scan_(std::istream& cin) override;
};

}}  // ::problem::refrain

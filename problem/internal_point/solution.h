#pragma once

#include <task/solution.h>

#include "input.h"
#include "output.h"

#include <memory>


namespace problem {
namespace internal_point {

class Solution : public ::task::Solution {
public:
    explicit Solution(const std::shared_ptr<::task::Input>& input)
            : ::task::Solution(input)
            , input_(static_cast<const Input*>(solutionInput_.get()))
            , output_(std::make_shared<Output>(input))
    {}

    virtual void run() override;

    virtual const Output* output() const override;

private:
    const Input* input_;
    std::shared_ptr<Output> output_;
};

}}  // ::problem::internal_point

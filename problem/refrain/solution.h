#pragma once

#include <task/solution.h>

#include "input.h"
#include "output.h"

#include <memory>


namespace problem {
namespace refrain {

class Solution : public ::task::Solution {
public:
    explicit Solution(const std::shared_ptr<::task::Input>& input);

    virtual void run() override;

    virtual const Output* output() const override;

private:
    const Input* input_;
    std::shared_ptr<Output> output_;
};

}}  // ::problem::refrain

#pragma once

#include <task/input.h>
#include <task/output.h>

#include <memory>


namespace task {

class Solution {
public:
    virtual ~Solution() = default;

    explicit Solution(const std::shared_ptr<Input>& input);

    virtual void run() = 0;

    virtual const Output* output() const = 0;

protected:
    const std::shared_ptr<Input> solutionInput_;
};

}  // ::task

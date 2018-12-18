#include "input.h"
#include "solution.h"


std::shared_ptr<::task::Input> getInput()
{
    return std::make_shared<::problem::refrain::Input>();
}

std::unique_ptr<::task::Solution> getSolution(
        const std::shared_ptr<::task::Input>& input)
{
    return std::make_unique<::problem::refrain::Solution>(input);
}

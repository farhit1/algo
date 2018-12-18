#include "solution.h"
#include "data_struct/get.h"


namespace problem {
namespace refrain {

Solution::Solution(const std::shared_ptr<::task::Input>& input)
        : ::task::Solution(input)
        , input_(static_cast<const Input*>(solutionInput_.get()))
        , output_(std::make_shared<Output>(input))
{}

void Solution::run()
{
    auto graph = data_struct::get(input_->numbers->get(),
                                  input_->m->get());

    auto [refrain, ans] = graph->getRefrain();

    output_->ans->set(ans);
    output_->refrain->set(refrain);
}

const Output* Solution::output() const
{
    return output_.get();
}

}}  // ::problem::solution

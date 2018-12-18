#include <task/output.h>


namespace task {

Output::Output(const std::shared_ptr<Input>& onInput)
        : onInput_(onInput)
{}

Input* Output::input() const
{
    return onInput_.get();
}

void Output::print(std::ostream& cout) const
{
    isAllSet();

    print_(cout);
}

}  // ::task

#include "solve.h"

#include <task/input.h>
#include <task/solution.h>


extern std::shared_ptr<::task::Input> getInput();

extern std::unique_ptr<::task::Solution> getSolution(
        const std::shared_ptr<::task::Input>& input);


void solve(std::istream& cin, std::ostream& cout)
{
    auto input = getInput();
    input->scan(cin);
    auto solution = getSolution(input);
    solution->run();
    solution->output()->print(cout);
}

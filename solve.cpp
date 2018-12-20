#include "solve.h"

#include <task/input.h>
#include <task/solution.h>


extern std::shared_ptr<::task::Input> getInput();

extern std::unique_ptr<::task::Solution> getSolution(
        const std::shared_ptr<::task::Input>& input);

namespace {

void run(std::istream& cin, std::ostream& cout) {
    auto input = getInput();
    input->scan(cin);
    auto solution = getSolution(input);
    solution->run();
    solution->output()->print(cout);
}

}  // anonymous namespace

void solve(std::istream& cin, std::ostream& cout)
{
#ifndef MULTITESTS
    run(cin, cout);
#else
    size_t testsN;
    cin >> testsN;
    while (testsN--) {
        run(cin, cout);
    }
#endif
}

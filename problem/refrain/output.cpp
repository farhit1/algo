#include "output.h"


namespace problem {
namespace refrain {

void Output::print_(std::ostream& cout) const
{
    cout << ans->get() << std::endl;
    cout << refrain->get().size() << std::endl;
    for (size_t i : refrain->get())
        cout << i + 1 << " ";
    cout << std::endl;
}

}}  // ::problem::refrain

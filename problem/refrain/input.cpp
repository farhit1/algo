#include "input.h"

#include <vector>

namespace problem {
namespace refrain {

void Input::scan_(std::istream& cin)
{
    int n;
    cin >> n;
    m->scan(cin);
    std::vector<int> x(n);
    for (int& i : x) {
        cin >> i;
        i--;
    }
    numbers->set(std::move(x));
}

}}  // ::problem:refrain

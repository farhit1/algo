#include <task/input.h>

#include <cassert>


namespace task {

void Input::scan(std::istream& cin)
{
    assert(!scanned_);
    scanned_ = true;

    scan_(cin);
    isAllSet();
}

}  // ::task

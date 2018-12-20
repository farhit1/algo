#include "output.h"


namespace problem {
namespace internal_point {

void Output::print_(std::ostream& cout) const {
    for (Result result : answer->get()) {
        switch (result) {
            case Result::INSIDE:
                cout << "INSIDE\n";
                break;
            case Result::BORDER:
                cout << "BORDER\n";
                break;
            case Result::OUTSIDE:
                cout << "OUTSIDE\n";
                break;
        }
    }
    cout << "\n";
}

}}  // ::problem::internal_point

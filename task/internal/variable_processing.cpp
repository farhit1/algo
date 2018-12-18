#include <task/internal/variable_processing.h>


namespace task {
namespace internal {

void VariableProcessing::isAllSet() const
{
    for (const UntypedVariable *var : requiredVariables_) {
        assert(var->isSet());
    }
}

}}  // ::task::internal

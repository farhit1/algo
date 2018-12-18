#include "get.h"
#include "refrain_suffix_automaton.h"


namespace problem {
namespace refrain {
namespace data_struct {

std::unique_ptr<Refrain> get(const std::vector<int>& s, size_t alphabet)
{
    return std::make_unique<RefrainSuffixAutomaton>(s, alphabet);
}

}}}  // ::problem::refrain::data_struct

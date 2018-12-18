#include "get.h"
#include "refrain_suffix_tree.h"


namespace problem {
namespace refrain {
namespace data_struct {

std::unique_ptr<Refrain> get(const std::vector<int>& s, size_t alphabet)
{
    return std::make_unique<RefrainSuffixTree>(s, alphabet);
}

}}}  // ::problem::refrain::data_struct

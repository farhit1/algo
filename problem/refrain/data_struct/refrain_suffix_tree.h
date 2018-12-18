#pragma once

#include "refrain.h"

#include <data_struct/suffix_tree.h>


namespace problem {
namespace refrain {
namespace data_struct {

class RefrainSuffixTree : public ::data_struct::SuffixTree
                        , public Refrain
{
public:
    using ::data_struct::SuffixTree::SuffixTree;

    virtual std::pair<std::vector<int>, long long> getRefrain() override;

private:
    std::pair<long long, Node*> dfs(Node* node, size_t len);
};

}}}  // ::problem::refrain::data_struct

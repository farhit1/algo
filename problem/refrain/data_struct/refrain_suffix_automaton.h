#pragma once

#include "refrain.h"

#include <data_struct/suffix_automaton.h>


namespace problem {
namespace refrain {
namespace data_struct {

class RefrainSuffixAutomaton : public ::data_struct::SuffixAutomaton
                             , public Refrain
{
public:
    using ::data_struct::SuffixAutomaton::SuffixAutomaton;

    virtual std::pair<std::vector<int>, long long> getRefrain() override;

private:
    std::pair<long long, Node*> findMax(Node* node);

    std::vector<int> restore(Node* node);
};

}}}  // ::problem::refrain::data_struct

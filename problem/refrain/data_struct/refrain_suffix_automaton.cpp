#include "get.h"
#include "refrain_suffix_automaton.h"

#include <algorithm>
#include <vector>


namespace problem {
namespace refrain {
namespace data_struct {

std::pair<std::vector<int>, long long>
RefrainSuffixAutomaton::getRefrain()
{
    build();

    auto [ans, bestNode] = findMax(root_.get());
    return {restore(bestNode), ans};
}

std::pair<long long, RefrainSuffixAutomaton::Node*>
RefrainSuffixAutomaton::findMax(Node* node)
{
    node->value = node->term ? 1 : 0;
    std::pair<long long, Node*> best = {0, nullptr};

    for (auto& to : node->next) {
        if (to) {
            if (to->value == -1) {
                auto result = findMax(to.get());
                if (best < result)
                    best = result;
            }
            if (node->len + 1 == to->len)
                to->prev = node;
            node->value += to->value;
        }
    }

    return std::max(best, {node->value * node->len, node});
}

std::vector<int> RefrainSuffixAutomaton::restore(
        RefrainSuffixAutomaton::Node* node)
{
    std::vector<int> refrain;

    while (node->prev) {
        for (int i = 0; i < alphabet_; i++)
            if (node->prev->next[i].get() == node) {
                refrain.push_back(i);
                break;
            }
        node = node->prev;
    }

    std::reverse(refrain.begin(), refrain.end());
    return refrain;
}

}}}  // ::problem::refrain::data_struct

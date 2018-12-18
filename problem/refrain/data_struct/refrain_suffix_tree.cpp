#include "get.h"
#include "refrain_suffix_tree.h"


namespace problem {
namespace refrain {
namespace data_struct {

std::pair<std::vector<int>, long long> RefrainSuffixTree::getRefrain()
{
    build();

    auto [ans, node] = dfs(root_.get(), 0);

    std::vector<int> refrain;
    while (node != root_.get()) {
        for (int i = node->right - 1; i >= node->left; i--)
            refrain.push_back(s_[i]);
        node = node->parent;
    }
    reverse(refrain.begin(), refrain.end());

    return {refrain, ans};
}

std::pair<long long, RefrainSuffixTree::Node*>
RefrainSuffixTree::dfs(Node* node, size_t len)
{
    node->subtreeTerms = node->term ? 1 : 0;
    std::pair<long long, Node*> ans = {0, nullptr};

    for (const auto& to : node->next) {
        if (to) {
            auto subtreeResult = dfs(to.get(), len + to->length());
            if (subtreeResult > ans)
                ans = subtreeResult;
            node->subtreeTerms += to->subtreeTerms;
        }
    }

    return std::max(ans, {(long long) node->subtreeTerms * len, node});
}

}}}  // ::problem::refrain::data_struct

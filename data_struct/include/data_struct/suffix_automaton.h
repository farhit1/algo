#pragma once

#include <data_struct/suffix_graph.h>

#include <memory>


namespace data_struct {

class SuffixAutomaton : public SuffixGraph {
public:
    SuffixAutomaton(const std::vector<int>& s,
                    size_t alphabet);

protected:
    struct Node {
        Node(size_t len, Node* suf, int alphabet);

        size_t len;
        Node* suf;
        std::vector<std::shared_ptr<Node>> next;

        bool term = false;

        long long value = -1;
        Node* prev = nullptr;
    };

    virtual void add(int i) override;

    virtual void markTerminals() override;

    std::shared_ptr<Node> root_;
    Node* last_;
};

}  // ::data_struct

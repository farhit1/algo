#pragma once

#include <data_struct/suffix_graph.h>

#include <memory>
#include <utility>


namespace data_struct {

class SuffixTree : public SuffixGraph {
public:
    SuffixTree(const std::vector<int>& s, size_t alphabet);

protected:
    struct Node {
        Node(size_t left, size_t right, Node* parent, size_t alphabet);

        int left;
        int right;

        Node* parent;
        std::vector<std::unique_ptr<Node>> next;

        Node* link = nullptr;
        bool term = false;
        size_t subtreeTerms = 0;

        int length() const;
    };

    virtual void add(int i) override;

    virtual void markTerminals() override;

    struct Position {
        Position()
                : node(nullptr)
                , len(-1)
        {}

        Position(Node* node, int len)
                : node(node)
                , len(len)
        {}

        Node* node;
        int len;
    };

    std::pair<std::unique_ptr<Node>, Node*> addEdgeToParent(int l, int r, Node* parent);

    Node* splitEdge(const Position& pos);

    Position readSymbol(const Position& pos, int c);

    Position descent(Node* v, int l, int r);

    Node* link(Node* v);

    Node* findBottom(Node* node, size_t len);

    std::unique_ptr<Node> root_;
    Position position_;
};

}  // ::data_struct

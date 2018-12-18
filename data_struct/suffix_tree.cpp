#include <data_struct/suffix_tree.h>


namespace data_struct {

SuffixTree::Node::Node(size_t left, size_t right,
                       Node* parent, size_t alphabet)
        : left(left)
        , right(right)
        , parent(parent)
        , next(std::vector<std::unique_ptr<Node>>(alphabet))
{}

int SuffixTree::Node::length() const
{
    return right - left;
}

SuffixTree::SuffixTree(const std::vector<int>& s, size_t alphabet)
        : SuffixGraph(s, alphabet)
        , root_(std::make_unique<Node>(-1, -1, nullptr, alphabet_))
        , position_(root_.get(), 0)
{
    root_->link = root_.get();
}

void SuffixTree::add(int i)
{
    while (true) {
        Position newPosition = readSymbol(position_, s_[i]);
        if (newPosition.node) {
            position_ = newPosition;
            return;
        }

        Node* divider = splitEdge(position_);
        addEdgeToParent(i, int(s_.size()), divider);
        position_ = Position(link(divider), 0);
        if (divider == root_.get()) {
            return;
        }
    }
}

void SuffixTree::markTerminals()
{
    Node* final = findBottom(root_.get(), 0);
    while (final != root_.get()) {
        final->term = true;
        final = link(final);
    }
}

std::pair<std::unique_ptr<SuffixTree::Node>, SuffixTree::Node*>
SuffixTree::addEdgeToParent(int l, int r, Node* parent)
{
    auto before = std::move(parent->next[s_[l]]);
    parent->next[s_[l]] = std::make_unique<Node>(l, r, parent, alphabet_);
    return {std::move(before), parent->next[s_[l]].get()};
}

SuffixTree::Node* SuffixTree::splitEdge(const Position& pos)
{
    if (!pos.len)
        return pos.node;

    int down = pos.node->length() - pos.len;
    if (!down)
        return pos.node->parent;

    auto [before, divider] = addEdgeToParent(pos.node->left,
                                             pos.node->left + down,
                                             pos.node->parent);
    pos.node->left += down;
    pos.node->parent = divider;
    divider->next[s_[pos.node->left]] = std::move(before);

    return divider;
}

SuffixTree::Position SuffixTree::readSymbol(const Position& pos, int c)
{
    if (pos.len) {
        if (s_[pos.node->right - pos.len] == c)
            return Position(pos.node, pos.len - 1);
        return Position();
    }

    Node* nextNode = pos.node->next[c].get();
    if (nextNode == nullptr)
        return Position();
    return Position(nextNode, nextNode->length() - 1);
}

SuffixTree::Position SuffixTree::descent(Node* v, int l, int r)
{
    if (l == r)
        return Position(v, 0);
    while (true) {
        v = v->next[s_[l]].get();
        if (v->length() > r - l - 1)
            return Position(v, v->length() - r + l);
        l += v->length();
    }
}

SuffixTree::Node* SuffixTree::link(Node* v)
{
    if (!v->link) {
        v->link = splitEdge(descent(link(v->parent),
                                    v->left + (v->parent != root_.get() ? 0 : 1),
                                    v->right));
    }
    return v->link;
}

SuffixTree::Node* SuffixTree::findBottom(Node* node, size_t len)
{
    if (len == s_.size())
        return node;
    for (const auto& to : node->next) {
        if (to) {
            Node* result = findBottom(to.get(),
                                      len + to->length());
            if (result)
                return result;
        }
    }
    return nullptr;
}

}  // ::data_struct

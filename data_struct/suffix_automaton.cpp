#include <data_struct/suffix_automaton.h>


namespace data_struct {

SuffixAutomaton::Node::Node(size_t len, Node* suf, int alphabet)
        : len(len)
        , suf(suf)
        , next(std::vector<std::shared_ptr<Node>>(alphabet))
{}

SuffixAutomaton::SuffixAutomaton(const std::vector<int>& s,
                                 size_t alphabet)
        : SuffixGraph(s, alphabet)
        , root_(std::make_shared<Node>(0, nullptr, alphabet_))
        , last_(root_.get())
{}

void SuffixAutomaton::add(int i)
{
    auto newNode = std::make_shared<Node>(last_->len + 1,
                                          root_.get(),
                                          alphabet_);
    Node* ptr = last_;
    Node* nextNode;
    last_ = newNode.get();

    while (ptr != nullptr &&
           (nextNode = ptr->next[i].get()) == nullptr)
    {
        ptr->next[i] = newNode;
        ptr = ptr->suf;
    }

    if (!ptr) {
        newNode->suf = root_.get();
    }
    else if (nextNode->len == ptr->len + 1) {
        newNode->suf = nextNode;
    }
    else {
        auto duplicateNode = std::make_shared<Node>(ptr->len + 1,
                                                    nextNode->suf,
                                                    alphabet_);
        nextNode->suf = newNode->suf = duplicateNode.get();
        while (ptr != nullptr && ptr->next[i].get() == nextNode) {
            ptr->next[i] = duplicateNode;
            ptr = ptr->suf;
        }
        duplicateNode->next = nextNode->next;
    }
}

void SuffixAutomaton::markTerminals()
{
    do {
        last_->term = true;
        last_ = last_->suf;
    } while (last_ != nullptr);
}

}  // ::data_struct

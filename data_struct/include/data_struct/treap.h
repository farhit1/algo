#pragma once

#include <data_struct/set.h>

#include <random>
#include <memory>


namespace data_struct {

//////////////////
// DECLARATIONS //
//////////////////

template<typename T>
class Treap : public Set<T> {
public:
    using typename Set<T>::const_reference;

    Treap() = default;

    virtual void insert(const_reference element) override;

    virtual size_t lower_bound(const_reference element) override;

    virtual void remove(size_t index) override;

    virtual const_reference at(size_t index) override;

    virtual size_t size() const override;

private:
    struct Node {
        const T element;
        const int priority;
        size_t size;
        std::unique_ptr<Node> l;
        std::unique_ptr<Node> r;

        static std::mt19937 mt_rand;

        explicit Node(const_reference element);

        const Node& recalc();
    };

    std::pair<std::unique_ptr<Node>, std::unique_ptr<Node>>
    split(std::unique_ptr<Node> t,
          const std::function<bool(const Node*)>& condition);

    std::unique_ptr<Node>
    merge(std::unique_ptr<Node> l, std::unique_ptr<Node> r);

    std::function<bool(const Node*)>
    getDefaultCondition(const_reference element);

    std::function<bool(const Node*)>
    getConditionByIndex(size_t& index);

    std::unique_ptr<Node> root_;
};

template<typename T>
std::unique_ptr<Set<T>> getTreap();

//////////////////////
// Treap DEFINITION //
//////////////////////

template<typename T>
void Treap<T>::insert(const_reference element)
{
    auto parts = split(std::move(root_), getDefaultCondition(element));
    root_ = std::move(merge(merge(std::move(parts.first), std::make_unique<Node>(element)),
                            std::move(parts.second)));
}

template<typename T>
size_t Treap<T>::lower_bound(const_reference element)
{
    auto parts = split(std::move(root_), getDefaultCondition(element));
    size_t result = (parts.first ? parts.first->size : 0);
    root_ = std::move(merge(std::move(parts.first), std::move(parts.second)));
    return result;
}

template<typename T>
void Treap<T>::remove(size_t index)
{
    auto parts = split(std::move(root_), getConditionByIndex(index));
    size_t oneIndex = 1;
    auto rightParts = split(std::move(parts.second), getConditionByIndex(oneIndex));
    root_ = std::move(merge(std::move(parts.first), std::move(std::move(rightParts.second))));
}

template<typename T>
typename Treap<T>::const_reference Treap<T>::at(size_t index)
{
    auto parts = split(std::move(root_), getConditionByIndex(index));
    size_t oneIndex = 1;
    auto rightParts = split(std::move(parts.second), getConditionByIndex(oneIndex));
    const_reference element = rightParts.first->element;
    root_ = std::move(merge(std::move(parts.first),
                            std::move(merge(std::move(rightParts.first), std::move(rightParts.second)))));
    return element;
}

template<typename T>
size_t Treap<T>::size() const
{
    return root_ ? root_->size : 0;
}

template<typename T>
std::pair<std::unique_ptr<typename Treap<T>::Node>, std::unique_ptr<typename Treap<T>::Node>>
Treap<T>::split(std::unique_ptr<Node> t,
                const std::function<bool(const Node*)>& condition)
{
    if (!t)
        return {nullptr, nullptr};
    t->recalc();

    if (condition(t.get())) {
        auto tmp = split(std::move(t->l), condition);
        t->l = std::move(tmp.second);
        t->recalc();
        return {std::move(tmp.first), std::move(t)};
    }
    else {
        auto tmp = split(std::move(t->r), condition);
        t->r = std::move(tmp.first);
        t->recalc();
        return {std::move(t), std::move(tmp.second)};
    }
}

template<typename T>
std::unique_ptr<typename Treap<T>::Node>
Treap<T>::merge(std::unique_ptr<Node> l, std::unique_ptr<Node> r)
{
    if (!l)
        return r;
    if (!r)
        return l;
    l->recalc();
    r->recalc();

    if (l->priority < r->priority) {
        l->r = merge(std::move(l->r), std::move(r));
        l->recalc();
        return l;
    } else {
        r->l = merge(std::move(l), std::move(r->l));
        r->recalc();
        return r;
    }
}

template<typename T>
std::function<bool(const typename Treap<T>::Node*)>
Treap<T>::getDefaultCondition(const_reference element)
{
    return [&element](const Node* node) {
        return element < node->element || element == node->element;
    };
}

template<typename T>
std::function<bool(const typename Treap<T>::Node*)>
Treap<T>::getConditionByIndex(size_t& index)
{
    return [&index](const Node* node) {
        size_t leftSize = node->l ? node->l->size : 0;
        bool result;
        if (index <= leftSize)
            result = true;
        else {
            result = false;
            index -= leftSize + 1;
        }
        return result;
    };
}

////////////////////////////
// Treap::Node DEFINITION //
////////////////////////////

template<typename T>
std::mt19937 Treap<T>::Node::mt_rand(0);

template<typename T>
Treap<T>::Node::Node(const_reference element)
        : element(element)
        , priority(mt_rand())
{}

template<typename T>
const typename Treap<T>::Node& Treap<T>::Node::recalc()
{
    size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
    return *this;
}

/////////////////////////
// getTreap DEFINITION //
/////////////////////////

template<typename T>
std::unique_ptr<Set<T>> getTreap() {
    return std::make_unique<Treap<T>>();
}

}  // ::data_struct

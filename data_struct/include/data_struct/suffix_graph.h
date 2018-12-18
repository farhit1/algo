#pragma once

#include <vector>


namespace data_struct {

class SuffixGraph {
public:
    virtual ~SuffixGraph() = default;

    SuffixGraph(const std::vector<int>& s,
                size_t alphabet);

    void build();

protected:
    virtual void add(int c) = 0;

    virtual void markTerminals() = 0;

    const std::vector<int> s_;
    const size_t alphabet_;
};

}  // ::data_struct

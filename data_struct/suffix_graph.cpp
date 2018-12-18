#include <data_struct/suffix_graph.h>


namespace data_struct {

SuffixGraph::SuffixGraph(const std::vector<int>& s,
                         size_t alphabet)
        : s_(s)
        , alphabet_(alphabet)
{}

void SuffixGraph::build()
{
    for (int c : s_) {
        add(c);
    }
    markTerminals();
}

}  // ::data_struct

#ifndef PPM_PPM_NODE_H_
#define PPM_PPM_NODE_H_

#include <vector>

#include "node_info.h"

class PPMNode {
public:
    PPMNode (std::size_t tree_level, std::size_t symbol);

    Probability findSymbol (const std::size_t &context, const int &context_level);

    bool hasSymbol (std::size_t symbol);
    Probability buildProbability (const std::size_t &child_index, const bool &isEscape);

private:
    NodeInfo data_;
    std::vector <PPMNode *> children_;

};

#endif // PPM_PPM_NODE_H_

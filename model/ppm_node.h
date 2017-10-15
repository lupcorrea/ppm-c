#ifndef PPM_PPM_NODE_H_
#define PPM_PPM_NODE_H_

#include <vector>

#include "../definitions.h"

class PPMNode {
public:
    PPMNode (const std::size_t &context_level, const bool isEscape, const std::size_t &symbol);

private:
    std::size_t context_level_;
    std::size_t symbol_;
    std::size_t occurrence_counter_;

    std::vector <PPMNode*> children_;
};

struct Compare {
    bool operator() (PPMNode *lhs, PPMNode *rhs) {
        return lhs->aabb.centroid_.x < rhs->aabb.centroid_.x;
    }
};



#endif // PPM_PPM_NODE_H_

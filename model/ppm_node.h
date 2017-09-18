#ifndef PPM_PPM_NODE_H_
#define PPM_PPM_NODE_H_

#include <vector>

#include "node_info.h"

class PPMNode {
public:
    PPMNode (std::size_t tree_level, std::size_t symbol);
    void buildNode ();

private:
    NodeInfo data_;
    std::vector <PPMNode *> children_;

};

#endif // PPM_PPM_NODE_H_

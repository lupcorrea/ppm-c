#ifndef PPM_PPM_TREE_H_
#define PPM_PPM_TREE_H_

#include "ppm_node.h"

/// \class PPMTree
/// \brief The root of the tree used to implement the PPM table structure.
/// The data inserted into this node is different from the rest of the tree, since it represents
/// context level K = -1. This node is also used to store escape counters for all context levels.

class PPMTree {
public:
    PPMTree (void);

private:

};

#endif //PPM_PPM_TREE_H_

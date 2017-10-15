#ifndef PPM_PPM_TREE_H_
#define PPM_PPM_TREE_H_

#include "ppm_node.h"

class PPMTree {
public:
    PPMTree (void);

private:
    PPMNode* root_;
    std::vector<std::size_t> context_;
};



#endif // PPM_PPM_TREE_H_

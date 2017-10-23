#ifndef PPM_PPM_TREE_H_
#define PPM_PPM_TREE_H_

#include "ppm_node.h"
#include "../Encoder.h"

class PPMTree {
public:
    PPMTree (void);

    void encodeSymbol (Encoder &encoder, const std::size_t &symbol);
    Probability encodeNegative (const std::size_t &symbol);

    void updateContext (const std::size_t &symbol);

private:
    PPMNode* root_;
    std::vector <std::size_t> context_;
};



#endif // PPM_PPM_TREE_H_

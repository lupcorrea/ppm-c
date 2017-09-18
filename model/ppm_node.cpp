#include "ppm_node.h"

PPMNode::PPMNode (std::size_t tree_level, std::size_t symbol) {
    data_.context_level = tree_level;
    data_.symbol = symbol;
}

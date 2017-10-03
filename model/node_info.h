#ifndef PPM_NODE_INFO_H_
#define PPM_NODE_INFO_H_

// TODO: define symbol type according to file module, or just template all over it.
// TODO: build a struct that stores low and high fields.
struct NodeInfo {
    std::size_t context_level;
    std::size_t symbol;
    std::size_t occurrence_counter = 1;
};

struct Probability {
    bool isEscape = true;
    std::size_t low;
    std::size_t high;
}

#endif // PPM_TABLE_CELL_H_

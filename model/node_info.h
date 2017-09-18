#ifndef PPM_NODE_INFO_H_
#define PPM_NODE_INFO_H_

/* TODO: define symbol type according to file module, or just template all over it. */
/* TODO: come up with a better name for this structure */
struct NodeInfo {
    std::size_t context_level;
    std::size_t symbol;
    std::size_t occurrence_counter;
};

#endif // PPM_TABLE_CELL_H_

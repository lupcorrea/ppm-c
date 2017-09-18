#ifndef PPM_TABLE_NODE_H_
#define PPM_TABLE_NODE_H_

#include <algorithm>
#include <queue>
#include <vector>

/* TODO: define symbol type according to file module, or just template all over it. */
/* TODO: come up with a better name for this structure */
/* TODO: come up with a lighter container than vector for the children list */
struct TableNode {
    int context_level;
    std::size_t symbol;
    std::size_t occurrence_counter;
    std::priority_queue <TableNode*, std::vector <TableNode*>, SortByOccurrenceCounter> children;
};

struct SortByOccurrenceCounter {
    bool operator() (TableNode *left, TableNode *right) {
        return left->occurrence_counter < right->occurrence_counter;
    }
};

#endif // PPM_TABLE_CELL_H_

#ifndef PPM_PPM_NODE_H_
#define PPM_PPM_NODE_H_

#include <vector>

#include "../definitions.h"
#include "node_info.h"

class PPMNode {
public:
    PPMNode (const std::size_t &context_level, const bool isEscape, const std::size_t &symbol);

    Probability searchForMatch (const std::vector <std::size_t> &context, const std::size_t &current_order);

    bool isContext (void);
    void createNewChild (const std::size_t &symbol);
    void increaseOccurrenceCounter (void);
    bool hasSymbol (const std::size_t &symbol);
    std::size_t getOccurrenceCounter (void);
    Probability hasChild (const std::size_t &symbol);

    Probability encodeFirstSymbol (const std::size_t &symbol);

private:
    std::size_t symbol_;
    std::size_t occurrence_counter_;
    std::size_t context_level_;

    std::vector <PPMNode*> children_;
};

struct Compare {
    bool operator() (PPMNode *lhs, PPMNode *rhs) {
        return lhs->getOccurrenceCounter() < rhs->getOccurrenceCounter();
    }
};



#endif // PPM_PPM_NODE_H_

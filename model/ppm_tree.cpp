#include "ppm_tree.h"

void PPMTree::PPMTree (void) {
    root_ = new PPMNode (0, false, NULL);
}

void encodeSymbol (std::size_t symbol) {
    Probability prob;

    // Update context
    updateContext (symbol);

    // Process for K > 0
    for (int current_order = context_.size()-1; current_order > 0; current_order--) {
        prob = root->searchForMatch (context_, current_order);

        // If semileaf isn't a context yet, just drop it to a lesser K.
        if (prob == NULL) continue;

        // TODO: Code whatever came out of the search.
    }

    // Process for K = 0
    if (prob.isEscape || prob == NULL) prob = root->hasChild (symbol);
    // TODO: Code whatever came out of the search.

    // If everything so far failed, code it with equiprobability
    if (prob.isEscape) //TODO;
}

void updateContext (const std::size_t &symbol) {
    context_.insert (context_.begin(), symbol);

    if (context_.size() > kMaxOrder) context_.pop_back();
}

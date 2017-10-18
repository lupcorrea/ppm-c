#include "ppm_tree.h"

void PPMTree::PPMTree (void) {
    root_ = new PPMNode (0, false, NULL);

    symbols_left_ = kAlphabetSize;
}

Probability PPMTree::encodeSymbol (std::size_t symbol) {
    Probability prob;

    // Update context
    updateContext (symbol);

    // Process for K > 0
    for (int current_order = context_.size()-1; current_order > 0; current_order--) {
        prob = root->searchForMatch (context_, current_order);

        // If semileaf isn't a context yet, just drop it to a lesser K.
        if (prob.total == -1) continue;

        return prob;
    }

    // Process for K = 0
    if (prob.isEscape || prob.total == -1) prob = root->hasChild (symbol); 
    return prob;

    // If everything so far failed, code it with equiprobability
    if (prob.isEscape) {
        // Encode
        prob.low = symbol;
        prob.high = symbol+1;
        prob.total = kAlphabetSize

        // Update
        root_->createNewChild (symbol);
    }

    return prob;
}

void PPMTree::updateContext (const std::size_t &symbol) {
    context_.insert (context_.begin(), symbol);

    if (context_.size() > kMaxOrder) context_.pop_back();
}

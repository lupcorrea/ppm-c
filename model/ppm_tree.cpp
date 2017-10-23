#include "ppm_tree.h"

PPMTree::PPMTree (void) {
    root_ = new PPMNode (0, false, kAlphabetSize + 5);
}

Probability PPMTree::encodeSymbol (std::size_t symbol) {
    Probability prob;

    // Update context
    updateContext (symbol);
/**/
    std::cout << "[Context] ";
    for (int i = 0; i < context_.size(); i++) std::cout << context_ [i] << " ";
    std::cout << '\n';
/**/

    // If this is the first symbol, encode it and abort immediately.
    if (context_.size() == 1) {
        prob = root_->encodeFirstSymbol (symbol);

/**/
        std::cout << "[First Symbol]" << '\n';
        std::cout << "[Probability] Low: " << prob.low << '\n';
        std::cout << "[Probability] High: " << prob.high << '\n';
        std::cout << "[Probability] Total: " << prob.total << '\n';
/**/

        return prob;
    }

    // Process for K > 0
    for (int current_order = context_.size()-1; current_order > 0; current_order--) {
        prob = root_->searchForMatch (context_, current_order);

        // If semileaf isn't a context yet, just drop it to a lesser K.
        if (!prob.hasContext) continue;
/**/
        std::cout << "[Order] " << current_order << '\n';
        std::cout << "[Probability] Low: " << prob.low << '\n';
        std::cout << "[Probability] High: " << prob.high << '\n';
        std::cout << "[Probability] Total: " << prob.total << '\n';
        std::cout << "[Probability] Escape: " << prob.isEscape << '\n';
/**/
        return prob;
    }

    // Process for K = 0
    if (prob.isEscape) {
        prob = root_->hasChild (symbol);

/**/
        std::cout << "[Order] 0" << '\n';
        std::cout << "[Probability] Low: " << prob.low << '\n';
        std::cout << "[Probability] High: " << prob.high << '\n';
        std::cout << "[Probability] Total: " << prob.total << '\n';
        std::cout << "[Probability] Escape: " << prob.isEscape << '\n';
/**/

        return prob;
    }


    // If everything so far failed, code it with equiprobability
    if (prob.isEscape) {
        // Encode
        prob.low = symbol;
        prob.high = symbol+1;
        prob.total = kAlphabetSize;

/**/
        std::cout << "[Order] -1" << '\n';
        std::cout << "[Probability] Low: " << prob.low << '\n';
        std::cout << "[Probability] High: " << prob.high << '\n';
        std::cout << "[Probability] Total: " << prob.total << '\n';
        std::cout << "[Probability] Escape: " << prob.isEscape << '\n';
/**/

        // Update
        root_->createNewChild (symbol);
    }

    return prob;
}

void PPMTree::updateContext (const std::size_t &symbol) {
    context_.insert (context_.begin(), symbol);

    if (context_.size() > kMaxOrder) context_.pop_back();
}

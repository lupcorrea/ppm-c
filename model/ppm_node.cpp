#include "ppm_node.h"

#include <algorithm>
#include <queue>

#include "node_info.h"

PPMNode::PPMNode (const std::size_t &context_level, const bool isEscape, const std::size_t &symbol) {
    // Setup basic information
    context_level_ = context_level;
    symbol_ = symbol;
    if (!isEscape) occurrence_counter_ = 1;

    // Create escape child if it is possible for this node to have children
    if (context_level_ < kMaxOrder && !isEscape) children_.push_back (new PPMNode (context_level_ + 1, true, kEscape));
}

Probability PPMNode::searchForMatch (const std::vector <std::size_t> &context, const std::size_t &current_order) {
    Probability prob;

    // If current semileaf is not a context yet, do not even try.
    if (current_order == 1 && !isContext) {
        prob.total = -1;
    };

    // Non-recursive part: if reached  a semileaf, try to find the child we are after.
    if (current_order == 1) {
        prob = hasChild (context [0]);
        if (prob.isEscape) createNewChild (context [0]);
        else children_ [prob.symbol_index]->increaseOccurrenceCounter()++;
        return prob;
    }

    // Recursive part: keep trying to find a match for all of the context elements
    for (int child_index = 1; child_index < children_.size(); child_index++) {
        if (children_ [child_index]->hasSymbol (context [current_order])) {
            prob = searchForMatch (context, current_order-1);
            break;
        }
    }

    return prob;
}

bool PPMNode::isContext (void) {
    return children_.size() > 1;
}

void PPMNode::createNewChild (const std::size_t &symbol) {
    // Update escape counter
    children_ [0].increaseOccurrenceCounter();

    // Create child
    children_.push_back (new PPMNode (context_level_ + 1, false, symbol));
}

void PPMNode::increaseOccurrenceCounter (void) {
    occurrence_counter_++;
}

bool PPMNode::hasSymbol (const std::size_t &symbol) {
    return symbol == symbol_;
}

std::size_t PPMNode::getOccurrenceCounter (void) {
    return occurrence_counter_;
}

Probability PPMNode::hasChild (const std::size_t &symbol) {
    // Setup for worst case scenario (no match found)
    Probability prob;
    prob.low = 0;
    prob.high = children_ [0]->getOccurrenceCounter ();
    prob.total = children_ [0]->getOccurrenceCounter ();


    // Sorted children list
    std::priority_queue <PPMNode*, std::vector<PPMNode*>, Compare> sorted_children;

    // Sort every child and check if there is any match
    for (int child_index = 1; child_index < children_.size(); child_index++) {
        sorted_children.push (children_ [child_index]);

        // If match was found, set flag
        if (children_ [child_index]->hasSymbol (symbol)) {
            prob.symbol_index = child_index;
            prob.isEscape = false;
        }
        // Increase the total counter
        prob.total += children_ [child_index]->getOccurrenceCounter();
    }

    // Abort immediately if no match was found
    if (prob.isEscape) return prob;

    // Go after the match
    for (int child_index = 1; child_index < children_.size(); child_index++) {
        // Whenever loop reaches the match, set the probability struct and abort immediately.
        if (sorted_children [child_index]->hasSymbol (symbol)) {
            prob.low = prob.total;
            prob.high = prob.total + sorted_children [child_index]->getOccurrenceCounter();
            break;
        }
    }

    // Return probability struct;
    return prob;
}

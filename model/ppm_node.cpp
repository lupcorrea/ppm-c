#include "ppm_node.h"

#include <algorithm>
#include <queue>

#include "node_info.h"

PPMNode::PPMNode (const int &context_level, const bool isEscape, const std::size_t &symbol) {
    // Setup basic information
    context_level_ = context_level;
    symbol_ = symbol;
    if (!isEscape) occurrence_counter_ = 1;

    // Create escape child if it is possible for this node to have children
    if (context_level_ < kMaxOrder && !isEscape) children_.push_back (new PPMNode (context_level_ + 1, true, kEscape));
}

Probability PPMNode::searchForMatch (const std::vector <std::size_t> &context, const std::size_t &current_order) {
    Probability prob;

    // If this is tree's root, activate recursivity
    if (context_level_ == -1) {
        for (std::size_t child_index = 1; child_index < children_.size(); child_index++) {
            if (children_ [child_index]->hasSymbol (context [current_order])) {
                prob = searchForMatch (context, current_order-1);
                return prob;
            }
        }
    }

    // If current semileaf is not a context yet, do not even try.
    if (current_order == 1 && !isContext()) {
        createNewChild (context [0]);
        prob.hasContext = false;
        return prob;
    };

    // Non-recursive part: if reached  a semileaf, try to find the child we are after.
    if (current_order == 1) {
        prob = hasChild (context [0]);
        if (prob.isEscape) createNewChild (context [0]);
        else children_ [prob.symbol_index]->increaseOccurrenceCounter();
        return prob;
    }

    // Recursive part: keep trying to find a match for all of the context elements
    for (std::size_t child_index = 1; child_index < children_.size(); child_index++) {
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
    children_ [0]->increaseOccurrenceCounter();

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
    Probability prob;

    // If there is no occurrence at escape counter, this is a newly created node.
    // Abort immediately.
    if (children_ [0]->occurrence_counter_ == 0) {
        prob.hasContext = false;
        return prob;
    }

    // Setup for worst case scenario (no match found)
    prob.low = 0;
    prob.high = children_ [0]->getOccurrenceCounter ();
    prob.total = children_ [0]->getOccurrenceCounter ();


    // Sorted children list
    std::priority_queue <PPMNode*, std::vector<PPMNode*>, Compare> sorted_children;

    // Sort every child and check if there is any match
    for (std::size_t child_index = 1; child_index < children_.size(); child_index++) {
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
    std::size_t counter = children_ [0]->getOccurrenceCounter();
    while (true) {
        if (!sorted_children.top()->hasSymbol (symbol)) {
            counter += sorted_children.top()->getOccurrenceCounter();
            sorted_children.pop();
            continue;
        }

        prob.low = counter;
        prob.high = prob.low + sorted_children.top()->getOccurrenceCounter();
        break;
    }

    // Return probability struct;
    return prob;
}

Probability PPMNode::encodeFirstSymbol (const std::size_t &symbol) {
    Probability prob;

    prob.low = symbol;
    prob.high = symbol + 1;
    prob.total = kAlphabetSize;

    createNewChild (symbol);

    return prob;
}

void PPMNode::searchForChild (const std::size_t& symbol, PPMNode *output) {
    for (std::size_t child_index = 1; child_index < children_.size(); child_index++) {
        if (children_ [child_index]->hasSymbol (symbol)) {
            output = children_ [child_index];
            break;
        }
    }

    output = nullptr;
}

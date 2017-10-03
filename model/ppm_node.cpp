#include "ppm_node.h"

#include "../definitions.h"

PPMNode::PPMNode (std::size_t tree_level, std::size_t symbol) {
    // Setup the node info
    data_.context_level = tree_level;
    data_.symbol = symbol;

    // Build escape child node
    if (tree_level < kMaxOrder && symbol != kEscape) children_->emplace_back (tree_level + 1, kEscape);
}

Probability PPMNode::findSymbol (const std::size_t &context, const int &context_level) {
    Probability odds;

    // If program reached the last parent node, exit recursivity
    if (context_level == context.size() - 2) {
        // Attempt to find node already setup with that symbol
        for (int child_index = 1; child_index < children_.size(); child_index++) {
            // If program finds a node already setup with that symbol
            if (children_ [child_index]->hasSymbol (context [context_level + 1])) {
                odds = buildProbability (child_index, false);
                children_ [child_index]->updateNode();
                break;
            }
        }

        // If program could not find a node already setup with that symbol
        if (odds.isEscape) {
            odds = buildProbability (0, true);
            children_.emplace_back (context_level + 1, context [context_level + 1]);
            children_.front()->updateNode();
            children_.back()->updateNode();
        }
    } else {
        // Attempt to find node already setup with that symbol (next context level)
        for (int child_index = 1; child_index < children_.size(); child_index++) {
            if (children_ [child_index]->hasSymbol (context [context_level + 1])) {
                odds = children_ [child_index]->findSymbol [context, context_level + 1];
                break;
            }
        }
    }

    return odds;
}

bool PPMNode::hasSymbol (std::size_t symbol) {
    return data_.symbol == symbol;
}

// TODO
Probability PPMNode::buildProbability (const std::size_t &child_index, const bool &isEscape) {
    Probability odds;

    return odds;
}

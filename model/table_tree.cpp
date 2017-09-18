#include "table_tree.h"

TableTree::TableTree() {
    static TableNode root;

    root.context_level = -1;
    root.symbol = NULL;
    root.occurrence_counter = NULL;

    root_ = &root;
}

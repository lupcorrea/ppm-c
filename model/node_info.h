#ifndef PPM_NODE_INFO_H_
#define PPM_NODE_INFO_H_

struct Probability {
    bool isEscape = true;
    std::size_t symbol_index = 0;
    unsigned int low;
    unsigned int high;
    unsigned int total;
    bool hasContext = true;
};

#endif // PPM_TABLE_CELL_H_

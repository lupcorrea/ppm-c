#ifndef PPM_NODE_INFO_H_
#define PPM_NODE_INFO_H_

struct Probability {
    bool isEscape = true;
    unsigned int low;
    unsigned int high;
    unsigned int total;
};

#endif // PPM_TABLE_CELL_H_

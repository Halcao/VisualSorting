#ifndef BUBBLESORTER_H
#define BUBBLESORTER_H

#include <sorter.h>

class BubbleSorter: public Sorter {
public:
    BubbleSorter() { name = "BubbleSort"; };
//    string name = "BubbleSort";
    SorterType type = BubbleSorterType;
    virtual void sort();
};

#endif // BUBBLESORTER_H

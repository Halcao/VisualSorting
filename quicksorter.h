#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include <sorter.h>

class QuickSorter: public Sorter {
public:
    QuickSorter() {
        name = "QuickSort";
        type = QuickSorterType;
    };
//    string name = "QuickSort";
    virtual void sort();
};

#endif // QuickSORTER_H

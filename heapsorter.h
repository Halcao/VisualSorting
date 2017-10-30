#ifndef HEAPSORTER_H
#define HEAPSORTER_H

#include <sorter.h>

class HeapSorter: public Sorter {
public:
    HeapSorter() {
        name = "HeapSort";
        type = HeapSorterType;
    };
//    string name = "HeapSort";
    virtual void sort();
private:
    void AdjustDown(int i, int len);
    void BuildMaxHeap(int len);
};

#endif // HeapSORTER_H

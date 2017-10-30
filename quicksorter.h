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
private:
    int partition(int low, int high);
    void quickSort(int low, int high);
};

#endif // QuickSORTER_H

#include "sorterfactory.h"

Sorter *SorterFactory::getSorter(const string &name) {
    if (name == "BubbleSort") {
        return new BubbleSorter;
    } else if (name == "QuickSort") {
        return new QuickSorter;
    } else if (name == "HeapSort") {
        return new HeapSorter;
    } else {
        return NULL;
    }
}

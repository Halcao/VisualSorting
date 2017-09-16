#include "sorterfactory.h"

Sorter *SorterFactory::getSorter(const string &name) {
    if (name == "BubbleSort") {
        return new BubbleSorter;
    } else if (name == "QuickSort") {
        return new BubbleSorter;
    } else if (name == "HeapSort") {
        return new BubbleSorter;
    } else {
        return NULL;
    }
}

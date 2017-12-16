#include "bubblesorter.h"
#include <iostream>

void BubbleSorter::sort() {
//    vector<int> a = array;
    for (unsigned int i = 0; i < array.size(); i++) {
        for (unsigned int j = 1; j < array.size() - i; j++) {
            if (state == SortingStateNotSorting) {
                return;
            }
            if (array[j-1] > array[j]) {
                int tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
                emit render1(j-1, j);
            }
        }
    }
}

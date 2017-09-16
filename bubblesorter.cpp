#include "bubblesorter.h"


void BubbleSorter::sort() {
    for (int i = 0; i < (int)size(); i++) {
        for (int j = 1; j < (int)size()-i; i++) {
            // if not sorting, stop it
            if (state == SortingStateNotSorting) {
                onStopSorting();
                return;
            }

            // flags to decide whether to swap or not
            bool ascendingNeedSwap = (array[j-1] > array[j]) && isAscending;
            bool descendingNeedSwap = (array[j-1] < array[j]) && !isAscending;
            if (ascendingNeedSwap || descendingNeedSwap) {
                // swap to right order
                swap(array[j-1], array[j]);
                // update UI
                render(j-1, j);
            }
        }
    }
}

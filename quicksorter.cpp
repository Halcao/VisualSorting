#include "quicksorter.h"
#include <iostream>

void QuickSorter::sort() {
    vector<int> a = array;
    for (unsigned int i = 0; i < a.size(); i++) {
        for (unsigned int j = 1; j < a.size() - i; j++) {
            if (a[j-1] > a[j]) {
                int tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
                emit render1(j-1, j);
            }
        }
    }
//    for(int i = 0; i < (int)size(); i++) {
//        for (int j = 1; j < (int)size()-i; i++) {
//            // if not sorting, stop it
//            if (state == SortingStateNotSorting) {
//                onStopSorting();
//                return;
//            }

//            // flags to decide whether to swap or not
////            bool ascendingNeedSwap = (array[j-1] > array[j]) && isAscending;
////            bool descendingNeedSwap = (array[j-1] < array[j]) && !isAscending;
////            if (ascendingNeedSwap || descendingNeedSwap) {
//            if (array[j-1] > array[j]) {
//                // swap to right order
////                swap(array[j-1], array[j]);
//                int tmp = array[j-1];
//                array[j-1] = array[j];
//                array[j] = tmp;
//                // update UI
////                render(j-1, j);
//                emit render1(j-1, j);
//            }
//        }
//    }
}
